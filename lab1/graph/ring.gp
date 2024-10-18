set terminal pdf
set output '../graph/Ring.pdf'
set title 'Message Size vs Time'
set xlabel 'Message Size (bytes)'
set ylabel 'Time (microseconds)'
set grid

set xtics (1, 1024, 1048576)
set ytics (0.000023, 0.000069, 0.000377)
plot '../Ring/result.txt' using 1:2 with lines title 'Time vs Message Size'


