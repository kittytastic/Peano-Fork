#!/bin/bash


source /etc/profile.d/modules.sh

module load intel/xe_2018.2
module load intelmpi/intel/2018.2

export d=2
for cores in 1 2 3 4 6 8 10 12 14 16 20 24 28 32 36 40 44 48
do
 for flops in 1 100 10000 1000000
 do
  for h in 0.1 0.5 0.01 0.005 0.001
  do
   executable="./PeanoRegularGridUpscaling"$d"d"
   output="shared-memory-"$cores"-cores-"$d"d-"$h"-"$flops"-flops.out"
   echo $executable  $output
   $executable $h $flops $cores > $output
  done
 done
done



