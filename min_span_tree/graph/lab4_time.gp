#! /usr/bin/gnuplot -persist

set terminal svg size 800, 600
set output "graph/sgemv_time.svg"

set colorsequence podo
set title "MST" font 'Calibri,18'
set xlabel "Proc (n)" font 'Calibri,16'
set ylabel "Time (s)" font 'Calibri,16'
set format y "%.1f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid

# Установка явных значений для xtics
set xtics ("1" 1, "8" 8, "16" 16, "24" 24, "32" 32)

# Построение графиков с данными из файлов
plot 'graph/res_1000.txt' using 1:2 title "n = 1000" with linespoints lw 2 pt 7 lc rgb 'black', \
     'graph/res_3000.txt' using 1:2 title "n = 3000" with linespoints lw 2 pt 7 lc rgb 'green', \
     'graph/res_5000.txt' using 1:2 title "n = 5000" with linespoints lw 2 pt 7 lc rgb 'blue', \
     'graph/res_8000.txt' using 1:2 title "n = 8000" with linespoints lw 2 pt 7 lc rgb 'gray', \
     'graph/res_10000.txt' using 1:2 title "n = 10000" with linespoints lw 2 pt 7 lc rgb 'yellow'
