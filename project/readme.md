### Install ExaHyPE

```
libtoolize; aclocal; autoconf; autoheader; cp src/config.h.in .; automake --add-missing
export CXXFLAGS="-std=c++17"
```

```
. /opt/intel/oneapi/setvars.sh --config=~/oneapi.config
export CC="icx"
export CXX="icpx"
export CFLAGS="-O3 -qopenmp"
export CXXFLAGS="-std=c++17 -O3 -qopenmp"
```

```
mkdir bindir
./configure --enable-exahype --enable-blockstructured --enable-loadbalancing --bindir=/home/jack/dis/Peano/bindir
--with-multithreading=omp
```

```
make -j12
make install
```


```
curl -sSL https://raw.githubusercontent.com/python-poetry/poetry/master/get-poetry.py | python -
source $HOME/.poetry/bin
```

#### Hamilton 8
source ~/exa-env/bin/activate; module load aocc/3.1.0; module load paraview/5.10.0
export PYTHONPATH=../../python
export CXX="clang++ -lstdc++fs"
export CXXFLAGS="-std=c++17 -march=znver2 -Ofast -Wno-unused-command-line-argument -fopenmp -g"
./configure --enable-exahype --enable-blockstructured --enable-loadbalancing --bindir=$PWD/bindir
make -j64
make install
```

Might need to: add -lstdc++fs to the LIBS+= in makefile

srun --nodes=1 --ntasks-per-node=1 --time=01:00:00 --pty bash -i

pvpython ../../python/peano4/visualisation/render.py solution-euler2D.peano-patch-file



build maqao
git clone git@gitlab.exascale-computing.eu:MAQAO/MAQAO.git


maqao oneview -R1 --config=maqao.lua