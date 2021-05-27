import os
import argparse

import peano4
import exahype2

import peano4.toolbox.particles
import dastgen2

modes = { 
  "release": peano4.output.CompileMode.Release,
  "trace":   peano4.output.CompileMode.Trace,
  "assert":  peano4.output.CompileMode.Asserts, "stats":  peano4.output.CompileMode.Stats,
  "debug":   peano4.output.CompileMode.Debug,
}

floatparams = {
        "GLMc0":1.5, "GLMc":1.2, "GLMd":2.0, "GLMepsA":1.0, "GLMepsP":1.0,
        "GLMepsD":1.0, 
	#"itau":1.0, "k1":0.0, "k2":0.0, "k3":0.0, "eta":0.0,
        #"f":0.0, "g":0.0, "xi":0.0, "e":1.0, "c":1.0, "mu":0.2, "ds":1.0,
        #"sk":0.0, "bs":0.0#, \
	"itau":1.0, "k1":0.1, "k2":0.0, "k3":0.5, "eta":1.0,
        "f":1.0, "g":0.0, "xi":1.0, "e":1.0, "c":1.0, "mu":0.2, "ds":1.0,
        "sk":1.0, "bs":1.0#, \
	#"par_b":666.0, "center_offset_x":-1.0, "center_offset_y":0.0, "center_offset_z":0.0, \
	#"target_m_plus":1.0, "par_p_plus_x":0.0, "par_p_plus_y":0.0, "par_p_plus_z":0.0, \
	#"par_s_plus_x":0.0, "par_s_plus_y":0.0, "par_s_plus_z":0.0, \
	#"target_m_minus":1.0, "par_p_minus_x":0.0, "par_p_minus_y":0.0, "par_p_minus_z":0.0, \
	#"par_s_minus_x":0.0, "par_s_minus_y":0.0, "par_s_minus_z":0.0, \
	#"tp_epsilon":1e-6
}

intparams = {"LapseType":0, "tp_grid_setup":0}

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='ExaHyPE 2 - CCZ4 script')
    parser.add_argument("-cs",   "--cell-size",       dest="max_h",           type=float, default=0.4,  help="Mesh size" )
    parser.add_argument("-ps",   "--patch-size",      dest="patch_size",      type=int, default=6,    help="Patch size, i.e. number of volumes per cell per direction" )
    parser.add_argument("-plt",  "--plot-step-size",  dest="plot_step_size",  type=float, default=0.04, help="Plot step size (0 to switch it off)" )
    parser.add_argument("-m",    "--mode",            dest="mode",            default="release",  help="|".join(modes.keys()) )
    parser.add_argument("-ext",  "--extension",       dest="extension",       choices=["none", "gradient", "adm", "PTadm"],   default="none",  help="Pick extension, i.e. what should be plotted on top. Default is none" )
    parser.add_argument("-impl", "--implementation",  dest="implementation",  choices=["ader-fixed", "fv-fixed", "fv-fixed-enclave", "fv-adaptive" ,"fv-adaptive-enclave", "fv-optimistic-enclave", "fv-fixed-gpu"], required="True",  help="Pick solver type" )
    parser.add_argument("-no-pbc",  "--no-periodic-boundary-conditions",      dest="periodic_bc", action="store_false", default="True",  help="switch on or off the periodic BC" )
    parser.add_argument("-et",   "--end-time",        dest="end_time",        type=float, default=1.0, help="End (terminal) time" )
    parser.add_argument("-s",    "--scenario",        dest="scenario",        choices=["gauge", "linear", "two-punctures"], required="True", help="Scenario" )


    for k, v in floatparams.items(): parser.add_argument("--{}".format(k), dest="CCZ4{}".format(k), type=float, default=v, help="default: %(default)s")
    for k, v in intparams.items():   parser.add_argument("--{}".format(k), dest="CCZ4{}".format(k), type=int, default=v, help="default: %(default)s")

    args = parser.parse_args()

    SuperClass = None
    
    if args.implementation=="fv-fixed":
       SuperClass = exahype2.solvers.fv.GenericRusanovFixedTimeStepSize
    if args.implementation=="fv-fixed-enclave":
       SuperClass = exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithEnclaves
    if args.implementation=="fv-adaptive":
       SuperClass = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSize
    if args.implementation=="fv-adaptive-enclave":
       SuperClass = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves
    if args.implementation=="fv-optimistic-enclave":
       SuperClass = exahype2.solvers.fv.GenericRusanovOptimisticTimeStepSizeWithEnclaves
    if args.implementation=="ader-fixed":
       SuperClass = exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize
    if args.implementation=="fv-fixed-gpu":
       SuperClass = exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithAccelerator

    class CCZ4Solver( SuperClass ):
      def __init__(self, name, patch_size, min_h, max_h ):
        unknowns = {
          "G":6,
          "K":6,
          "theta":1,
          "Z":3,
          "lapse":1,
          "shift":3,
          "b":3,
          "dLapse":3,
          "dxShift":3,
          "dyShift":3,
          "dzShift":3,
          "dxG":6,
          "dyG":6,
          "dzG":6,
          "traceK":1,
          "phi":1,
          "P":3,
          "K0":1,
        }

        number_of_unknowns = sum(unknowns.values())

        if SuperClass==exahype2.solvers.fv.GenericRusanovFixedTimeStepSize or \
           SuperClass==exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithAccelerator or \
           SuperClass==exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithEnclaves:
          SuperClass.__init__(
            self,
            name=name, patch_size=patch_size,
            unknowns=number_of_unknowns,
            auxiliary_variables=0,
            min_h=min_h, max_h=max_h,
            time_step_size=1e-2
          )
        else:
          SuperClass.__init__(
            self,
            name=name, patch_size=patch_size,
            unknowns=number_of_unknowns,
            auxiliary_variables=0,
            min_h=min_h, max_h=max_h,
            time_step_relaxation=0.05
          )

        self._solver_template_file_class_name = SuperClass.__name__

        #pde = exahype2.sympy.PDE(unknowns=self._unknowns,auxiliary_variables=self._auxiliary_variables,dimensions=3)

        self.set_implementation(
          boundary_conditions=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
          flux=exahype2.solvers.fv.PDETerms.None_Implementation,
          ncp=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
          source_term=exahype2.solvers.fv.PDETerms.User_Defined_Implementation
        )

      def get_user_includes(self):
        """
         We take this routine to add a few additional include statements.
        """
        return SuperClass.get_user_includes(self) + """
    #include "../CCZ4Kernels.h"
    #include "exahype2/PatchUtils.h"
    """


      def add_constraint_verification(self):
        """

         Add the constraint verification code

         We introduce new auxiliary variables. Prior to each time step, I
         compute the Laplacian and store it in the auxiliary variable. This
         is kind of a material parameter F(Q) which does not feed back into
         the solution.

         Changing the number of unknowns a posteriori is a delicate update
         to the solver, so we invoke the constructor again to be on the safe
         side.

        """
        self._auxiliary_variables = 6

        self.additional_includes += """
    #include "../CCZ4Kernels.h"
    """


        self.set_preprocess_reconstructed_patch_kernel( """
        const int patchSize = """ + str( self._patch.dim[0] ) + """;
        double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
        const int n_a_v=6;
        dfor(cell,patchSize) {
          tarch::la::Vector<Dimensions,int> currentCell = cell + tarch::la::Vector<Dimensions,int>(1);

          // This constraint routine will evaluate both the solution per voxel
          // plus the derivative. The latter is something that we don't have, i.e.
          // we have to reconstruct it manually.

          // See the docu in PDE.h
          double gradQ[3*59]={ 0 };

          // Lets look left vs right and compute the gradient. Then, lets
          // loop up and down. So we look three times for the respective
          // directional gradients
          for (int d=0; d<3; d++) {
            tarch::la::Vector<Dimensions,int> leftCell  = currentCell;
            tarch::la::Vector<Dimensions,int> rightCell = currentCell;
            leftCell(d)  -= 1;
            rightCell(d) += 1;
            const int leftCellSerialised  = peano4::utils::dLinearised(leftCell, patchSize + 2*1);
            const int rightCellSerialised = peano4::utils::dLinearised(rightCell,patchSize + 2*1);
            for(int i=0; i<59; i++) {
              gradQ[d*59+i] = ( reconstructedPatch[rightCellSerialised*(59+n_a_v)+i] - reconstructedPatch[leftCellSerialised*(59+n_a_v)+i] ) / 2.0 / volumeH;
            }
          }

          // We will use a Fortran routine to compute the constraints per
          // Finite Volume
          double constraints[n_a_v]={ 0 };

          // Central cell
          const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);

          admconstraints(constraints,reconstructedPatch+cellSerialised*(59+n_a_v),gradQ);

          for(int i=0;i<n_a_v;i++){
            reconstructedPatch[cellSerialised*(59+n_a_v)+59+i] = constraints[i];
          }
        }
    """)

        self.create_data_structures()
        self.create_action_sets()


      def add_derivative_calculation(self):
        """

         Add the constraint verification code

         We introduce new auxiliary variables. Prior to each time step, I
         compute the Laplacian and store it in the auxiliary variable. This
         is kind of a material parameter F(Q) which does not feed back into
         the solution.

         Changing the number of unknowns a posteriori is a delicate update
         to the solver, so we invoke the constructor again to be on the safe
         side.

        """
        self._auxiliary_variables = 59*3

        self.set_preprocess_reconstructed_patch_kernel( """
        const int patchSize = """ + str( self._patch.dim[0] ) + """;
        double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
        dfor(cell,patchSize) {
          tarch::la::Vector<Dimensions,int> currentCell = cell + tarch::la::Vector<Dimensions,int>(1);
          const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);

          // Lets look left vs right and compute the gradient. Then, lets
          // loop up and down. So we look three times for the respective
          // directional gradients
          for (int d=0; d<3; d++) {
            tarch::la::Vector<Dimensions,int> leftCell  = currentCell;
            tarch::la::Vector<Dimensions,int> rightCell = currentCell;
            leftCell(d)  -= 1;
            rightCell(d) += 1;
            const int leftCellSerialised  = peano4::utils::dLinearised(leftCell, patchSize + 2*1);
            const int rightCellSerialised = peano4::utils::dLinearised(rightCell,patchSize + 2*1);
            for (int i=0; i<59; i++) {
              reconstructedPatch[cellSerialised*(59*4)+59+i*3+d] =
                ( reconstructedPatch[rightCellSerialised*(59*4)+i] - reconstructedPatch[leftCellSerialised*(59*4)+i] ) / 2.0 / volumeH;
            }
          }
        }
    """)

        self.create_data_structures()
        self.create_action_sets()

      def add_PunctureTracker_Lconstraintwriter(self):
        """
        """
        self._auxiliary_variables = 6
        
        self.additional_includes += """
	#include "../libtwopunctures/TP_PunctureTracker.h"
	#include "../CCZ4Kernels.h"
    """

        self.set_preprocess_reconstructed_patch_kernel( """
        const int patchSize = """ + str( self._patch.dim[0] ) + """;
        double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
        
		std::fstream fin;
		std::string att="_re10.txt"; std::string p1="puncture1"; std::string p2="puncture2"; std::string tem="ztem";

		if (tarch::la::equals(t,0.0)){//initialization
			fin.open((p1+att),std::ios::out|std::ios::trunc);
			fin << "4.251 0.0 0.0 0.0" << std::endl;//4.461538
			fin.close();
			fin.open((p2+att),std::ios::out|std::ios::trunc);
			fin << "-4.251 0.0 0.0 0.0" << std::endl;//-5.538462
			fin.close();
			fin.open((tem+att),std::ios::out|std::ios::trunc);
			fin << "tem file" << std::endl;
			fin.close();		 
		} else {
			fin.open((p1+att),std::ios::in);
			std::string pos=getLastLine(fin);
			fin.close();
			double coor1[4]={0};//read in previous coordinates
			CoorReadIn(coor1,pos);
			fin.open((p2+att),std::ios::in);
			std::string pos2=getLastLine(fin);
			fin.close();
			double coor2[4]={0};
			CoorReadIn(coor2,pos2);
			if (marker.isContained(coor1)){
				tarch::la::Vector<Dimensions*2,int> IndexOfCell=FindCellIndex(coor1,marker.getOffset(),volumeH,patchSize); //find where the puncture is
				tarch::la::Vector<Dimensions,int> IndexForInterpolate[8];
				FindInterIndex(IndexForInterpolate,IndexOfCell);//find the closest 8 cells
				double raw[8*3];
				for (int i=0;i<8;i++){
					int Lindex=peano4::utils::dLinearised(IndexForInterpolate[i], patchSize + 2*1);
					for (int j=0;j<Dimensions;j++) {raw[i*3+j]=reconstructedPatch[Lindex*(59+6)+17+j];} //read in corresponding beta
				}
				double shift[3];
				Interpolation(shift,IndexForInterpolate,raw,coor1,marker.getOffset(),volumeH,patchSize);
				
				coor1[0]-=dt*shift[0]; coor1[1]-=dt*shift[1]; coor1[2]-=dt*shift[2];//updates position
				fin.open((p1+att),std::ios::app);//output
				fin << coor1[0] << " " << coor1[1] << " " << coor1[2] << " " << t << std::endl;
				fin.close();
				fin.open((tem+att),std::ios::app);
				fin << "for cellindex" << IndexOfCell(0) << " " << IndexOfCell(1) << " " << IndexOfCell(2) << " " << IndexOfCell(3) << " " << IndexOfCell(4) << " " << IndexOfCell(5) << std::endl;
				for (int i=0;i<8;i++){
				fin << IndexForInterpolate[i](0) << " " << IndexForInterpolate[i](1) << " " << IndexForInterpolate[i](2) << std::endl;
				fin << raw[i*3+0] << " " << raw[i*3+1] << " " << raw[i*3+2] << std::endl;
				}
				fin << "after inter" << shift[0] << " " << shift[1] << " " << shift[2] << " " << t << std::endl;
				fin.close();
			}
			if (marker.isContained(coor2)){//do the same for the second puncutre
				tarch::la::Vector<Dimensions*2,int> IndexOfCell=FindCellIndex(coor2,marker.getOffset(),volumeH,patchSize);
				tarch::la::Vector<Dimensions,int> IndexForInterpolate[8];
				FindInterIndex(IndexForInterpolate,IndexOfCell);
				double raw[8*3];
				for (int i=0;i<8;i++){
					int Lindex=peano4::utils::dLinearised(IndexForInterpolate[i], patchSize + 2*1);
					for (int j=0;j<Dimensions;j++) {raw[i*3+j]=reconstructedPatch[Lindex*(59+6)+17+j];}
				}
				double shift[3];
				Interpolation(shift,IndexForInterpolate,raw,coor2,marker.getOffset(),volumeH,patchSize);
				
				coor2[0]-=dt*shift[0]; coor2[1]-=dt*shift[1]; coor2[2]-=dt*shift[2];
				fin.open((p2+att),std::ios::app);
				fin << coor2[0] << " " << coor2[1] << " " << coor2[2] << " " << t << std::endl;
				fin.close();
			}
		}
		
		const int n_a_v=6;
		std::string l2="L2_constri"; std::string teml2="ztem_constri";
		double cons[6]={0,0,0,0,0,0};
        dfor(cell,patchSize) {
        	tarch::la::Vector<Dimensions,int> currentCell = cell + tarch::la::Vector<Dimensions,int>(1);

			double gradQ[3*59]={ 0 };

			for (int d=0; d<3; d++) {
				tarch::la::Vector<Dimensions,int> leftCell  = currentCell;
				tarch::la::Vector<Dimensions,int> rightCell = currentCell;
				leftCell(d)  -= 1;
				rightCell(d) += 1;
				const int leftCellSerialised  = peano4::utils::dLinearised(leftCell, patchSize + 2*1);
				const int rightCellSerialised = peano4::utils::dLinearised(rightCell,patchSize + 2*1);
				for(int i=0; i<59; i++) {
					gradQ[d*59+i] = ( reconstructedPatch[rightCellSerialised*(59+n_a_v)+i] - reconstructedPatch[leftCellSerialised*(59+n_a_v)+i] ) / 2.0 / volumeH;
				}
			}
			double constraints[n_a_v]={ 0 };
			const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);

			admconstraints(constraints,reconstructedPatch+cellSerialised*(59+n_a_v),gradQ);

			for(int i=0;i<n_a_v;i++){
				reconstructedPatch[cellSerialised*(59+n_a_v)+59+i] = constraints[i];
				cons[i]+=constraints[i]*constraints[i];
			}
		}
		/*
		for(int i=0;i<n_a_v;i++){cons[i]=cons[i]/(patchSize*patchSize*patchSize);}

		//if (marker.isContained({0,0,0})){	
			if (tarch::la::equals(t,0.0)){
				fin.open((teml2+att),std::ios::out|std::ios::trunc);
				fin << "0 0.0 0.0 0.0 0.0 0.0 0.0" << std::endl;//time, 6 constrinats L2
				fin.close();
				fin.open((l2+att),std::ios::out|std::ios::trunc);
				fin << "0 0.0 0.0 0.0 0.0 0.0 0.0" << std::endl;//time, 6 constrinats L2
				fin.close();
			} else {
				fin.open((teml2+att),std::ios::in);
				std::string checkingline=getLastLine(fin);
				fin.close();
				double checkingcons[7]={0};
				ConsReadIn(checkingcons,checkingline);
				if (std::abs(t-checkingcons[0])<(dt/100.0)){ //if they are stil in the same timestep
					fin.open((teml2+att),std::ios::app);
					fin << t << " " <<cons[0] << " " <<cons[1] << " " <<cons[2] << " " <<cons[3] << " " <<cons[4] << " " <<cons[5] << std::endl;
					fin.close();
				} else {
					//std::cout << "current t " << t << " file t " << checkingcons[0] << std::endl;
					fin.open((teml2+att),std::ios::in);
					int count=0; std::string line; double consOutput[6]={0,0,0,0,0,0};
					while (std::getline(fin,line)){
						count++;
						double constem[7]={0};
						ConsReadIn(constem,line);
						for(int i=1;i<(n_a_v+1);i++){consOutput[i-1]+=constem[i];}
					}
					for(int i=0;i<n_a_v;i++){consOutput[i]/=count;}
					fin.close();
					fin.open((l2+att),std::ios::app);
					fin << t << " " <<consOutput[0] << " " <<consOutput[1] << " " <<consOutput[2] << " " <<consOutput[3] << " " <<consOutput[4] << " " <<consOutput[5] << std::endl;
					fin.close();
					fin.open((teml2+att),std::ios::out|std::ios::trunc);
					fin << t << " " <<cons[0] << " " <<cons[1] << " " <<cons[2] << " " <<cons[3] << " " <<cons[4] << " " <<cons[5] << std::endl;
					fin.close();
				}
			}
		//}
		*/				
    """)

        self.create_data_structures()
        self.create_action_sets()
       


      def pick_Gauge_wave_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=0; /* Gauge wave */  """ )

      def pick_Linear_wave_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=1; /* Linear wave */  """ )

      def pick_two_puncture_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=2; /* Two-puncture */  """ )


    userwarnings = []

    project = exahype2.Project( ["examples", "exahype2", "ccz4"], "ccz4" )

    is_aderdg = False
    solver_name = "CCZ4"
    try:
      if SuperClass==exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize:
        is_aderdg = True
        order = 3
        unknowns = 59
        time_step_size = 0.001
    except Exception as e:
        msg = "Warning: ADER-DG no supported on this machine"
        print(msg)
        userwarnings.append((msg,e))

    if is_aderdg:
      solver_name    = "ADERDG" + solver_name
    else:
      solver_name    = "FiniteVolume" + solver_name

    if SuperClass == exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithAccelerator:
      solver_name += "OnGPU"

    if is_aderdg:
      my_solver = exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize(
          solver_name, order, unknowns, 0, #auxiliary_variables
          exahype2.solvers.aderdg.Polynomials.Gauss_Legendre,
          args.max_h, args.max_h, time_step_size,
          flux = None,
          ncp  = exahype2.solvers.aderdg.PDETerms.User_Defined_Implementation,
          sources = exahype2.solvers.aderdg.PDETerms.User_Defined_Implementation
      )
    else:
      my_solver = CCZ4Solver(solver_name, args.patch_size, args.max_h, args.max_h)

      if args.extension=="gradient":
        my_solver.add_derivative_calculation()
      if args.extension=="adm":
        my_solver.add_constraint_verification()
      if args.extension=="PTadm":
        my_solver.add_PunctureTracker_Lconstraintwriter()

    solverconstants=""
    for k, v in floatparams.items(): solverconstants+= "static constexpr double {} = {};\n".format("CCZ4{}".format(k), eval('args.CCZ4{}'.format(k)))
    for k, v in intparams.items():   solverconstants+= "static constexpr int {} = {};\n".format("CCZ4{}".format(k), eval('args.CCZ4{}'.format(k)))
    my_solver.set_solver_constants(solverconstants)

    if args.scenario=="gauge":
      my_solver.pick_Gauge_wave_scenario()
    elif args.scenario=="linear":
      my_solver.pick_Linear_wave_scenario()
    elif args.scenario=="two-punctures":
      my_solver.pick_two_puncture_scenario()
    else:
      raise Exception( "Scenario " + args.scenario + " is now known")        

    project.add_solver(my_solver)


    build_mode = modes[args.mode]
    
    dimensions = 3

    if args.periodic_bc:
      print( "Periodic BC set")
      periodic_boundary_conditions = [True,True,True]          # Periodic BC
    else:
      msg = "WARNING: Periodic BC deactivated"
      print(msg)
      periodic_boundary_conditions = [False,False,False]
      userwarnings.append((msg,None))

    project.set_global_simulation_parameters(
      dimensions,               # dimensions
      #[-20, -20, -20],  [40.0, 40.0, 40.0],
      #[-30, -30, -30],  [60.0, 60.0, 60.0],
      #[-40, -40, -40],  [80.0, 80.0, 80.0],
      [-0.5, -0.5, -0.5],  [1.0, 1.0, 1.0],
      args.end_time,                 # end time
      1110.0, args.plot_step_size,   # snapshots
      periodic_boundary_conditions,
      8  # plotter precision
    )

    project.set_Peano4_installation("../../..", build_mode)

    #project.set_output_path( "/cosma6/data/dp004/dc-zhan3/exahype2/bbh-fv2" )
    probe_point = [-5,-5,-5]
    project.add_plot_filter( probe_point,[10.0,10.0,10.0],1 )

    project.set_load_balancing("toolbox::loadbalancing::RecursiveSubdivision")

    #add tracer
    #tracer_particles = project.add_tracer( name="MyTracer",attribute_count=1 )
    #project.add_action_set_to_timestepping(exahype2.tracer.FiniteVolumesTracing(tracer_particles,my_solver,[17,18,19],[16],-1,time_stepping_kernel="toolbox::particles::explicitEulerWithoutInterpolation"))
    #project.add_action_set_to_timestepping(exahype2.tracer.FiniteVolumesTracing(tracer_particles,my_solver,[17,18,19],[16],-1,time_stepping_kernel="toolbox::particles::LinearInterp"))
    #project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesAlongCartesianMesh( particle_set=tracer_particles, h=args.max_h/8.0, noise=True ))
    #project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesbyCoor( particle_set=tracer_particles,p1=[0.1,0,0],p2=[-0.1,0,0]))

    peano4_project = project.generate_Peano4_project(verbose=True)

    if args.scenario=="gauge":
      pass
    elif args.scenario=="linear":
      pass
    elif args.scenario=="two-punctures":
      #
      # There are two different things to do when we pick a scneario: We have
      # to configure the solver accordingly (and keep in mind that every solver
      # needs its own config), and then we might have to adopt the build 
      # environment.
      #
      peano4_project.output.makefile.add_linker_flag( "-lm -L/cosma/local/gsl/2.4/lib -lgsl -L/cosma/local/gsl/2.4/lib -lgslcblas" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/TP_Utilities.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/TP_Parameters.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/TP_Logging.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/TwoPunctures.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/CoordTransf.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/Equations.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/FuncAndJacobian.cpp" )
      peano4_project.output.makefile.add_cpp_file( "libtwopunctures/Newton.cpp" )
      peano4_project.output.makefile.add_CXX_flag( "-DIncludeTwoPunctures" )
    else:
      raise Exception( "Scenario " + args.scenario + " is now known")        

    peano4_project.output.makefile.add_CXX_flag( "-DCCZ4EINSTEIN" )
    peano4_project.output.makefile.add_cpp_file( "InitialValues.cpp" )
    peano4_project.output.makefile.add_cpp_file( "CCZ4Kernels.cpp" )

    # NOTE these lines are required to build with the fortran routines --- this will also require to uncomment some
    # includes etc
    #
    # peano4_project.output.makefile.add_Fortran_flag( "-DCCZ4EINSTEIN -DDim3" )
    # peano4_project.output.makefile.add_Fortran_flag( "-lstdc++ -fdefault-real-8 -fdefault-double-8 -cpp -std=legacy -ffree-line-length-512 -fPIC" )
    # peano4_project.output.makefile.add_CXX_flag( "-fPIE -DCCZ4EINSTEIN" )
    # peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC -lgfortran" )
    # peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC -L/usr/lib/x86_64-linux-gnu -lgfortran" )

    # This might work for Intel (not tested)
    #peano4_project.output.makefile.add_Fortran_flag( "-r8 -cpp -auto -qopenmp-simd -O2" )
    #peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC" )
    # you might need -lifcore

    # peano4_project.output.makefile.add_Fortran_module( "MainVariables.f90" )

    # peano4_project.output.makefile.add_Fortran_files(
      # ["PDE.f90 ", "EinsteinConstraints.f90 ", "Properties.f90","ADMConstraints.f90"]
    # )


    # peano4_project.constants.export_string( "Scenario", "gaugewave-c++" )
    # peano4_project.constants.add_target_begin()
    # for k, v in floatparams.items(): peano4_project.constants.export_constexpr_with_type("CCZ4{}".format(k), eval('args.CCZ4{}'.format(k)), "double")
    # peano4_project.constants.add_target_end()
    # peano4_project.constants.add_target_begin()
    # for k, v in intparams.items():   peano4_project.constants.export_constexpr_with_type("CCZ4{}".format(k), eval('args.CCZ4{}'.format(k)), "int")
    # peano4_project.constants.add_target_end()
    # project.export_const_with_type("NumberOfUnknowns", 59, "int")
    #peano4_project.constants.export_string( "Scenario", "linearwave-c++" )

    peano4_project.generate( throw_away_data_after_generation=False )

    peano4_project.build( make_clean_first = True )

    # Remind the user of warnings!
    if len(userwarnings) >0:
        print("Please note that these warning occured before the build:")
        for msg, exception in userwarnings:
            if exception is None:
                print(msg)
            else: print(msg, "Exception: {}".format(exception))
