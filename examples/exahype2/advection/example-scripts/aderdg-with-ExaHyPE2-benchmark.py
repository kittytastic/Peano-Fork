"""

 A very simple example which demonstrates how to configure a patch-based
 Finite Volume solver in Peano4. The code relies on snippets from ExaHyPE2.
 However, it relies only on ExaHyPE's C/FORTRAN compute kernels, i.e. the
 sophisticated build environment of this H2020 project is not used. The
 solver simulates the simple linear advection equations.

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

python3 example-scripts/aderdg-with-ExaHyPE2-benchmark.py arguments
""")

modes = { 
  "release": peano4.output.CompileMode.Release,
  "trace":   peano4.output.CompileMode.Trace,
  "stats":   peano4.output.CompileMode.Stats,
  "assert":  peano4.output.CompileMode.Asserts, "stats":  peano4.output.CompileMode.Stats,
  "debug":   peano4.output.CompileMode.Debug,
}

parser = argparse.ArgumentParser(description='ExaHyPE 2 - Advection benchmarking script')
parser.add_argument("--load-balancing-quality", dest="load_balancing_quality", type=float, default=0.9, help="Load balancing quality (something between 0 and 1; 1 is optimal)" )
parser.add_argument("--h",               dest="h",              type=float, required=True, help="Mesh size" )
parser.add_argument("--j",               dest="j",              type=int, default=4, help="Parallel builds" )
parser.add_argument("--d",               dest="dim",            type=int, default=2, help="Dimensions" )
parser.add_argument("--m",               dest="mode",                     default="release", help="|".join(modes.keys()) )
parser.add_argument("--t",               dest="timesteps",      type=int, default=10, help="Number of timesteps" )
parser.add_argument("--p",               dest="peanodir",                 default="../../../", help="Peano4 directory" )
parser.add_argument("--c",               dest="configuredir",             default="../../../", help="Location of configure" )
parser.add_argument("--o",               dest="out",             default="peano4", help="Executable name" )
parser.add_argument("--f",               dest="force",           default=False, action="store_true", help="Allow overwriting of output file." )
parser.add_argument("--gpu",             dest="GPU",             default=False, action="store_true", help="Use GPU features." )
parser.add_argument("--dt",              dest="plot_snapshot_interval", default=0, help="Time interval in-between two snapshots (switched off by default")
args = parser.parse_args()

if args.dim not in [2,3]:
    print("Error, dimension must be 2 or 3, you supplied {}".format(args.dim))
    import sys
    sys.exit(1)

if args.mode not in modes: 
    print("Error, mode must be {} or {}, you supplied {}".format(", ",join(modes.keys()[:-1]),modes.keys()[-1],args.mode))
    import sys
    sys.exit(1)

if args.out is not None and os.path.exists(args.out) and not args.force:
    print("Not overwriting existing output file name {}. Use --f to force it.".format(args.out))
    sys.exit(1)

print("\nConfiguring {}D Advection problem with h={} and {} timesteps. Buildmode is {}, nbuilds={}.\n".format(args.dim, args.h, args.timesteps, args.mode, args.j))
print("Executable: {}".format(args.out))

#
# Create a project and configure it to end up in a subnamespace (and thus
# subdirectory). 
#
project = exahype2.Project( ["examples", "exahype2", "advection"], "aderdg", ".", executable=args.out )


#
# Add the Finite Volumes solver
#
order          = 3
unknowns       = 4
time_step_size = 0.00001
min_h          = args.h
max_h          = args.h

#
# Still the same solver, but this time we use named arguments. This is the way
# you can add further PDE terms btw.
#
#

thesolver = None
if args.GPU:
  print("Turning on OpenMP for GPUs")
  raise Exception( "not yet supported" )
  thesolver = exahype2.solvers.fv.GenericRusanovFixedTimeStepSizeWithAccelerator(
    "EulerOnGPU",
    patch_size,
    unknowns, 0,
    min_h, max_h,
    time_step_size,
    flux = exahype2.solvers.fv.PDETerms.User_Defined_Implementation
  )

else:
  print( "Have to introduce enclaves again" )
  thesolver = exahype2.solvers.aderdg.NonFusedGenericRusanovFixedTimeStepSize(
    "ADERDGAdvection", order, unknowns, 0, #auxiliary_variables
    exahype2.solvers.aderdg.Polynomials.Gauss_Legendre, 
    min_h, max_h, time_step_size
  )
  thesolver.set_plot_description( "0: Density, (1,2,3): Velocities")

project.add_solver( thesolver )

dimensions = args.dim
build_mode = modes[args.mode]

#
# Lets configure some global parameters
#
project.set_global_simulation_parameters(
  dimensions, [0.0,0.0,0.0], [1.0,1.0,1.0],
  time_step_size * args.timesteps, # end time
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
print( "Convert any output via pvpython ~/git/Peano/python/peano4/visualisation/render.py solution-ADERDGAdvection.peano-patch-file")
