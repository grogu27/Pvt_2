#! /usr/bin/gnuplot -persist 

set colorsequence podo
set terminal png size 800, 600
set output "middle_rectangle_method.png"
set title "middle_rectangle_method (a = 1 b = 1.2 eps = 1E-6)" font 'Calibri,18'
set xlabel "Count (bytes)" font 'Calibri,16'
set ylabel "Time (seconds)" font 'Calibri,16'
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
     '../middle_rectangle_method_s' using 1:2 title "node = 4 proc = 4" with linespoints lw 2 pt 7 lc rgb 'blue'
     
