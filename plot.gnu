# plot.gnu
set terminal png size 800,600
set output "test/average_time_vs_tellers.png"

set title "Average Time in Bank vs Number of Tellers"
set xlabel "Number of Tellers"
set ylabel "Average Time in Bank (minutes)"
set grid

set style line 1 lc rgb "blue" lt 1 lw 2 pt 7 ps 1.5

plot "test/results.txt" using 1:2 with linespoints linestyle 1 title "Avg Time"
