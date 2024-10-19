set terminal pdf
set output '../graph/Ring.pdf'
set title 'Message Size vs Time'
set xlabel 'Message Size (bytes)'
set ylabel 'Time (microseconds)'
set grid

set xtics (1, 1024, 1048576)

plot '../Ring/result.txt' using 1:2 with lines title '2node 8proc',
    '../ring_4node_4proc.txt' using 1:2 with lines title '4node 4proc'


