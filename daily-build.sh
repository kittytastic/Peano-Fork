folders=(pdf src visualisation)

peanoVersion="Peano-$(git log --format="%h" -n 1 .)"

tarName="$peanoVersion.tar.gz"

echo $tarName

tar --exclude-vcs --exclude=*.o -czvf  $tarName ${folders[*]} ${files[*]}

