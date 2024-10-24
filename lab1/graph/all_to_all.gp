set colorsequence podo
set terminal png size 800, 600
set output "all_to_all.png"
set title "all_to_all" font 'Calibri,18'
set xlabel "Count (bytes)" font 'Calibri,16'
set ylabel "Time (seconds)" font 'Calibri,16'
set format y "%.7f"
set format x "%.0f"
set xtics font 'Calibri,12'
set ytics font 'Calibri,12'
set grid

# Установка явных значений для xtics
set xtics (1024)
set xrange [1:1048576]   # Устанавливаем диапазон по оси X от 1 до 1048576

# Используем логарифмическую шкалу по оси Y
#set logscale x

# Построение графиков с данными из файлов
plot '../all_to_all_4node_4proc' using 1:2 title "node = 4 proc = 4" with linespoints lw 2 pt 7 lc rgb 'blue', \
     '../all_to_all_4node_8proc' using 1:2 title "node = 4 proc = 8" with linespoints lw 2 pt 7 lc rgb 'purple'
