#pragma once
#include "../stdlibs.h"
#include "tarch/la/Vector.h"

namespace kernels::shared{
namespace dim2 {

    const int Dimensions=2;
    void splitRusanov1d(
        std::function< void(
            const double * __restrict__ Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double * __restrict__ F
        ) >   flux,
        std::function< void(
            const double * __restrict__                  Q,
            const double * __restrict__     deltaQ,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double * __restrict__ BgradQ
        ) >   nonconservativeProduct,
        std::function< double(
            const double * __restrict__ Q,
            const tarch::la::Vector<Dimensions,double>&  faceCentre,
            const tarch::la::Vector<Dimensions,double>&  volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal
        ) >   eigenvalues,
        const double * __restrict__ QL,
        const double * __restrict__ QR,
        const tarch::la::Vector<Dimensions,double>&  x,
        double                                       dx,
        double                                       t,
        double                                       dt,
        int                                          normal,
        int                                          unknowns,
        int                                          auxiliaryVariables,
        double * __restrict__     FL,
        double * __restrict__     FR,
        bool skipFluxEvaluation   = false,
        bool skipNCPEvaluation    = false
        );

    void applySplit1DRiemannToPatch_Overlap1AoS2d(
        std::function< void(
            const double * __restrict__ QL,
            const double * __restrict__ QR,
            const tarch::la::Vector<2,double>&           faceCentre,
            double                                       volumeH,
            double                                       t,
            double                                       dt,
            int                                          normal,
            double * __restrict__ FL,
            double * __restrict__ FR
        ) >   splitRiemannSolve1d,
        std::function< void(
            const double * __restrict__ Q,
            const tarch::la::Vector<2,double>&           volueCentre,
            double                                       volumeH,
            double                                       t,
            double                                       dt,
            double * __restrict__ S
        ) >   sourceTerm,
        const tarch::la::Vector<2,double>&           patchCentre,
        const tarch::la::Vector<2,double>&           patchSize,
        double                                       t,
        double                                       dt,
        int                                          numberOfVolumesPerAxisInPatch,
        int                                          unknowns,
        int                                          auxiliaryVariables,
        const double * __restrict__                  Qin,
        double * __restrict__                        Qout
        );

    tarch::la::Vector<2,double>  getVolumeSize(
        const tarch::la::Vector<2,double>&  h,
        int                                 numberOfVolumesPerAxisInPatch
  );
}}