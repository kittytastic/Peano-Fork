#include "matrixfree/stencil/StencilFactory.h"

#include "peano/utils/Loop.h"


matrixfree::stencil::Stencil
matrixfree::stencil::exchangeCoordinates( const Stencil& stencil, int coord0, int coord1 ) {
    Stencil result;

#ifdef Dim3
    d3for3(destination)
            tarch::la::Vector<DIMENSIONS,int> source;
    source = destination;
    source(coord0) = destination(coord1);
    source(coord1) = destination(coord0);
    result( peano::utils::dLinearised(destination,3) ) = stencil( peano::utils::dLinearised(source,3) );
    enddforx
        #else
    assertionMsg( false, "operation only supported for d=3" );
#endif

    return result;
}


tarch::la::Vector<5,double> matrixfree::stencil::get1DLinearInterpolationStencil() {
    tarch::la::Vector<5,double> result;
    result(0) =  1.0 / 3.0;
    result(1) =  2.0 / 3.0;
    result(2) =  3.0 / 3.0;
    result(3) =  2.0 / 3.0;
    result(4) =  1.0 / 3.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DMassStencil() {
    tarch::la::Vector<3,double> result;
    result(0) =  1.0 / 6.0;
    result(1) =  4.0 / 6.0;
    result(2) =  1.0 / 6.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DIdentity() {
    tarch::la::Vector<3,double> result;
    result(0) =  0.0;
    result(1) =  1.0;
    result(2) =  0.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DLeftIdentity() {
    tarch::la::Vector<3,double> result;
    result(0) =  1.0;
    result(1) =  0.0;
    result(2) =  0.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DRightIdentity() {
    tarch::la::Vector<3,double> result;
    result(0) =  0.0;
    result(1) =  0.0;
    result(2) =  1.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DDownwindStencil() {
  tarch::la::Vector<3,double> result;
  result(0) =  -1.0;
  result(1) =  1.0;
  result(2) =  0.0;
  return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DUpwindStencil() {
  tarch::la::Vector<3,double> result;
  result(0) =  0.0;
  result(1) = -1.0;
  result(2) =  1.0;
  return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DCentralDifferencesStencil() {
  tarch::la::Vector<3,double> result;
  result(0) = -1.0;
  result(1) =  0.0;
  result(2) =  1.0;
  return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DMeanValueStencil() {
    tarch::la::Vector<3,double> result;
    result(0) =  1.0 / 2.0;
    result(1) =  0.0;
    result(2) =  1.0 / 2.0;
    return result;
}


tarch::la::Vector<3,double> matrixfree::stencil::get1DLaplaceStencil() {
    tarch::la::Vector<3,double> result;
    result(0) = -1.0;
    result(1) =  2.0;
    result(2) = -1.0;
    return result;
}


tarch::la::Vector<3*3,double> matrixfree::stencil::stencilProduct(
        const tarch::la::Vector<3,double>& a,
        const tarch::la::Vector<3,double>& b
        ) {
    tarch::la::Vector<3*3,double> result;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            result(i+j*3) = a(i) * b(j);
        }
    }

    return result;
}


tarch::la::Vector<5*5,double> matrixfree::stencil::stencilProduct(
        const tarch::la::Vector<5,double>& a,
        const tarch::la::Vector<5,double>& b
        ) {
    tarch::la::Vector<5*5,double> result;

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            result(i+j*5) = a(i) * b(j);
        }
    }

    return result;
}


tarch::la::Vector<3*3*3,double> matrixfree::stencil::stencilProduct(
        const tarch::la::Vector<3,double>& a,
        const tarch::la::Vector<3,double>& b,
        const tarch::la::Vector<3,double>& c
        ) {
    tarch::la::Vector<3*3*3,double> result;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                result(i+j*3+k*3*3) = a(i) * b(j) * c(k);
            }
        }
    }

    return result;
}


tarch::la::Vector<5*5*5,double> matrixfree::stencil::stencilProduct(
        const tarch::la::Vector<5,double>& a,
        const tarch::la::Vector<5,double>& b,
        const tarch::la::Vector<5,double>& c
        ) {
    tarch::la::Vector<5*5*5,double> result;

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            for (int k=0; k<5; k++) {
                result(i+j*5+k*5*5) = a(i) * b(j) * c(k);
            }
        }
    }

    return result;
}


tarch::la::Vector<3*3*3*3,double> matrixfree::stencil::stencilProduct(
  const tarch::la::Vector<3,double>& a,
  const tarch::la::Vector<3,double>& b,
  const tarch::la::Vector<3,double>& c,
  const tarch::la::Vector<3,double>& d
) {
  tarch::la::Vector<3*3*3*3,double> result;

  for (int ai=0; ai<3; ai++) {
    for (int bi=0; bi<3; bi++) {
      for (int ci=0; ci<3; ci++) {
        for (int di=0; di<3; di++) {
          result(ai+bi*3+ci*3*3+di*3*3*3) = a(ai) * b(bi) * c(ci) * d(di);
        }
      }
    }
  }

  return result;
}


tarch::la::Vector<5*5*5*5,double> matrixfree::stencil::stencilProduct(
  const tarch::la::Vector<5,double>& a,
  const tarch::la::Vector<5,double>& b,
  const tarch::la::Vector<5,double>& c,
  const tarch::la::Vector<5,double>& d
) {
  tarch::la::Vector<5*5*5*5,double> result;

  for (int ai=0; ai<5; ai++) {
    for (int bi=0; bi<5; bi++) {
      for (int ci=0; ci<5; ci++) {
        for (int di=0; di<5; di++) {
          result(ai+bi*5+ci*5*5+di*5*5*5) = a(ai) * b(bi) * c(ci) * d(di);
        }
      }
    }
  }

  return result;
}


tarch::la::Vector<3*3*3*3*3,double> matrixfree::stencil::stencilProduct(
  const tarch::la::Vector<3,double>& a,
  const tarch::la::Vector<3,double>& b,
  const tarch::la::Vector<3,double>& c,
  const tarch::la::Vector<3,double>& d,
  const tarch::la::Vector<3,double>& e
) {
  tarch::la::Vector<3*3*3*3*3,double> result;

  for (int ai=0; ai<3; ai++) {
    for (int bi=0; bi<3; bi++) {
      for (int ci=0; ci<3; ci++) {
        for (int di=0; di<3; di++) {
          for (int ei=0; ei<3; ei++) {
            result(ai+bi*3+ci*3*3+di*3*3*3+ei*3*3*3*3) = a(ai) * b(bi) * c(ci) * d(di) * e(ei);
          }
        }
      }
    }
  }

  return result;
}


tarch::la::Vector<5*5*5*5*5,double> matrixfree::stencil::stencilProduct(
  const tarch::la::Vector<5,double>& a,
  const tarch::la::Vector<5,double>& b,
  const tarch::la::Vector<5,double>& c,
  const tarch::la::Vector<5,double>& d,
  const tarch::la::Vector<5,double>& e
) {
  tarch::la::Vector<5*5*5*5*5,double> result;

  for (int ai=0; ai<5; ai++) {
    for (int bi=0; bi<5; bi++) {
      for (int ci=0; ci<5; ci++) {
        for (int di=0; di<5; di++) {
          for (int ei=0; ei<5; ei++) {
            result(ai+bi*5+ci*5*5+di*5*5*5+ei*5*5*5*5) = a(ai) * b(bi) * c(ci) * d(di) * e(ei);
          }
        }
      }
    }
  }

  return result;
}


tarch::la::Vector<THREE_POWER_D,double> matrixfree::stencil::getLaplacian(
  const tarch::la::Vector<DIMENSIONS,double>& h,
  const tarch::la::Vector<DIMENSIONS,double>& scaling
) {
  tarch::la::Vector<THREE_POWER_D,double> result;

  #if defined(Dim2)
  result =  scaling(0) * h(1)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            )
            + scaling(1) * h(0)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            );
  #elif defined(Dim3)
  result =  scaling(0) * h(1)*h(2)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            )
            + scaling(1) * h(0)*h(2)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            )
            + scaling(2) * h(0)*h(1)/h(2) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            );
  #else
  assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getLaplacian(
  const tarch::la::Vector<DIMENSIONS,std::complex<double> >& h,
  const tarch::la::Vector<DIMENSIONS,std::complex<double> >& scaling
) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  scaling(0) * h(1)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(1) * h(0)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            ).convertScalar< std::complex<double> >();
  #elif defined(Dim3)
  result =  scaling(0) * h(1)*h(2)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(1) * h(0)*h(2)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(2) * h(0)*h(1)/h(2) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            ).convertScalar< std::complex<double> >();
  #elif defined(Dim4)
  result =  scaling(0) * h(1)*h(2)*h(3)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(1) * h(0)*h(2)*h(3)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(2) * h(0)*h(1)*h(3)/h(2) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(2) * h(0)*h(1)*h(2)/h(3) *
              matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            ).convertScalar< std::complex<double> >();
  #elif defined(Dim5)
  result =  scaling(0) * h(1)*h(2)*h(3)*h(4)/h(0) *
          matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DLaplaceStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil()
          ).convertScalar< std::complex<double> >()
          + scaling(1) * h(0)*h(2)*h(3)*h(4)/h(1) *
          matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DLaplaceStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil()
          ).convertScalar< std::complex<double> >()
          + scaling(2) * h(0)*h(1)*h(3)*h(4)/h(2) *
          matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DLaplaceStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil()
          ).convertScalar< std::complex<double> >()
          + scaling(2) * h(0)*h(1)*h(2)*h(4)/h(3) *
            matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DLaplaceStencil(),
            matrixfree::stencil::get1DMassStencil()
          ).convertScalar< std::complex<double> >();
          + scaling(2) * h(0)*h(1)*h(2)*h(3)/h(4) *
            matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DLaplaceStencil()
          ).convertScalar< std::complex<double> >();
  #else
  assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}

tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getLaplacian(
  const tarch::la::Vector<DIMENSIONS,double >& h,
  const tarch::la::Vector<DIMENSIONS,std::complex<double> >& scaling
) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  scaling(0) * h(1)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(1) * h(0)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            ).convertScalar< std::complex<double> >();
  #elif defined(Dim3)
  result =  scaling(0) * h(1)*h(2)/h(0) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(1) * h(0)*h(2)/h(1) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            + scaling(2) * h(0)*h(1)/h(2) *
            matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DLaplaceStencil()
            ).convertScalar< std::complex<double> >();
  #else
  assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<THREE_POWER_D,double> matrixfree::stencil::getMassMatrix(const tarch::la::Vector<DIMENSIONS,double>& h) {
  tarch::la::Vector<THREE_POWER_D,double> result;

  #if defined(Dim2)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ) * h(0) * h(1);
  #elif defined(Dim3)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ) * h(0) * h(1) * h(2);
  #else
    assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getMassMatrix(const tarch::la::Vector<DIMENSIONS,std::complex<double> >& h) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >()
            * h(0) * h(1);
  #elif defined(Dim3)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil()
            ).convertScalar< std::complex<double> >() * h(0) * h(1) * h(2);
  #else
    assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getHelmholtzShiftMatrix(
        const tarch::la::Vector<DIMENSIONS,double>& h,
        const std::complex<double>& phi ) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  ( h(0) * h(1)* matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil() )
             ).convertScalar< std::complex<double> >();
  #elif defined(Dim3)
  result =  ( h(0) * h(1) * h(2) * matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil() )
              ).convertScalar< std::complex<double> >();
  #else
    assertionMsg( false, "dimension not supported" );
  #endif

  return phi * result;
}

tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getHelmholtzShiftMatrix(
  const tarch::la::Vector<DIMENSIONS,std::complex<double> >& h,
  const std::complex<double>& phi
) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  h(0) * h(1)* (  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil() )
             ).convertScalar< std::complex<double> >();
  #elif defined(Dim3)
  result =  h(0) * h(1) * h(2) * ( matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil(),
              matrixfree::stencil::get1DMassStencil() )
              ).convertScalar< std::complex<double> >();
  #elif defined(Dim4)
  result =  h(0) * h(1) * h(2) * h(3) * ( matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil() )
            ).convertScalar< std::complex<double> >();
  #elif defined(Dim5)
  result =  h(0) * h(1) * h(2) * h(3) * h(4) * ( matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil(),
            matrixfree::stencil::get1DMassStencil() )
            ).convertScalar< std::complex<double> >();
  #else
    assertionMsg( false, "dimension not supported" );
  #endif

  return phi * result;
}


tarch::la::Vector<THREE_POWER_D,double> matrixfree::stencil::getIdentity(const tarch::la::Vector<DIMENSIONS,double>& h) {
  tarch::la::Vector<THREE_POWER_D,double> result;

  #if defined(Dim2)
  result = matrixfree::stencil::stencilProduct(
             matrixfree::stencil::get1DIdentity(),
             matrixfree::stencil::get1DIdentity()
           )
           * h(0) * h(1);
  #elif defined(Dim3)
  result = matrixfree::stencil::stencilProduct(
             matrixfree::stencil::get1DIdentity(),
             matrixfree::stencil::get1DIdentity(),
             matrixfree::stencil::get1DIdentity()
           )
           * h(0) * h(1) * h(2);
  #else
    assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<THREE_POWER_D,std::complex<double> > matrixfree::stencil::getIdentity(const tarch::la::Vector<DIMENSIONS,std::complex<double> >& h) {
  tarch::la::Vector<THREE_POWER_D,std::complex<double> > result;

  #if defined(Dim2)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DIdentity(),
              matrixfree::stencil::get1DIdentity()
            ).convertScalar< std::complex<double> >()
            * h(0) * h(1);
  #elif defined(Dim3)
  result =  matrixfree::stencil::stencilProduct(
              matrixfree::stencil::get1DIdentity(),
              matrixfree::stencil::get1DIdentity(),
              matrixfree::stencil::get1DIdentity()
              ).convertScalar< std::complex<double> >()
            * h(0) * h(1) * h(2);
  #elif defined(Dim4)
  result =  matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity()
            ).convertScalar< std::complex<double> >()
          * h(0) * h(1) * h(2) * h(3);
  #elif defined(Dim4)
  result =  matrixfree::stencil::stencilProduct(
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity(),
            matrixfree::stencil::get1DIdentity()
            ).convertScalar< std::complex<double> >()
          * h(0) * h(1) * h(2) * h(3) * h(4);
  #else
  assertionMsg( false, "dimension not supported" );
  #endif

  return result;
}


tarch::la::Vector<FIVE_POWER_D,double> matrixfree::stencil::getDLinearInterpolation() {
    tarch::la::Vector<FIVE_POWER_D,double> result;
#ifdef Dim2
    result =
            matrixfree::stencil::stencilProduct(
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil()
                );
#elif Dim3
    result =
            matrixfree::stencil::stencilProduct(
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil()
                );
#elif Dim4
    result =
            matrixfree::stencil::stencilProduct(
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil()
                );
#elif Dim5
    result =
            matrixfree::stencil::stencilProduct(
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil(),
                matrixfree::stencil::get1DLinearInterpolationStencil()
                );
#else
    assertionMsg( false, "dimension not supported" );
#endif

    return result;
}
