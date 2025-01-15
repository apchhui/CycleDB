import os

def count_lines_of_code(path, extensions=None):
    total_lines = 0
    extensions = extensions or ['.cpp', '.h']  # Укажите нужные расширения
    for root, _, files in os.walk(path):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                with open(os.path.join(root, file), 'r', encoding='utf-8', errors='ignore') as f:
                    total_lines += sum(1 for _ in f)
    return total_lines

path_to_project = r"C:\Users\apchhui\Documents\cycle\products\CycleDB\src"
lines = count_lines_of_code(path_to_project)
print(f"Количество строк кода: {lines}")
