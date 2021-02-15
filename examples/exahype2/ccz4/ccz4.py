import os
import peano4
import exahype2

class CCZ4Solver( exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves ):
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
    
    number_of_unknowns = 0
    for i in unknowns:
      number_of_unknowns += unknowns[i]
    print( "number of unknowns=", number_of_unknowns )
    
    #number_of_auxiliary_variables = 0
    number_of_auxiliary_variables  = 6

    exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves.__init__( 
      self,
      name=name, patch_size=patch_size, 
      unknowns=number_of_unknowns, 
      auxiliary_variables=number_of_auxiliary_variables, 
      min_h=min_h, max_h=max_h, 
      time_step_relaxation=0.1
    )
    
    self._solver_template_file_class_name = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves.__name__
    self.add_constraint_verification()


  def get_user_includes(self):
    """
    
     We take this routine to add a few additional include statements.
     
    """
    return exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves.get_user_includes(self) + """
#include "../PDE.h"
#include "exahype2/PatchUtils.h"    
"""


  def add_constraint_verification(self):
    """
     
     Add the constraint verification code
     
     We introduce new auxiliary variables. Prior to each time step, I 
     compute the Laplacian and store it in the auxiliary variable. This
     is kind of a material parameter F(Q) which does not feed back into
     the solution.
     
    """
    if self._auxiliary_variables != 6:
      raise Exception( "number of constraints does not match." )
  
    self._preprocess_reconstructed_patch  = """
    const int patchSize = """ + str(self._patch.dim[0]) + """;
    double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
    int n_a_v=6;
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
     
      admconstraints_(constraints,reconstructedPatch+cellSerialised*(59+n_a_v),gradQ);
	  
      for(int i=0;i<n_a_v;i++){
        reconstructedPatch[cellSerialised*(59+n_a_v)+59+i] = constraints[i];
      }
    }
"""
    
    
if __name__ == "__main__":
    project = exahype2.Project( ["examples", "exahype2", "ccz4"], "ccz4" )

    time_step_size      = 0.001
    max_h               = 0.4
    min_h               = 0.4
    patch_size          = 6
    
    my_solver = CCZ4Solver(
      "CCZ4", patch_size, min_h, max_h
    )
    
    project.add_solver(my_solver)
    
    import exahype2.sympy
    
    pde = exahype2.sympy.PDE(unknowns=my_solver._unknowns,auxiliary_variables=my_solver._auxiliary_variables,dimensions=3)
    
    my_solver.set_implementation(
      boundary_conditions=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
      flux=exahype2.solvers.fv.PDETerms.None_Implementation,
      ncp=exahype2.solvers.fv.PDETerms.User_Defined_Implementation,
      source_term=exahype2.solvers.fv.PDETerms.User_Defined_Implementation
    )   
    
    build_mode = peano4.output.CompileMode.Asserts
    #build_mode = peano4.output.CompileMode.Release
    
    dimensions = 3
    end_time = 1.0
    snapshots = time_step_size*40
        
    project.set_global_simulation_parameters(
      dimensions,               # dimensions
      [-0.5, -0.5, -0.5],  [1.0, 1.0, 1.0],
      end_time,                 # end time
      0.0, snapshots,   # snapshots
      [True,True,True]          # Periodic BC
    )
    
    project.set_Peano4_installation("../../..", build_mode)

    #project.set_output_path( "/cosma6/data/dp004/dc-zhan3/tem3" )

    peano4_project = project.generate_Peano4_project()
    
    peano4_project.output.makefile.add_Fortran_flag( "-DCCZ4EINSTEIN -DDim3" )
    
    # This is for GNU
    peano4_project.output.makefile.add_Fortran_flag( "-lstdc++ -fdefault-real-8 -fdefault-double-8 -cpp -std=legacy -ffree-line-length-512 -fPIC" )
#add routie to find the gfortran
#need to create a link first:sudo ln -s /usr/lib/x86_64-linux-gnu/libgfortran.so.4 /usr/lib/x86_64-linux-gnu/libgfortran.so
    #peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC -L/usr/lib/x86_64-linux-gnu -lgfortran" )
    peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC -lgfortran" )

    # This might work for Intel (not tested)
    #peano4_project.output.makefile.add_Fortran_flag( "-r8 -cpp -auto -qopenmp-simd -O2" )
    #peano4_project.output.makefile.add_linker_flag( "-lstdc++ -fPIC" )
    # you might need -lifcore
    
    peano4_project.output.makefile.add_Fortran_module( "MainVariables.f90" )
    
    peano4_project.output.makefile.add_Fortran_files( 
      ["PDE.f90 ", "EinsteinConstraints.f90 ", "Properties.f90",
        "Metric.f90 ", "C2P-FOCCZ4.f90 ","ADMConstraints.f90"] 
    )
    
    peano4_project.constants.export_string( "Scenario", "gaugewave-c++" )
    
    peano4_project.generate( throw_away_data_after_generation=False )
    
    parallel_builds = 4   # I don't use a massively parallel build here as my laptop otherwise becomes too hot.
                          # Without any arguments, the build process will grab all of your cores.
    peano4_project.build( make_clean_first = False, number_of_parallel_builds = parallel_builds )
    #!make -j4

