import matplotlib.pyplot as plt

# Данные из трех файлов
data1 = [(1, 0.038559), (1024, 0.000085), (1048576, 0.01422)]
data2 = [(1, 0.028127), (1024, 0.000892 ), (1048576, 0.007614)]
data3 = [(1, 0.023617), (1024, 0.000143), (1048576, 0.009293)]

# Разбираем данные на отдельные массивы для каждой серии
x1, y1 = zip(*data1)
x2, y2 = zip(*data2)
x3, y3 = zip(*data3)

# Создаем график
plt.figure(figsize=(8, 6))  # Размер изображения

# Построение каждой линии
plt.plot(x1, y1, label="node = 2 proc = 8", marker='o', color='red')
plt.plot(x2, y2, label="node = 4 proc = 4", marker='o', color='blue')
plt.plot(x3, y3, label="node = 8 proc = 2", marker='o', color='purple')

# Установка меток осей
plt.xlabel("Count (bytes)")
plt.ylabel("Time (seconds)")

# Использование логарифмической шкалы для оси X
plt.xscale('log')

# Установка меток по оси X
plt.xticks([1, 1024, 1048576], ['1', '1024', '1048576'])

# Установка диапазона по оси Y
#plt.ylim(0, 0.03)  # Ограничение по Y

# Настройка формата меток по оси Y
plt.gca().yaxis.set_major_formatter(plt.FormatStrFormatter('%.6f'))

# Включаем сетку
plt.grid(True)

# Заголовок и легенда
plt.title("Ring")
plt.legend()

# Сохраняем график как изображение
plt.savefig('ring_plot.png')

# Показать график
plt.show()
