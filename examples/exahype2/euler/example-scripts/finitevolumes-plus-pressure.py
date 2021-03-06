"""

 A very simple example which demonstrates how to configure a patch-based
 Finite Volume solver in Peano4. The code relies on snippets from ExaHyPE2.
 However, it relies only on ExaHyPE's C/FORTRAN compute kernels, i.e. the
 sophisticated build environment of this H2020 project is not used. The
 solver simulates the simple Euler equations.

"""


#
# We import Peano4 as project. If this step fails, ensure that your environment
# variable PYTHONPATH points to Peano4's python directory.
#
import os, sys
import peano4
import exahype2
import argparse


print( """
Please call this script from the directory hosting the Makefile and the
sources. Typically, I invoke the script via

python3 example-scripts/finitevolumes-with-ExaHyPE2-benchmark.py arguments
""")


parser = argparse.ArgumentParser(description='ExaHyPE 2 - Euler benchmarking script')
parser.add_argument("-lb",  "--load-balancing-quality", dest="load_balancing_quality", type=float, default=0.9, help="Load balancing quality (something between 0 and 1; 1 is optimal)" )
parser.add_argument("-cs",  "--cell-size",              dest="h",              type=float, required=True, help="Mesh size" )
parser.add_argument("-j",   "--parallel-builds",        dest="j",              type=int, default=4, help="Parallel builds" )
parser.add_argument("-d",   "--dim",                    dest="dim",            type=int, default=2, help="Dimensions" )
parser.add_argument("-m",   "--mode",                   dest="mode",                     default="release", help="release|trace|assert" )
parser.add_argument("-et",   "--end-time",              dest="end_time",                 type=float, default=1.0, help="Number of timesteps" )
parser.add_argument("-pd",  "--peano-dir",              dest="peanodir",                 default="../../../", help="Peano4 directory" )
parser.add_argument("-cd",  "--configure-dir",          dest="configuredir",             default="../../../", help="Location of configure" )
parser.add_argument("-o",   "--output",                 dest="out",                      default="peano4", help="Executable name" )
parser.add_argument("-f",   "--force",                  dest="force",                    default=False, action="store_true", help="Allow overwriting of output file" )
parser.add_argument("-t",   "--type",                   dest="type",                     choices=["default", "default-ats", "enclave", "enclave-ats" ], default="default", help="Pick implementation variant" )
parser.add_argument("-pdt", "--plot-dt",                dest="plot_snapshot_interval", default=0, help="Time interval in-between two snapshots (switched off by default")
args = parser.parse_args()

if args.dim not in [2,3]:
    print("Error, dimension must be 2 or 3, you supplied {}".format(args.dim))
    import sys
    sys.exit(1)

if args.mode not in ["release", "trace", "assert"]:
    print("Error, mode must be release, trace or assert, you supplied {}".format(args.mode))
    import sys
    sys.exit(1)

if args.out is not None and os.path.exists(args.out) and not args.force:
    print("Not overwriting existing output file name {}. Use --f to force it.".format(args.out))
    sys.exit(1)

print("\nConfiguring {}D Euler problem. Buildmode is {}, nbuilds={}.\n".format(args.dim, args.mode, args.j))
print("Executable: {}".format(args.out))

#
# Create a project and configure it to end up in a subnamespace (and thus
# subdirectory). 
#
project = exahype2.Project( ["examples", "exahype2", "euler"], "finitevolumes", ".", executable=args.out )


#
# Add the Finite Volumes solver
#
patch_size     = 12
unknowns       = 5
time_step_size = 0.000001
min_h          = args.h
max_h          = args.h


admissible_time_step_size = min_h/patch_size*0.01

#
# Still the same solver, but this time we use named arguments. This is the way
# you can add further PDE terms btw.
#
#

auxiliary_variables = 3

thesolver = None
if args.type=="enclave":
  thesolver = exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithEnclaves(
    "Euler",
    patch_size,
    unknowns, auxiliary_variables,
    min_h, max_h,
    admissible_time_step_size,
    flux = exahype2.solvers.fv.PDETerms.User_Defined_Implementation
  )
elif args.type=="enclave-ats":
  thesolver = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSizeWithEnclaves(
    "Euler",
    patch_size,
    unknowns, auxiliary_variables,
    min_h, max_h,
    flux = exahype2.solvers.fv.PDETerms.User_Defined_Implementation
  )
elif args.type=="default":
  thesolver = exahype2.solvers.fv.GenericRusanovFixedTimeStepSize(
    "Euler",
    patch_size,
    unknowns, auxiliary_variables,
    min_h, max_h,
    admissible_time_step_size,
    flux = exahype2.solvers.fv.PDETerms.User_Defined_Implementation
  )
elif args.type=="default-ats":
  thesolver = exahype2.solvers.fv.GenericRusanovAdaptiveTimeStepSize(
    "Euler",
    patch_size,
    unknowns, auxiliary_variables,
    min_h, max_h,
    flux = exahype2.solvers.fv.PDETerms.User_Defined_Implementation
  )


thesolver.additional_includes = """
#include "peano4/utils/Loop.h"
"""
thesolver.set_preprocess_reconstructed_patch_kernel( """
  const int patchSize = """ + str(patch_size) + """;
  double volumeH = ::exahype2::getVolumeLength(marker.h(),patchSize);
  const int analysedVariable = 4; // energy
  dfor(cell,patchSize) {
    tarch::la::Vector<Dimensions,int> currentCell = cell + tarch::la::Vector<Dimensions,int>(1);
      
    const int cellSerialised  = peano4::utils::dLinearised(currentCell, patchSize + 2*1);
    reconstructedPatch[cellSerialised*(5+3)+5] = 1.0 / volumeH / 2.0 * (reconstructedPatch[ (cellSerialised+1)*(5+3)+analysedVariable] - reconstructedPatch[ (cellSerialised-1)*(5+3)+analysedVariable]);
    reconstructedPatch[cellSerialised*(5+3)+6] = 1.0 / volumeH / 2.0 * (reconstructedPatch[ (cellSerialised+patchSize+2)*(5+3)+analysedVariable] - reconstructedPatch[ (cellSerialised-patchSize-2)*(5+3)+analysedVariable]);
    #if Dimensions==3
    #endif
  }
""" )
project.add_solver( thesolver )


dimensions = args.dim
if (args.mode=="release"):
    build_mode = peano4.output.CompileMode.Release
elif (args.mode=="trace"):
    build_mode = peano4.output.CompileMode.Trace
else:
    build_mode = peano4.output.CompileMode.Asserts



#
# Lets configure some global parameters
#
project.set_global_simulation_parameters(
  dimensions, [0.0,0.0,0.0], [1.0,1.0,1.0],
  args.end_time, 
  0.0, args.plot_snapshot_interval      # snapshots
)


#
# So here's the parallel stuff. This is new compared to the serial
# prototype we did start off with.
#
project.set_load_balancing( "toolbox::loadbalancing::RecursiveSubdivision", "(" + str(args.load_balancing_quality) + ")" )
project.set_Peano4_installation( args.peanodir, build_mode )
peano4_project = project.generate_Peano4_project()
peano4_project.output.makefile.parse_configure_script_outcome( args.configuredir )
peano4_project.build(make_clean_first=True, number_of_parallel_builds=args.j)
print("Done. Executable is: {}".format(args.out))
print( "Convert any output via pvpython ~/git/Peano/python/peano4/visualisation/render.py solution-Euler.peano-patch-file")
