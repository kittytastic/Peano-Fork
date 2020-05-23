#!/usr/bin/env python3
"""
 A more sophisticated example, which uses an FV solver with
 nonconservative product and also shows how to adapt your
 code to take command line arguments into account.

 This example simulates the LOH.1 seismology benchmark based on the elastic
 wave equations plus a diffuse interface model that takes material interfaces
 into account.
 We solve the equations using (a very diffusive) first-order FV solver.
 The code relies on snippets from the first version 
 of ExaHyPE. However, it relies only on ExaHyPE's C/FORTRAN compute kernels, i.e. the 
 sophisticated build environment of this H2020 project is not used. 

 For more details on the benchmark problem, see:
 http://sismowine.org/model/WP2_LOH1.pdf

 Fore more details on the underlying mathematical modelling, see:
 https://www.sciencedirect.com/science/article/pii/S0021999119300786 
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

# CLI
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-c","--clean", dest="make_clean_first", action="store_true",help="Clean the project before making the project.")
args = parser.parse_args()

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
project = exahype2.Project( 
  namespace    = ["examples", "exahype2", "finitevolumes"], 
  project_name = "finitevolumes", 
  directory    = "." )

#
# Add the Finite Volumes solver with (flux and ncp)
#
project.add_solver(  
  exahype2.solvers.GenericRusanovFVFixedTimeStepSize(
    name           = "LOH1", 
    patch_size     = 7, 
    unknowns       = 9, 
    time_step_size = 0.01, 
    flux           = True, 
    ncp            = True) )

build_mode = peano4.output.CompileMode.Asserts

#
# Lets configure some global parameters
#
dimensions=3 
project.set_global_simulation_parameters(
  dimensions            = dimensions,
  offset                = [0.0]*dimensions, 
  size                  = [1.0]*dimensions,
  terminal_time         = 0.1,        
  first_plot_time_stamp = 0.0, 
  time_in_between_plots = 0.1
)

peano4_project = project.generate_Peano4_project()

peano4_project.output.makefile.parse_configure_script_outcome( "../../../.." )
peano4_project.output.makefile.add_library( project.get_core_library(build_mode), "../../../../src/exahype2" )
peano4_project.output.makefile.set_mode(build_mode)

peano4_project.generate( peano4.output.Overwrite.Default )
peano4_project.build( make_clean_first = args.make_clean_first )
success = peano4_project.run( [] )

if success:
  convert = peano4.visualisation.Convert( "solutionLOH1", True )
  convert.set_visualisation_tools_path( "../../../../src/visualisation" )
  convert.extract_fine_grid()
  convert.convert_to_vtk()
