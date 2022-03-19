#!/bin/sh
jobs=1
preset="g++"

while getopts :p:j: flag
do
    case "${flag}" in
        p) preset=${OPTARG};;
        j) jobs=${OPTARG};;
    esac
done

MAKE_ARGS=""
case $preset in
    hal-intel)
        MAKE_ARGS="CXX=icpx"
        ;;
    ham-amd)
        MAKE_ARGS="CXX='clang++' OPTIMISE_CXX_FLAGS='-Ofast'"
        ;;
    ham-intel)
        MAKE_ARGS="CXX='icpx' OPTIMISE_CXX_FLAGS='-Ofast'"
        ;;
    g++)
        MAKE_ARGS="CXX=g++"
        ;;
    *)
        echo "Unknown arguent $1"
        exit 1
        ;;
esac

echo "Using preset: $1";
echo "Running: make $MAKE_ARGS -j $jobs"
make clean
make $MAKE_ARGS -j $jobs