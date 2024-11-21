import os

# Папка с входными файлами
input_folder = "res/28000"  # Укажите путь к папке с файлами
output_file = "graph/res_28000.txt"  # Файл для сохранения результатов

# Очистка выходного файла
with open(output_file, "w") as outfile:
    outfile.write("")  # Удаляем содержимое файла, если он уже существует

# Получение списка файлов в папке
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

    # Если нашли данные, записываем их в выходной файл
    if proc_count is not None and elapsed_time is not None:
        with open(output_file, "a") as outfile:
            outfile.write(f"{proc_count} {elapsed_time}\n")
        print(f"Обработан файл: {filename}")
    else:
        print(f"Не удалось извлечь данные из файла: {filename}")

print(f"Все данные сохранены в файл: {output_file}")
