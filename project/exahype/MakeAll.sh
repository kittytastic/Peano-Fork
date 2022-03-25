echo "------ Preparing Projects ------"
(cd Euler2D/default_kernel; git clean -xdf; python euler2D.py; make clean;)>>/dev/null
echo "Euler 2D - default: DONE"
(cd Euler2D/generated; git clean -xdf; python euler2D.py; make clean; git restore observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.cpp; python ../../fix_makefile.py euler2d.g.cpp)>>/dev/null
echo "Euler 2D - generated: DONE"
(cd SWE/default_kernel; git clean -xdf; python SWE.py; make clean; git restore observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.cpp)>>/dev/null
echo "SWE - default: DONE"
(cd SWE/generated; git clean -xdf; python SWE.py; make clean; git restore observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.cpp; python ../../fix_makefile.py swe.g.cpp)>>/dev/null
echo "SWE - generated: DONE"
(cd Euler3D/default_kernel; git clean -xdf; python euler3D.py; make clean; git restore observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.cpp)>>/dev/null
echo "Euler 3D - default: DONE"
(cd Euler3D/generated; git clean -xdf; python euler3D.py; make clean; git restore observers/TimeStep2peano4_toolbox_blockstructured_ReconstructPatchAndApplyFunctor5.cpp; python ../../fix_makefile.py euler3d.g.cpp)>>/dev/null
echo "Euler 3D - generated: DONE"


echo ""
echo "------ Making projects ------"
(cd Euler2D/default_kernel; make -j$1)>>/dev/null
echo "Euler 2D - default: DONE"
(cd Euler2D/generated; make -j$1)>>/dev/null
echo "Euler 2D - generated: DONE"
(cd SWE/default_kernel; make -j$1)>>/dev/null
echo "SWE - default: DONE"
(cd SWE/generated; make -j$1)>>/dev/null
echo "SWE - generated: DONE"
(cd Euler3D/default_kernel; make -j$1)>>/dev/null
echo "Euler 3D - default: DONE"
(cd Euler3D/generated; make -j$1)>>/dev/null
echo "Euler 3D - generated: DONE"