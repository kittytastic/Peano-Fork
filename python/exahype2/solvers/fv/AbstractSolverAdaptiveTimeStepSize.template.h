    /**
     * Alias for periodic boundary conditions.
     */
    static std::bitset<Dimensions> PeriodicBC;

    double getMinTimeStamp() const final;
    double getMaxTimeStamp() const final;
    double getMinTimeStepSize() const final;
    double getMaxTimeStepSize() const final;
    
    


    /**
     * @param Q Vector of unknowns
     * @param t Time
     */
    virtual ::exahype2::RefinementCommand refinementCriterion(
      const double * __restrict__ Q, // Q[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}],
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t
    ) {% if REFINEMENT_CRITERION_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final {% endif %};


    /**
     * Feel free to change the solution in the particular finite volume.
     * You can for example change the initial conditions by overwriting
     * the solution for t=0. You may change Q. All other parameters are
     * in.
     *
     * @param gridIsConstructred The initial condition is used while we
     *   create the grid to identify regions where the adaptivity
     *   criterion kicks in. One the grid is however fully constructed
     *   and does not change anymore, the initial condition is once more
     *   set with this parameter being true.
     */
    virtual void initialCondition(
      double * __restrict__ Q,
      const tarch::la::Vector<Dimensions,double>&  volumeCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      bool                                         gridIsConstructred
    ) {% if INITIAL_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final {% endif %};


    /**
     * Apply boundary conditions. You can overwrite both the inside and
     * outside values though most BCs only modify the outside ones. Please
     * note that the boundary conditions you set here are after that subject
     * to the Riemann solver, i.e. flux and eigenvalues.
     */
    virtual void boundaryConditions(
      const double * __restrict__ Qinside, // Qinside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      double * __restrict__ Qoutside, // Qoutside[{{NUMBER_OF_UNKNOWNS}}+{{NUMBER_OF_AUXILIARY_VARIABLES}}]
      const tarch::la::Vector<Dimensions,double>&  faceCentre,
      const tarch::la::Vector<Dimensions,double>&  volumeH,
      double                                       t,
      int                                          normal
    ) {% if BOUNDARY_CONDITIONS_IMPLEMENTATION=="<user-defined>" %}= 0{% else %} final{% endif %};




    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startGridConstructionStep() override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishGridConstructionStep() override;



    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startGridInitialisationStep() override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishGridInitialisationStep() override;




    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startTimeStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    ) override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishTimeStep() override;


    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void startPlottingStep(
      double globalMinTimeStamp,
      double globalMaxTimeStamp,
      double globalMinTimeStepSize,
      double globalMaxTimeStepSize
    ) override;

    /**
     * If you hook into this routine, ensure the abstract base class
     * operation is still invoked.
     */
    void finishPlottingStep() override;


    double getMaxMeshSize() const override;
    double getMinMeshSize() const override;
    
    /**
     * Inform about maximum eigenvalue of a patch
     *
     * The routine automatically computes the admissible time step size 
     * for the next time step. Is to be called per patch from the solver.
     *
     *
     * This operation is thread-safe.
     */
    void setMaximumEigenvalue( double value );

    SolverState  getSolverState() const;
    #if defined(OpenMPGPUOffloading)
    #pragma omp declare target
    #endif
    static constexpr int    NumberOfUnknowns           = {{NUMBER_OF_UNKNOWNS}};
    static constexpr int    NumberOfAuxiliaryVariables = {{NUMBER_OF_AUXILIARY_VARIABLES}};
    {{SOLVER_CONSTANTS}}
    #if defined(OpenMPGPUOffloading)
    #pragma omp end declare target
    #endif

  protected:
    static tarch::logging::Log                  _log;
    static tarch::multicore::BooleanSemaphore   _sempahore;

    const int     _NumberOfFiniteVolumesPerAxisPerPatch;

    double     _timeStamp;
    double     _timeStepSize;
    double     _admissibleTimeStepSize;

    SolverState  _solverState;

    double     _maxH;
    double     _minH;

