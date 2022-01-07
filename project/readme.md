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