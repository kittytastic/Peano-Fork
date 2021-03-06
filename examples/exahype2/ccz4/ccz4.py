import os
import argparse

import peano4
import exahype2

import peano4.toolbox.particles
import dastgen2

from Probe_file_gene import tracer_seeds_generate

from peano4.toolbox.blockstructured.DynamicAMR                 import DynamicAMR


modes = { 
  "release": peano4.output.CompileMode.Release,
  "trace":   peano4.output.CompileMode.Trace,
  "assert":  peano4.output.CompileMode.Asserts, "stats":  peano4.output.CompileMode.Stats,
  "debug":   peano4.output.CompileMode.Debug,
}

floatparams = {
        "GLMc0":1.5, "GLMc":1.2, "GLMd":2.0, "GLMepsA":1.0, "GLMepsP":1.0,
        "GLMepsD":1.0, 
	"itau":1.0, "k1":0.1, "k2":0.0, "k3":0.5, "eta":1.0,
        "f":0.75, "g":0.0, "xi":1.0, "e":1.0, "c":1.0, "mu":0.2, "ds":1.0,
        "sk":1.0, "bs":1.0#, \
	#"itau":1.0, "k1":0.1, "k2":0.0, "k3":0.5, "eta":1.0,
        #"f":1.0, "g":0.0, "xi":1.0, "e":1.0, "c":1.0, "mu":0.2, "ds":1.0,
        #"sk":1.0, "bs":1.0#, \
	#"par_b":666.0, "center_offset_x":-1.0, "center_offset_y":0.0, "center_offset_z":0.0, \
	#"target_m_plus":1.0, "par_p_plus_x":0.0, "par_p_plus_y":0.0, "par_p_plus_z":0.0, \
	#"par_s_plus_x":0.0, "par_s_plus_y":0.0, "par_s_plus_z":0.0, \
	#"target_m_minus":1.0, "par_p_minus_x":0.0, "par_p_minus_y":0.0, "par_p_minus_z":0.0, \
	#"par_s_minus_x":0.0, "par_s_minus_y":0.0, "par_s_minus_z":0.0, \
	#"tp_epsilon":1e-6
}

intparams = {"LapseType":1, "tp_grid_setup":0, "swi":99, "ReSwi":0, "source":0}

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='ExaHyPE 2 - CCZ4 script')
    parser.add_argument("-maxh",   "--max-h",       dest="max_h",           type=float, required="True",  help="upper limit for refinement. Refers to volume size, i.e. not to patch size" )
    parser.add_argument("-minh",   "--min-h",       dest="min_h",           type=float, default=0,  help="lower limit for refinement (set to 0 to make it equal to max_h - default). Refers to volume size, i.e. not to patch size" )
    parser.add_argument("-ps",   "--patch-size",      dest="patch_size",      type=int, default=6,    help="Patch size, i.e. number of volumes per patch per direction" )
    parser.add_argument("-plt",  "--plot-step-size",  dest="plot_step_size",  type=float, default=0.04, help="Plot step size (0 to switch it off)" )
    parser.add_argument("-m",    "--mode",            dest="mode",            default="release",  help="|".join(modes.keys()) )
    parser.add_argument( "--gpu",            dest="GPU",            default=False, action="store_true",  help="Run with accelerator support" )
    parser.add_argument("-ext",  "--extension",       dest="extension",       choices=["none", "gradient", "AMRadm", "Full"],   default="none",  help="Pick extension, i.e. what should be plotted on top. Default is none" )
    parser.add_argument("-impl", "--implementation",  dest="implementation",  choices=["fv-global-fixed", "fv-global-adaptive", "fv-global-fixed-enclave", "fv-global-adaptive-enclave"], required="True",  help="Pick solver type" )
    #parser.add_argument("-impl", "--implementation",  dest="implementation",  choices=["ader-fixed", "fv-fixed", "fv-fixed-enclave", "fv-adaptive" ,"fv-adaptive-enclave", "fv-optimistic-enclave", "fv-fixed-gpu", "fv-adaptive-gpu"], required="True",  help="Pick solver type" )
    parser.add_argument("-no-pbc",  "--no-periodic-boundary-conditions",      dest="periodic_bc", action="store_false", default="True",  help="switch on or off the periodic BC" )
    parser.add_argument("-et",   "--end-time",        dest="end_time",        type=float, default=1.0, help="End (terminal) time" )
    parser.add_argument("-s",    "--scenario",        dest="scenario",        choices=["gauge", "linear", "single-puncture","two-punctures"], required="True", help="Scenario" )
    parser.add_argument("-tracer", "--add-tracer",    dest="add_tracer", type=int, default=0,  help="Add tracers and specify the seeds. 0-switch off, 1-x axis, 2-xy plane, 3-over domain (evenly), 4-over domain(with noise option), 5-inserted by coordinate, 6-spherical surface(Gauss_Legendre_quadrature), 7-spherical surface(t-design)" )
    parser.add_argument("-tn", "--tracer-name",       dest="tra_name",    type=str, default="de",  help="name of output tracer file (temporary)" )
    parser.add_argument("-exn", "--exe-name",        dest="exe_name",    type=str, default="",  help="name of output executable file" )
    parser.add_argument("-outdir", "--output-directory",        dest="path",    type=str, default="./",  help="specify the output directory, include the patch file and tracer file" )
    parser.add_argument("-interp",   "--interpolation", dest="interpolation",     choices=["constant", "linear-slow", "linear-slow+enforce", "linear", "linear+enforce", "outflow" ], default="linear-slow",  help="interpolation scheme for AMR" )
    parser.add_argument("-restrict", "--restriction",   dest="restriction",       choices=["average", "inject", "average+enforce", "inject+enforce"], default="average",  help="restriction scheme for AMR" )


    for k, v in floatparams.items(): parser.add_argument("--{}".format(k), dest="CCZ4{}".format(k), type=float, default=v, help="default: %(default)s")
    for k, v in intparams.items():
      if k=="ReSwi":
        parser.add_argument("--{}".format(k), dest="CCZ4{}".format(k), type=int, default=v, help="default: %(default)s, choose refinement criterion, 0-no refinement, 1-radius based, 2-SBH phi gradient based, 3-BBH phi gradient based. Notice: 2 and 3 only work with -ext Full")
      else: parser.add_argument("--{}".format(k), dest="CCZ4{}".format(k), type=int, default=v, help="default: %(default)s")

    args = parser.parse_args()

    SuperClass = None

    if args.implementation=="fv-global-fixed":
       SuperClass = exahype2.solvers.fv.rusanov.GlobalFixedTimeStep
    if args.implementation=="fv-global-adaptive":
       SuperClass = exahype2.solvers.fv.rusanov.GlobalAdaptiveTimeStep
    if args.implementation=="fv-global-fixed-enclave":
       SuperClass = exahype2.solvers.fv.rusanov.GlobalFixedTimeStepWithEnclaveTasking
    if args.implementation=="fv-global-adaptive-enclave":
       SuperClass = exahype2.solvers.fv.rusanov.GlobalAdaptiveTimeStepWithEnclaveTasking


#    if args.implementation=="fv-fixed-enclave" or args.implementation=="fv-fixed-gpu":
#       SuperClass = exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithEnclaves
#    if args.implementation=="fv-adaptive-enclave" or args.implementation=="fv-adaptive-gpu":
#       SuperClass = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves
#    if args.implementation=="fv-optimistic-enclave":
#       SuperClass = exahype2.solvers.fv.GenericRusanovOptimisticTimeStepSizeWithEnclaves
#    if args.implementation=="ader-fixed":
#       SuperClass = exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize

    class CCZ4Solver( SuperClass ):
      def __init__(self, name, patch_size, min_volume_h, max_volume_h ):
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

        self._my_user_includes = """
#include "../CCZ4Kernels.h"
#include "exahype2/PatchUtils.h"
"""

        if SuperClass==exahype2.solvers.fv.rusanov.GlobalFixedTimeStep:
          SuperClass.__init__(
            self,
            name=name, patch_size=patch_size,
            unknowns=number_of_unknowns,
            auxiliary_variables=0,
            min_volume_h=min_volume_h, max_volume_h=max_volume_h,
            time_step_size=1e-2
          )
        elif SuperClass==exahype2.solvers.fv.rusanov.GlobalFixedTimeStepWithEnclaveTasking:
          SuperClass.__init__(
            self,
            name=name, patch_size=patch_size,
            unknowns=number_of_unknowns,
            auxiliary_variables=0,
            min_volume_h=min_volume_h, max_volume_h=max_volume_h,
            time_step_size=1e-2,
            use_gpu =args.GPU #=="fv-fixed-gpu" else False
          )
        else:
          SuperClass.__init__(
            self,
            name=name, patch_size=patch_size,
            unknowns=number_of_unknowns,
            auxiliary_variables=0,
            min_volume_h=min_volume_h, max_volume_h=max_volume_h,
            time_step_relaxation=0.5,
            #use_gpu =args.GPU #=="fv-fixed-gpu" else False
#                        use_gpu = True if args.implementation=="fv-adaptive-gpu" else False
          )

        self._patch_size = patch_size

        self.set_implementation(
          boundary_conditions=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
          flux=exahype2.solvers.fv.PDETerms.None_Implementation,
          ncp=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
          source_term=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
          refinement_criterion=exahype2.solvers.fv.PDETerms.User_Defined_Implementation
        )

        self.set_postprocess_updated_patch_kernel( """
  {
    #if Dimensions==2
    constexpr int itmax = {{NUMBER_OF_VOLUMES_PER_AXIS}} * {{NUMBER_OF_VOLUMES_PER_AXIS}};
    #endif

    #if Dimensions==3
    constexpr int itmax = {{NUMBER_OF_VOLUMES_PER_AXIS}} * {{NUMBER_OF_VOLUMES_PER_AXIS}} * {{NUMBER_OF_VOLUMES_PER_AXIS}};
    #endif

    int index = 0;
    for (int i=0;i<itmax;i++)
    {

    // dfor( volume, {{NUMBER_OF_VOLUMES_PER_AXIS}} ) {
      examples::exahype2::ccz4::enforceCCZ4constraints( targetPatch+index );
      index += {{NUMBER_OF_UNKNOWNS}} + {{NUMBER_OF_AUXILIARY_VARIABLES}};
    }
  }
""" )

   
      def create_action_sets(self):
        SuperClass.create_action_sets(self)

        self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.additional_includes += """ 
#include "../CCZ4Kernels.h"
            """
        self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_restriction_scheme( "averaging" )
        self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_interpolation_scheme( "linear" )

        if args.interpolation=="constant":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_interpolation_scheme( "piecewise_constant" )
          print( "Interpolation rule: piecewise_constant" )
        if args.interpolation=="linear-slow" or args.interpolation=="linear-slow+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_interpolation_scheme( "linear" )
          print( "Interpolation rule: linear interpolation without optimisation" )
        if args.interpolation=="linear" or args.interpolation=="linear+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_interpolation_scheme( "linear_precomputed_operators<" + str(self._patch_size) +">" )
          print( "Interpolation rule: optimised linear interpolation with patch size " + str(self._patch_size) )
        if args.interpolation=="outflow":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_interpolation_scheme( "outflow" )
          print( "Interpolation rule: outflow (from fine grid into coarse grid)" )

        if args.restriction=="average" or args.restriction=="average+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_restriction_scheme( "averaging" )
          print( "Restiction rule: averaging" )
        if args.restriction=="inject" or args.restriction=="inject+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_restriction_scheme( "inject" )
          print( "Restiction rule: injection" )
          
        if args.interpolation=="linear+enforce" or args.interpolation=="linear-slow+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_point_wise_postprocessing_of_interpolation( "examples::exahype2::ccz4::enforceCCZ4constraints(targetVolume)" )
        if args.restriction=="average+enforce" or args.restriction=="inject+enforce":
          self._action_set_couple_resolution_transitions_and_handle_dynamic_mesh_refinement.switch_point_wise_postprocessing_of_restriction( "examples::exahype2::ccz4::enforceCCZ4constraints(targetVolume)" )


      def get_user_action_set_includes(self):
        """
         We take this routine to add a few additional include statements.
        """
        return SuperClass.get_user_action_set_includes(self) + self._my_user_includes


      def add_constraint_RefinementFlag_verification(self):
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

        self._my_user_includes += """
	#include "../CCZ4Kernels.h"
	#include "../AbstractFiniteVolumeCCZ4.h"
    """

        self.set_preprocess_reconstructed_patch_kernel( """
        const int patchSize = """ + str( self._patch.dim[0] ) + """;
        double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
        const int n_a_v="""+str(self._auxiliary_variables)+""";
        dfor(cell,patchSize) {
          //tarch::la::Vector<Dimensions,int> currentPosition=marker.getOffset()+(cell+0.5)*volumeH;
          tarch::la::Vector<Dimensions,int> currentCell = cell + tarch::la::Vector<Dimensions,int>(1);
          double currentPosition[3];
          
          for (int d=0; d<3; d++) currentPosition[d]=marker.getOffset()(d)+(cell(d)+0.5)*volumeH;

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

          // Finite Volume
          double constraints[6]={ 0 };

          // Central cell
          const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);

          admconstraints(constraints,reconstructedPatch+cellSerialised*(59+n_a_v),gradQ);
          
          //NaN detector here/////////////////////////////////
          /*for(int i=0;i<59;i++){
            if ( std::isnan(reconstructedPatch[cellSerialised*(59+n_a_v)+i]) ) {
              ::exahype2::triggerNonCriticalAssertion( __FILE__, __LINE__, "[Quantity should no be NaN]", "NaN detected at t=" + std::to_string(t) + " for quantity "+std::to_string(i)+" at position ["+std::to_string(currentPosition[0])+", "+std::to_string(currentPosition[1])+", "+std::to_string(currentPosition[2])+"]");}
          }*/
          ///////////////////////////////////////////////////

          for(int i=0;i<6;i++){
            reconstructedPatch[cellSerialised*(59+n_a_v)+59+i] = constraints[i];
          }
          
          /*double sour[59]={ 0 };
          examples::exahype2::ccz4::source(sour,reconstructedPatch+cellSerialised*(59+n_a_v),0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.1, 0, 0.5);
          for(int i=0;i<59;i++){
            reconstructedPatch[cellSerialised*(59+n_a_v)+59+6+i] = sour[i];
          }*/

          /*
          //here we calculate the norm of conformal factor phi as the refinement condition
          double Phi = std::exp(reconstructedPatch[cellSerialised*(59+n_a_v)+54]);
          double P1  = reconstructedPatch[cellSerialised*(59+n_a_v)+55]*Phi;
          double P2  = reconstructedPatch[cellSerialised*(59+n_a_v)+56]*Phi;
          double P3  = reconstructedPatch[cellSerialised*(59+n_a_v)+57]*Phi;
          
          reconstructedPatch[cellSerialised*(59+n_a_v)+59+6]=pow((P1*P1+P2*P2+P3*P3),0.5);//gradient of phi
          
          double Psi4[2]={0,0};
          Psi4Calc(Psi4, reconstructedPatch+cellSerialised*(59+n_a_v), gradQ, currentPosition);
          reconstructedPatch[cellSerialised*(59+n_a_v)+59+7]=Psi4[0];//re part of psi4
		      reconstructedPatch[cellSerialised*(59+n_a_v)+59+8]=Psi4[1];//im part of psi4
		      */
		      //std::cout<< Psi4[0] << std::endl;
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
        int aux_var=""" + str( self._auxiliary_variables ) + """;
        int real_var=59;
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
            for (int i=0; i<real_var; i++) {
              reconstructedPatch[cellSerialised*(real_var+aux_var)+real_var+i*3+d] =
                ( reconstructedPatch[rightCellSerialised*(real_var+aux_var)+i] - reconstructedPatch[leftCellSerialised*(real_var+aux_var)+i] ) / 2.0 / volumeH;
              if (isnan(reconstructedPatch[cellSerialised*(real_var+aux_var)+real_var+i*3+d])) {std::cout <<reconstructedPatch[rightCellSerialised*(real_var+aux_var)+i]<<" "<< reconstructedPatch[leftCellSerialised*(real_var+aux_var)+i] << std::endl;}
            }

          }
        }
    """)

        self.create_data_structures()
        self.create_action_sets()

      def add_PT_ConsW_Psi4W_AMRFlag(self):
        """
				add puncutrestracker, constraints writer, psi4 writer, AMRflag(currently using gradient of phi)
        """
        self._auxiliary_variables = 9

        self._my_user_includes += """
	#include "../libtwopunctures/TP_PunctureTracker.h"
	#include "../CCZ4Kernels.h"
	#include <fstream>
	#include <iomanip>
    """

        self.set_preprocess_reconstructed_patch_kernel( """
        const int patchSize = """ + str( self._patch.dim[0] ) + """;
        double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);

		std::fstream fin;
		std::string att="_"""+args.tra_name+""".txt"; std::string p1="puncture1"; std::string p2="puncture2"; std::string tem="ztem";
		const int n_a_v=9;

		if (tarch::la::equals(t,0.0)){//initialization
			fin.open((p1+att),std::ios::out|std::ios::trunc);
			fin << "4.251 0.0 0.0 0.0 0.0" << std::endl;//4.461538
			fin.close();
			fin.open((p2+att),std::ios::out|std::ios::trunc);
			fin << "-4.251 0.0 0.0 0.0 0.0" << std::endl;//-5.538462
			fin.close();
			//fin.open((tem+att),std::ios::out|std::ios::trunc);
			//fin << "tem file" << std::endl;
			//fin.close();
		} else {
			fin.open((p1+att),std::ios::in);
			std::string pos=getLastLine(fin);
			fin.close();
			double coor1[5]={0};//read in previous coordinates
			CoorReadIn(coor1,pos);
			fin.open((p2+att),std::ios::in);
			std::string pos2=getLastLine(fin);
			fin.close();
			double coor2[5]={0};
			CoorReadIn(coor2,pos2);
			int inter_number=4;
			if (marker.isContained(coor1)){
				tarch::la::Vector<Dimensions*2,int> IndexOfCell=FindCellIndex(coor1,marker.getOffset(),volumeH,patchSize); //find where the puncture is
				tarch::la::Vector<Dimensions,int> IndexForInterpolate[8];
				FindInterIndex(IndexForInterpolate,IndexOfCell);//find the closest 8 cells
				double raw[8*inter_number];
				for (int i=0;i<8;i++){
					int Lindex=peano4::utils::dLinearised(IndexForInterpolate[i], patchSize + 2*1);
					for (int j=0;j<Dimensions;j++) {raw[i*inter_number+j]=reconstructedPatch[Lindex*(59+n_a_v)+17+j];} //read in corresponding beta
					raw[i*inter_number+3]=reconstructedPatch[Lindex*(59+n_a_v)+16];
				}
				double result[inter_number];
				Interpolation(result,IndexForInterpolate,raw,coor1,marker.getOffset(),volumeH,patchSize);
				
				coor1[0]-=dt*result[0]; coor1[1]-=dt*result[1]; coor1[2]-=dt*result[2];//updates position
				fin.open((p1+att),std::ios::app);//output
				fin << std::setprecision (17) << coor1[0] << " " << coor1[1];
				fin << " " << coor1[2] << " " << t << " " << std::exp(result[3]) << std::endl;
				fin.close();
				fin.open((tem+att),std::ios::app);
				fin << "for cellindex" << IndexOfCell(0) << " " << IndexOfCell(1) << " " << IndexOfCell(2) << " " << IndexOfCell(3) << " " << IndexOfCell(4) << " " << IndexOfCell(5) << std::endl;
				for (int i=0;i<8;i++){
				fin << IndexForInterpolate[i](0) << " " << IndexForInterpolate[i](1) << " " << IndexForInterpolate[i](2) << std::endl;
				fin << raw[i*inter_number+0] << " " << raw[i*inter_number+1] << " " << raw[i*inter_number+2] << std::endl;
				}

				fin << "after inter" << result[0] << " " << result[1] << " " << result[2] << " " << t << std::endl;
				fin.close();
			}
			if (marker.isContained(coor2)){//do the same for the second puncutre
				tarch::la::Vector<Dimensions*2,int> IndexOfCell=FindCellIndex(coor2,marker.getOffset(),volumeH,patchSize);
				tarch::la::Vector<Dimensions,int> IndexForInterpolate[8];
				FindInterIndex(IndexForInterpolate,IndexOfCell);
				double raw[8*inter_number];
				for (int i=0;i<8;i++){
					int Lindex=peano4::utils::dLinearised(IndexForInterpolate[i], patchSize + 2*1);
					for (int j=0;j<Dimensions;j++) {raw[i*inter_number+j]=reconstructedPatch[Lindex*(59+n_a_v)+17+j];}
					raw[i*inter_number+3]=reconstructedPatch[Lindex*(59+n_a_v)+16];
				}
				double result[inter_number];
				Interpolation(result,IndexForInterpolate,raw,coor2,marker.getOffset(),volumeH,patchSize);
				
				coor2[0]-=dt*result[0]; coor2[1]-=dt*result[1]; coor2[2]-=dt*result[2];
				fin.open((p2+att),std::ios::app);
				fin << std::setprecision (17) << coor2[0] << " " << coor2[1];
				fin << " " << coor2[2] << " " << t << " " << std::exp(result[3]) << std::endl;
				fin.close();
			}
		}
		
		//std::string l2="L2_constri"; std::string teml2="ztem_constri";
		double cons[7]={0,0,0,0,0,0,0};
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
			double constraints[n_a_v-1]={ 0 };
			const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);

			admconstraints(constraints,reconstructedPatch+cellSerialised*(59+n_a_v),gradQ);

			for(int i=0;i<6;i++){
				reconstructedPatch[cellSerialised*(59+n_a_v)+59+i] = constraints[i];
				cons[i]+=constraints[i]*constraints[i];
			}
      //here we calculate the norm of conformal factor phi as the refinement condition
      double Phi = std::exp(reconstructedPatch[cellSerialised*(59+n_a_v)+54]);
      double P1  = reconstructedPatch[cellSerialised*(59+n_a_v)+55]*Phi;
      double P2  = reconstructedPatch[cellSerialised*(59+n_a_v)+56]*Phi;
      double P3  = reconstructedPatch[cellSerialised*(59+n_a_v)+57]*Phi;
          
      reconstructedPatch[cellSerialised*(59+n_a_v)+59+6]=pow((P1*P1+P2*P2+P3*P3),0.5);
      
      double Psi4[2]={0,0};
      double currentPosition[3]; 
      for (int d=0; d<3; d++) currentPosition[d]=marker.getOffset()(d)+(cell(d)+0.5)*volumeH;
      Psi4Calc(Psi4, reconstructedPatch+cellSerialised*(59+n_a_v), gradQ, currentPosition);
      reconstructedPatch[cellSerialised*(59+n_a_v)+59+7]=Psi4[0];//re part of psi4
		  reconstructedPatch[cellSerialised*(59+n_a_v)+59+8]=Psi4[1];//im part of psi4
		}		
    """)

        self.create_data_structures()
        self.create_action_sets()
       


      def pick_Gauge_wave_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=0; /* Gauge wave */  """ )

      def pick_Linear_wave_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=1; /* Linear wave */  """ )

      def pick_two_puncture_scenario(self):
        self.add_solver_constants( """static constexpr int Scenario=2; /* Two-puncture */  """ )

########################################################################################
#main starts here
########################################################################################
    userinfo = []
    exe="peano4"
    
    if args.exe_name!="":
      exe += "_"
      exe += args.exe_name
    if not args.tra_name=="de":
      exe += "_" + args.tra_name
    project = exahype2.Project( ["examples", "exahype2", "ccz4"], "ccz4", executable=exe)

########################################################################################
#Pick solver
########################################################################################
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
        userinfo.append((msg,e))

    if is_aderdg:
      solver_name    = "ADERDG" + solver_name
    else:
      solver_name    = "FiniteVolume" + solver_name


    min_h = args.min_h
    if min_h <=0.0:
      print( "No minimal mesh size chosen. Set it to max mesh size (regular grid)" )
      min_h = args.max_h

    if is_aderdg:
      my_solver = exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize(
          solver_name, order, unknowns, 0, #auxiliary_variables
          exahype2.solvers.aderdg.Polynomials.Gauss_Legendre,
          min_h, args.max_h, time_step_size,
          flux = None,
          ncp  = exahype2.solvers.aderdg.PDETerms.User_Defined_Implementation,
          sources = exahype2.solvers.aderdg.PDETerms.User_Defined_Implementation
      )
    else:
      my_solver = CCZ4Solver(solver_name, args.patch_size, min_h, args.max_h)

########################################################################################
#Add postpocessing function
########################################################################################
      if args.extension=="gradient":
        my_solver.add_derivative_calculation()
      if args.extension=="AMRadm":
        my_solver.add_constraint_RefinementFlag_verification()
      if args.extension=="Full":
        my_solver.add_PT_ConsW_Psi4W_AMRFlag()

########################################################################################
#parameter setting according to scenarios
########################################################################################
    if args.scenario=="two-punctures":
      msg = "Periodic BC deactivated because you pick Puncture scenario\nInitialize binary black holes"
      print(msg)
      periodic_boundary_conditions = [False,False,False]
      intparams.update({"swi":2})  #notice it may change, see according function in FiniteVolumeCCZ4.cpp
      print(intparams)
      userinfo.append((msg,None))
    elif args.scenario=="single-puncture":
      msg = "Periodic BC deactivated because you pick Puncture scenario\nInitialize single black hole"
      print(msg)
      periodic_boundary_conditions = [False,False,False]
      intparams.update({"swi":0}) 
      userinfo.append((msg,None))
    elif args.periodic_bc=="True":
      msg = "Periodic BC set"
      print(msg)
      periodic_boundary_conditions = [True,True,True]          # Periodic BC
      userinfo.append((msg,None))
    else:
      msg = "WARNING: Periodic BC deactivated by hand"
      print(msg)
      periodic_boundary_conditions = [False,False,False]
      userinfo.append((msg,None))

    intparams.update({"ReSwi":args.CCZ4ReSwi})

    solverconstants=""
    for k, v in floatparams.items(): solverconstants+= "static constexpr double {} = {};\n".format("CCZ4{}".format(k), v)
    for k, v in intparams.items():   solverconstants+= "static constexpr int {} = {};\n".format("CCZ4{}".format(k), v)
    my_solver.set_solver_constants(solverconstants)

    if args.scenario=="gauge":
      my_solver.pick_Gauge_wave_scenario()
    elif args.scenario=="linear":
      my_solver.pick_Linear_wave_scenario()
    elif  (args.scenario=="two-punctures") or (args.scenario=="single-puncture"):
      my_solver.pick_two_puncture_scenario()
    else:
      raise Exception( "Scenario " + args.scenario + " is now unknown")  

    project.add_solver(my_solver)

    build_mode = modes[args.mode]
    
    dimensions = 3

########################################################################################
#Domain settings
########################################################################################
    if args.scenario=="gauge" or args.scenario=="linear":
      offset=[-0.5, -0.5, -0.5]; domain_size=[1.0, 1.0, 1.0]
      #offset=[-1.5, -1.5, -1.5]; domain_size=[3.0, 3.0, 3.0]
      msg = "Gauge wave, domain set as "+str(offset)+" and "+str(domain_size)
      print(msg)
      userinfo.append((msg,None))
    if args.scenario=="two-punctures" or args.scenario=="single-puncture":
      offset=[-20, -20, -20]; domain_size=[40.0, 40.0, 40.0]
      #offset=[-30, -30, -30]; domain_size=[60.0, 60.0, 60.0]
      #offset=[-40, -40, -40]; domain_size=[80.0, 80.0, 80.0]
      msg = "Two/single punctures, domain set as "+str(offset)+" and "+str(domain_size)
      print(msg)
      userinfo.append((msg,None))

    project.set_global_simulation_parameters(
      dimensions,               # dimensions
      offset,  domain_size,
      args.end_time,                 # end time
      0.0, args.plot_step_size,   # snapshots
      periodic_boundary_conditions,
      8  # plotter precision
    )

    project.set_Peano4_installation("../../..", build_mode)

########################################################################################
#output dir and proble
########################################################################################
    path="./"
    if not args.path=="./":
        path=args.path 
    #path="/cosma5/data/durham/dc-zhan3/bbh-c5-1"
    #path="/cosma6/data/dp004/dc-zhan3/exahype2/sbh-fv3"
    project.set_output_path(path)
    probe_point = [-1,-1,0.0]
    project.add_plot_filter( probe_point,[40.0,40.0,0.01],1 )

    project.set_load_balancing("toolbox::loadbalancing::RecursiveSubdivision","(new ::exahype2::LoadBalancingConfiguration(0.98,0))" )

########################################################################################
#Tracer setting 
########################################################################################
    if not args.add_tracer==0:
      tracer_name = {1:"line", 2:"slide", 3:"volume", 6:"Gauss_Legendre_quadrature", 7:"t-design"}
      tracer_particles = project.add_tracer( name="MyTracer",attribute_count=65 )
       #project.add_action_set_to_timestepping(exahype2.tracer.FiniteVolumesTracing(tracer_particles,my_solver,[17,18,19],[16],-1,time_stepping_kernel="toolbox::particles::explicitEulerWithoutInterpolation"))
      project.add_action_set_to_timestepping(
        exahype2.tracer.FiniteVolumesTracing(
          tracer_particles,my_solver,
          [17,18,19],range(65),-1,
          #time_stepping_kernel="toolbox::particles::LinearInterp",
          time_stepping_kernel="toolbox::particles::StaticPosition"#,
          #observer_kernel="toolbox::particles::ObLinearInterp"
        )
      )
      if args.add_tracer==1 or args.add_tracer==2 or args.add_tracer==3 :
        tracer_seeds_generate(Type=args.add_tracer, a=-15, b=15, N_x=1000,N_y=1,N_z=1)
        project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesFromFile( particle_set=tracer_particles, filename=tracer_name[args.add_tracer]+".dat", scale_factor=1)) #"Line.dat" #slide.dat #volume.dat
      if args.add_tracer==4:  
        project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesAlongCartesianMesh( particle_set=tracer_particles, h=args.max_h/2.0, noise=True ))
      if args.add_tracer==5:
        project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesbyCoordinates ( particle_set=tracer_particles, N=3, coor_s=[[0.4251,0,0],[-0.4251,0,0],[0.2,0.2,0]]))
      if args.add_tracer==6 or args.add_tracer==7:
        project.add_action_set_to_initialisation( exahype2.tracer.InsertParticlesFromFile( particle_set=tracer_particles, filename=tracer_name[args.add_tracer]+".dat", scale_factor=abs(offset[0])*0.8)) #"Gauss_Legendre_quadrature.dat" #"t-design.dat" 
      
      if path=="./": path1="."
      else: path1="/cosma5/data/durham/dc-zhan3/sbh-tracer"
      project.add_action_set_to_timestepping(exahype2.tracer.DumpTrajectoryIntoDatabase(
        particle_set=tracer_particles,
        solver=my_solver,
        filename=path1+"/zz"+args.tra_name,
        number_of_entries_between_two_db_flushes=30000
      ))
      #data_delta_between_two_snapsots,position_delta_between_two_snapsots,filename,          
      #,,-1,"zz",1000))

########################################################################################
#linking stuff
########################################################################################
    peano4_project = project.generate_Peano4_project(verbose=True)

    if args.scenario=="gauge":
      pass
    elif args.scenario=="linear":
      pass
    elif args.scenario=="two-punctures" or args.scenario=="single-puncture":
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
      raise Exception( "Scenario " + args.scenario + " is now unknown")        

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
    userinfo.append(("the executable file name: "+exe, None))
    userinfo.append(("output directory: "+path, None))
    print("=========================================================")
    if not args.add_tracer==0:
        userinfo.append(("tracer output file: "+path1+"/zz"+args.tra_name, None))
    if len(userinfo) >0:
        print("Please note that these warning occured before the build:")
        for msg, exception in userinfo:
            if exception is None:
                print(msg)
            else: print(msg, "Exception: {}".format(exception))
    print(intparams)
    print(floatparams)
    print("=========================================================")
