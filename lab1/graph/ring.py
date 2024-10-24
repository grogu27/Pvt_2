import matplotlib.pyplot as plt
import numpy as np

# Загрузка данных из файлов
def load_data(filename):
    x, y = [], []
    with open(filename, 'r') as f:
        for line in f:
            values = line.split()
            if len(values) == 2:
                x_value = float(values[0])
                y_value = float(values[1])
                # Игнорируем точки с y = 1024 и x = 0
                if x_value != 0 and y_value != 1024:
                    x.append(x_value)
                    y.append(y_value)
    return x, y

# Загрузка данных из файлов
x1, y1 = load_data('../ring_2node_8proc')
x2, y2 = load_data('../ring_4node_4proc')
x3, y3 = load_data('../ring_8node_2proc')

# Отладочные выводы
print(f"Data from '../ring_2node_8proc': {len(x1)} points")
print(f"Data from '../ring_4node_4proc': {len(x2)} points")
print(f"Data from '../ring_8node_2proc': {len(x3)} points")

# Настройка графика
plt.figure(figsize=(8, 6))
plt.title('Ring', fontsize=18)
plt.xlabel('Count (bytes)', fontsize=16)
plt.ylabel('Time (seconds)', fontsize=16)
plt.grid()

# Интерполяция для более плавной линии
x_values = [1, 1024, 1048576]
for x_data, y_data, label, color in zip(
    [x1, x2, x3], 
    [y1, y2, y3], 
    ['node = 2 proc = 8', 'node = 4 proc = 4', 'node = 8 proc = 2'], 
    ['red', 'blue', 'purple']
):
    # Интерполяция
    x_interp = np.linspace(min(x_data), max(x_data), 100)
    y_interp = np.interp(x_interp, x_data, y_data)
    plt.plot(x_interp, y_interp, label=label, linewidth=2, color=color)

# Установка формата осей
plt.xscale('linear')
plt.xlim(1, 1048576)  # Устанавливаем диапазон по оси X от 1 до 1048576
plt.ylim(bottom=0)    # Устанавливаем нижний предел по оси Y

# Установка меток оси X
plt.xticks([1, 1024, 1048576])  # Явное указание меток по оси X

# Добавление легенды
plt.legend(fontsize=12)

# Сохранение графика
plt.savefig('ring.png')
plt.show()
