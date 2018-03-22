set style line 1 lc rgb 'black' pt 5   # square
set style line 2 lc rgb 'black' pt 7   # circle
set style line 3 lc rgb 'black' pt 9   # triangle
set xlabel '#threads'
set ylabel 'bandwidth(GB/s)' #offset 2,1 rotate by 0

# gnuplot -e "set style line 1 lc rgb 'black' pt 5; set terminal dumb; set xlabel '#threads'; set ylabel 'bandwidth(GB/s)'; plot for[col=2:2] '/dev/shm/mytempfile' using 1:col title columnheader(col) with points ls 1"
# gnuplot -e "set style line 1 lc rgb 'black' pt 5; set terminal dumb; set xlabel '#threads'; set ylabel 'bandwidth(GB/s)'; plot for[col=2:2] 'README.md' using 1:col title columnheader(col) with lines;"
gnuplot -e "set style line 1 lc rgb 'black' pt 5; set terminal png; set output 'result.png'; set xlabel '#threads'; set ylabel 'bandwidth(GB/s)'; plot for[col=2:2] '/dev/shm/mytempfile' using 1:col title columnheader(col) with points ls 1;"

