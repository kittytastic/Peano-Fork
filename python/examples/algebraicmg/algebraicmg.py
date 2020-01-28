"""

 A very simple example for our geometric-algebraic multigrid solver.
 Sole h-refinement with a low-order discretisation.

"""

import os
import peano4
import peano4.datamodel
import peano4.solversteps
import peano4.output
import peano4.visualisation
import peano4.toolbox



#
# Lets first clean up all plot files, so we don't get a mismatch
#
output_files = [ f for f in os.listdir(".") if f.endswith(".peano-patch-file") ]
for f in output_files:
  os.remove(f)



#
# Create a project and configure it to end up in a subnamespace (and thus
# subdirectory). 
#
project = peano4.Project( ["examples", "algebraicmg"], "." )


#
# There's different ways to tell the project which data are associated to the 
# grid entities. One way to associate stuff is to use our DaStGen legacy format.
# This is our strategy here.
#
dastgen_model = peano4.datamodel.DaStGen( "MG" )
dastgen_model.add_double_scalar( "u" )
dastgen_model.add_double_scalar( "rhs" )
dastgen_model.add_double_scalar( "res" )
project.datamodel.add_vertex( dastgen_model )



#
# First, lets create the initial grid (which is regular)
#
create_grid = peano4.solversteps.Step( "CreateGrid", False )
#
# @todo Die Zeile haett ich gern raus. Aber dann werden die Vertices net auf dem Stack
#       abgelegt. Das ist konzeptionell. Aber ich muss es irgendwo abfragen/-sichern.
#       Alternativ kann ich die Konvention einbauen, dass creational Patterns immer in
#       jedem Mapping aufgerufen werden. Find ich aber net so schoen. Am schoensten 
#       waere eine Assertion im C++ Code oder ein Check hier. Eher ersteres.
#
create_grid.use_vertex( dastgen_model )
create_grid.add_mapping( peano4.toolbox.CreateRegularGrid(0.01) )
project.solversteps.add_step(create_grid)



#
# Set up the rhs and the material parameters, boundary conditions, and, finally,
# also the initial guess. For this, we use the default constructor value True,
# i.e. we ask the API to give us a C++ routine.
#
setup_scenario = peano4.solversteps.Step( "SetupScenario" )
setup_scenario.use_vertex( dastgen_model )
project.solversteps.add_step(setup_scenario)


#
# Finally, plot the grid.
#
plot_solution = peano4.solversteps.Step( "PlotSolution", False )
plot_solution.add_mapping( peano4.toolbox.PlotGridInPeanoBlockFormat("solution",None) )
project.solversteps.add_step(plot_solution)


#
# Peano's API does not know which settings to use on the present system. To 
# make it copy/clone the settings identified by ./configure, we ask it to 
# parse the generated configuration scripts. The makefile would also offer a
# routine to set the dimension. We take the default here.
#
project.output.makefile.parse_configure_script_outcome( "/home/tobias/git/Peano" )


#
# Standard triad of operations. You can skip the first two steps if you want as 
# the script then will automatically invoke the previous steps. The other way 
# round, it is always admissible to only generate stuff, e.g., but to build and
# run the project through a command line
#
project.generate(peano4.output.Overwrite.Default)
project.build()
project.run( ["myarguments"] )


#
# Convert data into vtk, so we can open it in Paraview
#
convert = peano4.visualisation.Convert( "solution" )
convert.set_visualisation_tools_path( "/home/tobias/git/Peano/src/visualisation" )
convert.extract_fine_grid()
convert.convert_to_vtk()
