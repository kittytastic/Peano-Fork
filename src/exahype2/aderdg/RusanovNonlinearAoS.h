#ifndef _EXAHYPE2_ADERDG_RUSANOV_NONLINEAR_AOS_H_
#define _EXAHYPE2_ADERDG_RUSANOV_NONLINEAR_AOS_H_

#include "tarch/la/Vector.h"

#include <functional>

namespace exahype2 {
  namespace aderdg {
      
    /** 
     * @brief Set boundary state at given coordinates and time.
     *
     * @param[in] boundaryState
     * @param[inout] QOut
     * @param[in] QIn
     * @param[in] nodes
     * @param[in] t
     * @param[in] dt
     * @param[in] faceCentre
     * @param[in] dx
     * @param[in] nodesPerAxis
     * @param[in] unknowns
     * @param[in] strideQ
     * @param[in] direction
     * @param[in] orientation
     * @param[in] scalarIndexFace
     */
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    void rusanovNonlinear_setBoundaryState_body_AoS(
      std::function< void(
        const double * __restrict__                 QIn,
        const tarch::la::Vector<Dimensions,double>& x,
        double                                      t,
        int                                         normal,
        double * __restrict__                       OOut
      ) >                                         boundaryState,
      double * __restrict__                       QOut,
      const double * __restrict__                 QIn,
      const double * __restrict__                 nodes,
      const double                                t,
      const double                                dt,
      const tarch::la::Vector<Dimensions,double>& faceCentre,
      const double                                dx,
      const int                                   nodesPerAxis,
      const int                                   unknowns,
      const int                                   strideQ,
      const int                                   direction,
      const int                                   scalarIndexFace);
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif

    /** 
     * Determines the maximum absolute value among the eigenvalues computed 
     * at a space-time quadrature point on a face.
     *
     * @note: Different to the ExaHyPE1 implementation, we compute the
     * maximum of the absolute values of the eigenvalues using
     * all space-time quadrature points.
     *
     * @return the largest absolute eigenvalue
     *
     * @param maxAbsoluteEigenvalue
     * @param QLR,
     * @param t
     * @param dt
     * @param faceCentre
     * @param dx
     * @param nodesPerAxis
     * @param unknowns
     * @param strideQ
     * @param direction
     * @param scalarIndexFace
     */
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    GPUCallableMethod double rusanovNonlinear_maxAbsoluteEigenvalue_body_AoS(
      std::function< double(
        const double * __restrict__                 Q,
        const tarch::la::Vector<Dimensions,double>& x,
        double                                      t,
        const int                                   direction
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
      const int                                   scalarIndexFace);
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    
    /** 
     * compute fluxes (and fluctuations for non-conservative PDEs)
     * @note Zero out FLOut/FROut arrays before.
     */
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    GPUCallableMethod void rusanovNonlinear_riemannFlux_body_AoS(
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
        const int                                   scalarIndexFace);
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif
    
     /** 
      * compute fluxes (and fluctuations for non-conservative PDEs)
      * @note Zero out gradient and FLOut, FROut or call flux function before.
      * @todo also offer an option with a only the flux
      */
     #if defined(OpenMPGPUOffloading)
     #pragma omp declare target
     #endif
     GPUCallableMethod void rusanovNonlinear_addNcpContributionsToRiemannFlux_body_AoS(
        std::function< void(
          double * __restrict__                       Q,
          double                                      gradQ[][Dimensions],
          const tarch::la::Vector<Dimensions,double>& x,
          double                                      t,
          int                                         normal,
          double * __restrict__                       BgradQ
        ) >                                         nonconservativeProduct,
        double * __restrict__                       FLOut,
        double * __restrict__                       FROut,
        double * __restrict__                       QAvgAux,
        double * __restrict__                       gradQAux,
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
        const int                                   scalarIndexFace);
     #if defined(OpenMPGPUOffloading)
     #pragma omp end declare target
     #endif
    
     void rusanovNonlinear_setBoundaryState_loop_AoS(
       std::function< void(
         const double * __restrict__                 QIn,
         const tarch::la::Vector<Dimensions,double>& x,
         double                                      t,
         int                                         normal,
         double * __restrict__                       OOut
       ) >                                         boundaryState,
       double * __restrict__                       QOut,
       const double * __restrict__                 QIn,
       const double * __restrict__                 nodes,
       const double                                t,
       const double                                dt,
       const tarch::la::Vector<Dimensions,double>& faceCentre,
       const double                                dx,
       const int                                   order,
       const int                                   unknowns,
       const int                                   auxiliaryVariables,
       const int                                   direction);
    
     double rusanovNonlinear_maxAbsoluteEigenvalue_loop_AoS(
        std::function< double(
          const double * __restrict__                 Q,
          const tarch::la::Vector<Dimensions,double>& x,
          double                                      t,
          const int                                   direction
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
        const int                                   direction);
    
    void rusanovNonlinear_loop_AoS(
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
        double                                      gradQ[][Dimensions],
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
      const bool                                  callNonconservativeProduct);

  }
}

#endif
