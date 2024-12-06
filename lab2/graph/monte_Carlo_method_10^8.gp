#! /usr/bin/gnuplot -persist 

set colorsequence podo
set terminal png size 800, 600
set output "monte_Carlo_method_10^8.png"
set title "monte_Carlo_method (10^8)" font 'Calibri,18'
set xlabel "Proc" font 'Calibri,16'
set ylabel "Speedup" font 'Calibri,16'
set format y "%.1f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid

# Установка явных значений для xtics
set xtics (4, 16, 28, 40, 52, 64)
set xrange [4:64]

# Используем логарифмическую шкалу по оси Y
#set logscale y

# Построение графиков с данными из файлов
plot x title "Linear speedup" with linespoints  lw 2 pt 7 lc rgb 'red', \
     '../monte_Carlo_method_s_10^8' using 1:2 title "" with linespoints lw 2 pt 7 lc rgb 'blue'
     #'../monte_Carlo_method_1node_4proc_10^8' using 1:2 title "" with linespoints lw 2 pt 7 lc rgb 'blue', \
     #'../monte_Carlo_method_2node_8proc_10^8' using 1:2 title "node = 2 proc = 8" with linespoints lw 2 pt 7 lc rgb 'purple', \
     #'../monte_Carlo_method_4node_7proc_10^8' using 1:2 title "node = 4 proc = 7" with linespoints lw 2 pt 7 lc rgb 'green', \
     #'../monte_Carlo_method_4node_8proc_10^8' using 1:2 title "node = 4 proc = 8" with linespoints lw 2 pt 7 lc rgb 'black'