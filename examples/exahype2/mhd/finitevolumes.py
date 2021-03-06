"""

 A very simple example which demonstrates how to configure a patch-based
 Finite Volume solver in Peano4. The code relies on snippets from ExaHyPE2.
 However, it relies only on ExaHyPE's C/FORTRAN compute kernels, i.e. the 
 sophisticated build environment of this H2020 project is not used. The 
 solver simulates the simple MHD equations.

"""


#
# We import Peano4 as project. If this step fails, ensure that your environment
# variable PYTHONPATH points to Peano4's python directory.
#
import os
import peano4
import peano4.datamodel
import peano4.solversteps
import peano4.output
import peano4.visualisation
import peano4.toolbox.blockstructured


import exahype2


#
# Lets first clean up all plot files, so we don't get a mismatch
#
output_files = [ f for f in os.listdir(".") if f.endswith(".peano-patch-file") or f.endswith(".vtu") ]
for f in output_files:
  os.remove(f)


#
# Create a project and configure it to end up in a subnamespace (and thus
# subdirectory). 
#
project = exahype2.Project( ["examples", "exahype2", "finitevolumes"], "finitevolumes", "." )


#
# Add the Finite Volumes solver
#
patch_size     = 23
unknowns       = 9
time_step_size = 0.01
project.add_solver( exahype2.solvers.fv.GenericRusanovFixedTimeStepSize(
  name="MHD", 
  patch_size=patch_size, 
  unknowns=unknowns, 
  auxiliary_variables=0, 
  min_h=0.1, 
  max_h=0.1, 
  time_step_size=0.001, 
  #flux=PDETerms.User_Defined_Implementation, ncp=None, plot_grid_properties=False 
))


dimensions = 2
build_mode = peano4.output.CompileMode.Asserts

#
# Lets configure some global parameters
#
if dimensions==2:
  project.set_global_simulation_parameters(
    dimensions,  [0.0,0.0],  [1.0,1.0],
    0.1,          # end time
    0.0, 0.1     # snapshots
  )
else:
  project.set_global_simulation_parameters(
    dimensions, [0.0,0.0,0.0], [1.0,1.0,1.0],
    1.0,          # end time
    0.0, 0.1
  )



peano4_project = project.generate_Peano4_project()

peano4_project.output.makefile.parse_configure_script_outcome( "../../.." )
peano4_project.output.makefile.set_mode(build_mode)

peano4_project.output.makefile.add_Fortran_file( "Parameters.f90" )
peano4_project.output.makefile.add_Fortran_file( "C2P-MHD.f90" )
peano4_project.output.makefile.add_Fortran_file( "C2PRoutines.f90" )
peano4_project.output.makefile.add_Fortran_file( "PDE.f90" )
peano4_project.output.makefile.add_Fortran_file( "InitialData.f90" )

peano4_project.generate(peano4.output.Overwrite.Default)
peano4_project.build()
success = peano4_project.run( [] )


if success:
  convert = peano4.visualisation.Convert( "solutionMHD", True )
  convert.set_visualisation_tools_path( "../../../../src/visualisation" )
  convert.extract_fine_grid()
  convert.convert_to_vtk()



