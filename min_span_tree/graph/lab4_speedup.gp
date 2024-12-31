#! /usr/bin/gnuplot -persist 

set colorsequence podo
set terminal svg size 800, 600
set output "graph/sgemv_speedup.svg"
set title "MST" font 'Calibri,18'
set xlabel "Proc (n)" font 'Calibri,16'
set ylabel "Speedup (S)" font 'Calibri,16'
set format y "%.1f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid


# Установка явных значений для xtics
set xtics (1, 8, 16, 24, 32)
#set xrange [4:64]
set yrange [:32]

# Используем логарифмическую шкалу по оси Y
#set logscale y
set key left top
# Построение графиков с данными из файлов
plot x title "Linear speedup" with linespoints  lw 2 pt 7 lc rgb 'red', \
     'graph/res_1000_speedup.txt' using 1:2 title "n = 1000" with linespoints lw 2 pt 7 lc rgb 'black', \
     'graph/res_3000_speedup.txt' using 1:2 title "n = 3000" with linespoints lw 2 pt 7 lc rgb 'green', \
     'graph/res_5000_speedup.txt' using 1:2 title "n = 5000" with linespoints lw 2 pt 7 lc rgb 'blue', \
     'graph/res_8000_speedup.txt' using 1:2 title "n = 8000" with linespoints lw 2 pt 7 lc rgb 'gray', \
     'graph/res_10000_speedup.txt' using 1:2 title "n = 10000" with linespoints lw 2 pt 7 lc rgb 'yellow'
 

     
