# author: Tobias Weinzierl


set style line 1 lc rgb "#ff6600" lt 1 pt 7   lw 1.0 ps 1.6 
set style line 2 lc rgb "#00ff66" lt 1 pt 9   lw 1.0 ps 1.6 
set style line 3 lc rgb "#6600ff" lt 1 pt 11  lw 1.0 ps 1.6 


set grid

set xlabel 'runtime'
set ylabel 'time [t]=s'

set key right top

#set style data histogram
#set style histogram cluster gap 1 
#set style fill solid border -1 
#set boxwidth 0.9
#set xtic rotate by -45 scale 0
#set key left top 



set title "Overview"

plot "tmp.data"  using  1:2  title "idle times"   with points ls 1, \
     "tmp.data"  using  1:3  title "busy times"   with points ls 2, \
     "tmp.data"  using  ($1):(($2)+($3))   every :::0::1  title "total"  with lines ls 3


#     "tmp.data"  using  1:(($2)+($3))   every :::1::1  title "total"  with lines ls 3
     

set terminal png font "/usr/share/fonts/dejavu/DejaVuSans.ttf" size 1200,900
set output 'tmp.runtimes.png'
replot

set log y
set terminal png font "/usr/share/fonts/dejavu/DejaVuSans.ttf" size 1200,900
set output 'tmp.runtimes.log.png'
replot


unset log y

set title "Global Master"

plot "tmp.data"  using  1:2             every :::0::1  title "idle times"   with lines ls 1, \
     "tmp.data"  using  1:3             every :::0::1  title "busy times"   with lines ls 2, \
     "tmp.data"  using  1:(($2)+($3))   every :::0::1  title "total"  with lines ls 3
     

set terminal png font "/usr/share/fonts/dejavu/DejaVuSans.ttf" size 1200,900
set output 'tmp.runtimes.master.png'
replot

set log y
set terminal png font "/usr/share/fonts/dejavu/DejaVuSans.ttf" size 1200,900
set output 'tmp.runtimes.master.log.png'
replot

clear
