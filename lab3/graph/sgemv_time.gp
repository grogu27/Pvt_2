#! /usr/bin/gnuplot -persist 

set colorsequence podo
set terminal png size 800, 600
set output "graph/sgemv_time.png"
set title "sgemv" font 'Calibri,18'
set xlabel "Proc" font 'Calibri,16'
set ylabel "Time (s)" font 'Calibri,16'
set format y "%.1f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid


# Установка явных значений для xtics
set xtics (1, 8, 16, 24)
#set xrange [4:64]

# Используем логарифмическую шкалу по оси Y
#set logscale y

# Построение графиков с данными из файлов
plot 'graph/res_28000.txt' using 1:2 title "n = 28000, Memory used: 2990 MiB" with linespoints lw 2 pt 7 lc rgb 'black', \
     'graph/res_45000.txt' using 1:2 title "n = 45000, Memory used: 7725 MiB" with linespoints lw 2 pt 7 lc rgb 'green'
 

     
