#include "RusanovNonlinearAoS.h"

#include "Generic.h"

#include "KernelUtils.h"

#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
GPUCallableMethod void exahype2::dg::rusanovNonlinear_setBoundaryState_body_AoS(
  std::function< void(
    double * __restrict__                       QInside,
    double * __restrict__                       OOutside,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal
  ) >                                         boundaryState,
  double * __restrict__                       QOut,
  double * __restrict__                       QIn,
  const double * __restrict__                 nodes,
  const double                                t,
  const double                                dt,
  const tarch::la::Vector<Dimensions,double>& faceCentre,
  const double                                dx,
  const int                                   nodesPerAxis,
  const int                                   unknowns,
  const int                                   strideQ,
  const int                                   direction,
  const int                                   scalarIndexFace) {
  const tarch::la::Vector<Dimensions+1,int> indexQFace = // (t,y,z,face=0) , (t,x,z,face=0), (t,x,y,face=0)
    delineariseIndex(scalarIndexFace,getStrides(nodesPerAxis,false)); 
  const tarch::la::Vector<Dimensions+1,double> coords = 
    getCoordinatesOnFace(indexQFace,faceCentre,direction,dx,t,dt,nodes);
  const tarch::la::Vector<Dimensions,double> x(&coords[1]);
  const double time = coords[0];

  boundaryState( &QIn[ scalarIndexFace*strideQ ], &QOut[ scalarIndexFace*strideQ ], x, time, direction );
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif

#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
GPUCallableMethod double exahype2::dg::rusanovNonlinear_maxAbsoluteEigenvalue_body_AoS(
  std::function< double(
    const double * __restrict__                 Q,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    const int                                   normal
  ) >                                         maxAbsoluteEigenvalue,
  const double * __restrict__                 QLR[2],
  const double * __restrict__                 nodes,
  const double                                t,
  const double                                dt,
  const tarch::la::Vector<Dimensions,double>& faceCentre,
  const double                                dx,
  const int                                   nodesPerAxis,
  const int                                   unknowns,
  const int                                   strideQ,
  const int                                   direction,
  const int                                   scalarIndexFace) {
  const tarch::la::Vector<Dimensions+1,int> indexQFace = // (y,z,face) , (x,z,face), (x,y,face)
    delineariseIndex(scalarIndexFace,getStrides(nodesPerAxis,false)); 
  const tarch::la::Vector<Dimensions+1,double> coords = 
    getCoordinatesOnFace(indexQFace,faceCentre,direction,dx,t,dt,nodes);
  const tarch::la::Vector<Dimensions,double> x(&coords[1]);
  const double time = coords[0];

  const int lr = indexQFace[Dimensions];
 
  // hyperbolic eigenvalues
  return maxAbsoluteEigenvalue( &QLR[lr][ scalarIndexFace*strideQ ], x, time, direction );
  // @todo: check this value is > 0.
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif

#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
GPUCallableMethod void exahype2::dg::rusanovNonlinear_riemannFlux_body_AoS(
    std::function< void(
      const double * __restrict__                 Q,
      const tarch::la::Vector<Dimensions,double>& x,
      double                                      t,
      int                                         normal,
      double * __restrict__                       F
    ) >                                         fluxL,
    std::function< void(
      const double * __restrict__                 Q,
      const tarch::la::Vector<Dimensions,double>& x,
      double                                      t,
      int                                         normal,
      double * __restrict__                       F
    ) >                                         fluxR,
    double * __restrict__                       FLOut,
    double * __restrict__                       FROut,
    double * __restrict__                       FLAux,
    double * __restrict__                       FRAux,
    const double * __restrict__                 QLIn, 
    const double * __restrict__                 QRIn, 
    const double                                smax,
    const double * __restrict__                 nodes, 
    const double * __restrict__                 weights, 
    const double                                t,
    const double                                dt,
    const tarch::la::Vector<Dimensions,double>& faceCentre,
    const double                                dx,
    const int                                   nodesPerAxis,
    const int                                   unknowns,
    const int                                   strideQ,
    const int                                   strideF,
    const int                                   direction,
    const int                                   scalarIndexFace) {
  const tarch::la::Vector<Dimensions+1,int> indexQFace = // (y,z,face=0) , (x,z,face=0), (x,y,face=0)
    delineariseIndex(scalarIndexFace,getStrides(nodesPerAxis,false)); 
  const tarch::la::Vector<Dimensions+1,double> coords = 
    getCoordinatesOnFace(indexQFace,faceCentre,direction,dx,t,dt,nodes);
  const tarch::la::Vector<Dimensions,double> x(&coords[1]);

  // time-averaged flux FLOut
  const int offsetQ = scalarIndexFace*strideQ;
  const double coeff1 = 0.5;
  const double coeff2 = coeff1 * smax;
  
  const double time = t;
  
  fluxL( QLIn + offsetQ, x, time, direction, FLAux ); 
  fluxR( QRIn + offsetQ, x, time, direction, FRAux );
  for (int var = 0; var < unknowns; var++) {
    FLOut[ scalarIndexFace*strideF + var ] += coeff1 * (FRAux[ var ] + FLAux[ var ]);
  }
  
  for (int var = 0; var < unknowns; var++) {
    FLOut[ scalarIndexFace*strideF + var ] -= coeff2 * (QRIn[ offsetQ + var ] - QLIn[ offsetQ + var ]);
  }
  // copy FLOut to FROut
  for (int var = 0; var < unknowns; var++) {
    FROut[ scalarIndexFace*strideF + var ] = FLOut[ scalarIndexFace*strideF + var ]; 
  }
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif

#if defined(OpenMPGPUOffloading)
#pragma omp declare target
#endif
GPUCallableMethod void exahype2::dg::rusanovNonlinear_addNcpContributionsToRiemannFlux_body_AoS(
    std::function< void(
      double * __restrict__                       Q,
      double * __restrict__                       dQ_or_deltaQ,
      const tarch::la::Vector<Dimensions,double>& x,
      double                                      t,
      int                                         normal,
      double * __restrict__                       BgradQ
    ) >                                         nonconservativeProduct,
    double * __restrict__                       FLOut,
    double * __restrict__                       FROut,
    double * __restrict__                       QAvgAux,
    double * __restrict__                       dQAux,
    double * __restrict__                       SAux,
    const double * __restrict__                 QLIn, 
    const double * __restrict__                 QRIn, 
    const double                                smax,
    const double * __restrict__                 nodes, 
    const double * __restrict__                 weights, 
    const double                                t,
    const double                                dt,
    const tarch::la::Vector<Dimensions,double>& faceCentre,
    const double                                dx,
    const int                                   nodesPerAxis,
    const int                                   unknowns,
    const int                                   strideQ,
    const int                                   strideF,
    const int                                   direction,
    const int                                   scalarIndexFace) {
  const tarch::la::Vector<Dimensions+1,int> indexQFace = // (y,z,face=0) , (x,z,face=0), (x,y,face=0)
    delineariseIndex(scalarIndexFace,getStrides(nodesPerAxis,false)); 
  const tarch::la::Vector<Dimensions+1,double> coords = 
    getCoordinatesOnFace(indexQFace,faceCentre,direction,dx,t,dt,nodes);
  const tarch::la::Vector<Dimensions,double> x(&coords[1]);
    
  const int offsetQ = scalarIndexFace*strideQ;
  
  for (int var=0; var < strideQ; var++) {
    dQAux[ var ] = QRIn[ offsetQ + var ] - QLIn[ offsetQ + var ];
  }
  
  for (int var=0; var < strideQ; var++) {
    QAvgAux[var] = 0.5 * (QRIn[ offsetQ + var ] + QLIn[ offsetQ + var ]);
  }
  
  const double time = t;
  nonconservativeProduct(QAvgAux,  dQAux, x, time, direction, SAux);

  const double coeff = 0.5;
  for (int var = 0; var < unknowns; var++) {
    FROut[ scalarIndexFace*strideF + var ] -= coeff * SAux[var];
  }
  
  for (int var = 0; var < unknowns; var++) {
    FLOut[ scalarIndexFace*strideF + var ] += coeff * SAux[var];
  }
}
#if defined(OpenMPGPUOffloading)
#pragma omp end declare target
#endif


// launchers

void exahype2::dg::rusanovNonlinear_setBoundaryState_loop_AoS(
  std::function< void(
    double * __restrict__                       QInside,
    double * __restrict__                       OOutside,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal
  ) >                                         boundaryState,
  double * __restrict__                       QOut,
  double * __restrict__                       QIn,
  const double * __restrict__                 nodes,
  const double                                t,
  const double                                dt,
  const tarch::la::Vector<Dimensions,double>& faceCentre,
  const double                                dx,
  const int                                   order,
  const int                                   unknowns,
  const int                                   auxiliaryVariables,
  const int                                   direction) {
  const unsigned int nodesPerAxis = order + 1;

  const unsigned int strideQ = unknowns + auxiliaryVariables; 

  const unsigned int nodesOnFace = getNodesPerCell(nodesPerAxis)/nodesPerAxis; // nodesPerAxis^d-1

  for ( unsigned int scalarIndexFace = 0; scalarIndexFace < nodesOnFace; scalarIndexFace++ ) {
    rusanovNonlinear_setBoundaryState_body_AoS(
      boundaryState,
      QOut,
      QIn,
      nodes,
      t,
      dt,
      faceCentre,
      dx,
      nodesPerAxis,
      unknowns,
      strideQ,
      direction,
      scalarIndexFace);
  } 
}

double exahype2::dg::rusanovNonlinear_maxAbsoluteEigenvalue_loop_AoS(
  std::function< double(
    const double * __restrict__                 Q,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal
  ) >                                         maxAbsoluteEigenvalue,
  const double * __restrict__                 QL,
  const double * __restrict__                 QR,
  const double * __restrict__                 nodes,
  const double                                t,
  const double                                dt,
  const tarch::la::Vector<Dimensions,double>& faceCentre,
  const double                                dx,
  const int                                   order,
  const int                                   unknowns,
  const int                                   auxiliaryVariables,
  const int                                   direction) {
  const unsigned int nodesPerAxis = order + 1;

  const unsigned int strideQ = unknowns + auxiliaryVariables; 

  const unsigned int nodesOnInterface = getNodesPerCell(nodesPerAxis)/nodesPerAxis * 2; // nodesPerAxis^d-1 * 2

  const double* QLR[2] = {QL,QR};
 
  double maxAbsEigenvalue = 0.0;  // strictly positive
  for ( unsigned int scalarIndexFace = 0; scalarIndexFace < nodesOnInterface; scalarIndexFace++ ) {
    const double smax = 
      rusanovNonlinear_maxAbsoluteEigenvalue_body_AoS(
        maxAbsoluteEigenvalue,
        QLR,
        nodes,
        t,
        dt,
        faceCentre,
        dx,
        nodesPerAxis,
        unknowns,
        strideQ,
        direction,
        scalarIndexFace);
    maxAbsEigenvalue = std::max( maxAbsEigenvalue, smax );
  } 
  return maxAbsEigenvalue;
}

void exahype2::dg::rusanovNonlinear_loop_AoS(
  std::function< void(
    const double * __restrict__                 Q,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal,
    double * __restrict__                       F
  ) >                                         flux,
  std::function< void(
    const double * __restrict__                 Q,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal,
    double * __restrict__                       F
  ) >                                         boundaryFlux,
  std::function< void(
    double * __restrict__                       Q,
    double * __restrict__                       dQ_or_deltaQ,
    const tarch::la::Vector<Dimensions,double>& x,
    double                                      t,
    int                                         normal,
    double * __restrict__                       BgradQ
  ) >                                         nonconservativeProduct,
  double * __restrict__                       FLOut,
  double * __restrict__                       FROut,
  const double * __restrict__                 QLIn, 
  const double * __restrict__                 QRIn, 
  const double                                smax,
  const double * __restrict__                 nodes, 
  const double * __restrict__                 weights, 
  const double                                t,
  const double                                dt,
  const tarch::la::Vector<Dimensions,double>& faceCentre,
  const double                                dx,
  const int                                   order,
  const int                                   unknowns,
  const int                                   auxiliaryVariables,
  const int                                   direction,
  const bool                                  leftCellIsOutside,
  const bool                                  rightCellIsOutside,
  const bool                                  callFlux,
  const bool                                  callNonconservativeProduct) {
  const unsigned int nodesPerAxis = order + 1;

  const int strideQ  = unknowns+auxiliaryVariables;
  const int strideS  = unknowns;
  const int strideF  = unknowns;
  const int strideDQ = strideQ; // gradient of auxiliary variables needed for some apps

  const unsigned int nodesOnFace = getNodesPerCell(nodesPerAxis)/nodesPerAxis; // nodesPerAxis^(d-1)
  
  double * FAux     = new double[2*nodesOnFace*strideF]{0.0}; 
  double * QAvgAux  = new double[nodesOnFace*strideQ]{0.0};
  double * SAux     = new double[nodesOnFace*strideS]{0.0};
  double * dQAux    = new double[nodesOnFace*strideDQ]{0.0};
  double * FBndAux  = new double[nodesOnFace*strideF]{0.0};
  
  for ( unsigned int scalarIndexFace = 0; scalarIndexFace < nodesOnFace; scalarIndexFace++ ) {
    if ( callFlux ) {
      rusanovNonlinear_riemannFlux_body_AoS(
        ( leftCellIsOutside )  ? boundaryFlux : flux,
        ( rightCellIsOutside ) ? boundaryFlux : flux,
        ( leftCellIsOutside )  ? FBndAux : FLOut,
        ( rightCellIsOutside ) ? FBndAux : FROut,
        &FAux[ scalarIndexFace*2*strideF ],
        &FAux[ scalarIndexFace*2*strideF + strideF ],
        QLIn, 
        QRIn, 
        smax,
        nodes, 
        weights, 
        t,
        dt,
        faceCentre,
        dx,
        nodesPerAxis,
        unknowns,
        strideQ,
        strideF,
        direction,
        scalarIndexFace);
    }
    if ( callNonconservativeProduct ) {
      rusanovNonlinear_addNcpContributionsToRiemannFlux_body_AoS(
        nonconservativeProduct,
        ( leftCellIsOutside ) ? FBndAux : FLOut,
        ( rightCellIsOutside ) ? FBndAux : FROut,
        &QAvgAux[ scalarIndexFace*strideQ ],
        &dQAux[ scalarIndexFace*strideDQ ],
        &SAux[ scalarIndexFace*strideS ],
        QLIn, 
        QRIn, 
        smax,
        nodes, 
        weights, 
        t,
        dt,
        faceCentre,
        dx,
        nodesPerAxis,
        unknowns,
        strideQ,
        strideF,
        direction,
        scalarIndexFace);
    }
  }

  delete [] FAux;
  delete [] QAvgAux;
  delete [] SAux;
  delete [] dQAux;
}  
