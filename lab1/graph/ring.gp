#! /usr/bin/gnuplot -persist 


set colorsequence podo
# Установка параметров графика
set terminal png size 800, 600
set output "ring.png"
set title "Ring" font 'Calibri,18'
set xlabel "Count (bytes)" font 'Calibri,16'
set ylabel "Time (seconds)" font 'Calibri,16'
set format y "%.6f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid

# Установка явных значений для xtics без 0
set xtics (1, 1024, 1048576)
set xrange [0:1048576]   # Устанавливаем диапазон по оси X от 1 до 1048576
set yrange [0:*]         # Устанавливаем диапазон по оси Y от 0 до максимума

# Построение графиков с данными из файла
plot '../ring_2node_8proc' using 1:2 title "node = 2 proc = 8" with linespoints lw 2 pt 7 lc rgb 'red', \
     '../ring_4node_4proc' using 1:2 title "node = 4 proc = 4" with linespoints lw 2 pt 7 lc rgb 'blue', \
     '../ring_8node_2proc' using 1:2 title "node = 8 proc = 2" with linespoints lw 2 pt 7 lc rgb 'purple'
