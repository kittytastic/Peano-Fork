#!/bin/bash

# Request resources:
#SBATCH -n 1          # 1 CPU core
#SBATCH --time=1:0:0  # 6 hours (hours:minutes:seconds)
#SBATCH -p shared
#SBATCH --mem=8GB
# Commands to be run:

../KernelCompare -f ham8-amd-5s.csv -t 5.0
../KernelCompare -f ham8-amd-10s.csv -t 10.0
../KernelCompare -f ham8-amd-20s.csv -t 20.0
../KernelCompare -f ham8-amd-30s.csv -t 30.0
../KernelCompare -f ham8-amd-40s.csv -t 40.0
../KernelCompare -f ham8-amd-50s.csv -t 50.0
../KernelCompare -f ham8-amd-60s.csv -t 60.0
