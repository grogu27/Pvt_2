import os

# Папка с входными файлами
input_folder = "res/5000"  # Укажите путь к папке с файлами
output_file = "graph/res_5000_speedup.txt"  # Файл для сохранения результатов

# Очистка выходного файла
with open(output_file, "w") as outfile:
    outfile.write("")  # Удаляем содержимое файла, если он уже существует

# Переменная для хранения времени выполнения с одним процессом
single_thread_time = None

# Первый проход: находим время выполнения для одного потока
for filename in os.listdir(input_folder):
    input_path = os.path.join(input_folder, filename)

    # Проверяем, что это файл
    if not os.path.isfile(input_path):
        continue

    # Переменные для хранения данных
    proc_count = None
    elapsed_time = None

    # Открываем и читаем файл
    with open(input_path, "r") as infile:
        lines = infile.readlines()

    # Ищем нужные строки
    for line in lines:
        if line.startswith("Count proc:"):
            proc_count = int(line.split(":")[1].strip())
        elif line.startswith("Elapsed time"):
            elapsed_time = float(line.split(":")[1].split()[0].strip())

    # Если это файл с одним процессом, сохраняем время
    if proc_count == 1:
        single_thread_time = elapsed_time
        print(f"Обнаружено время выполнения с одним процессом: {single_thread_time} сек. (файл: {filename})")
        break

# Проверяем, что время для одного потока найдено
if single_thread_time is None:
    print("Время выполнения с одним процессом не найдено. Программа завершена.")
    exit()

# Второй проход: обрабатываем остальные файлы
for filename in os.listdir(input_folder):
    input_path = os.path.join(input_folder, filename)

    # Проверяем, что это файл
    if not os.path.isfile(input_path):
        continue

    # Переменные для хранения данных
    proc_count = None
    elapsed_time = None

    # Открываем и читаем файл
    with open(input_path, "r") as infile:
        lines = infile.readlines()

    # Ищем нужные строки
    for line in lines:
        if line.startswith("Count proc:"):
            proc_count = int(line.split(":")[1].strip())
        elif line.startswith("Elapsed time"):
            elapsed_time = float(line.split(":")[1].split()[0].strip())

    # Пропускаем файл с одним процессом
    if proc_count == 1:
        continue

    # Вычисляем ускорение и записываем в выходной файл
    if proc_count is not None and elapsed_time is not None:
        speedup = single_thread_time / elapsed_time
        with open(output_file, "a") as outfile:
            outfile.write(f"{proc_count} {speedup:.2f}\n")
        print(f"Обработан файл: {filename} | Proc: {proc_count}, Speedup: {speedup:.2f}")

print(f"Все данные сохранены в файл: {output_file}")
