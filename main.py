import json
import os

class Database:
    def __init__(self, db_name):
        self.db_name = db_name
        self.tables = {}
        self.load()

    def create_table(self, table_name, columns):
        if table_name in self.tables:
            print(f"Таблица {table_name} уже существует.")
            return
        if not columns:
            print("Ошибка: таблица должна иметь хотя бы одну колонку.")
            return
        self.tables[table_name] = {
            "columns": columns,
            "data": []
        }
        print(f"Таблица {table_name} создана.")
        self.save()

    def insert(self, table_name, record):
        if table_name not in self.tables:
            print(f"Таблица {table_name} не существует.")
            return
        columns = self.tables[table_name]["columns"]
        if len(record) != len(columns):
            print("Ошибка: количество полей не совпадает с колонками таблицы.")
            return
        self.tables[table_name]["data"].append(record)
        print(f"Запись {record} добавлена в таблицу {table_name}.")
        self.save()

    def select(self, table_name, condition=None):
        if table_name not in self.tables:
            print(f"Таблица {table_name} не существует.")
            return []
        data = self.tables[table_name]["data"]
        if condition:
            return [record for record in data if condition(record)]
        return data

    def update(self, table_name, condition, new_values):
        if table_name not in self.tables:
            print(f"Таблица {table_name} не существует.")
            return
        data = self.tables[table_name]["data"]
        for record in data:
            if condition(record):
                for i, value in enumerate(new_values):
                    record[i] = value
        print(f"Записи в таблице {table_name} обновлены.")
        self.save()

    def delete(self, table_name, condition):
        if table_name not in self.tables:
            print(f"Таблица {table_name} не существует.")
            return
        self.tables[table_name]["data"] = [
            record for record in self.tables[table_name]["data"] if not condition(record)
        ]
        print(f"Записи из таблицы {table_name} удалены.")
        self.save()

    def save(self):
        try:
            with open(self.db_name, "w") as file:
                json.dump(self.tables, file, indent=4)
            print(f"База данных сохранена в файл {self.db_name}.")
        except IOError as e:
            print(f"Ошибка при сохранении базы данных: {e}")

    def load(self):
        if os.path.exists(self.db_name) and os.path.getsize(self.db_name) > 0:
            try:
                with open(self.db_name, "r") as file:
                    self.tables = json.load(file)
                print(f"База данных загружена из файла {self.db_name}.")
            except json.JSONDecodeError as e:
                print(f"Ошибка при загрузке базы данных: {e}")
                self.tables = {}
        else:
            self.tables = {}
            print(f"Файл {self.db_name} не существует или пуст. Создана новая база данных.")

    def print_tables(self):
        print(json.dumps(self.tables, indent=4))

def print_help():
    print("Доступные команды:")
    print("  create <имя_таблицы> <колонка1,колонка2,...> - Создать таблицу")
    print("  create <колонка1,колонка2,...> - Создать таблицу с именем по умолчанию")
    print("  insert <имя_таблицы> <значение1,значение2,...> - Вставить запись")
    print("  insert <значение1,значение2,...> - Вставить запись в таблицу по умолчанию")
    print("  select <имя_таблицы> [условие] - Выбрать записи")
    print("  update <имя_таблицы> <условие> <новые_значения> - Обновить записи")
    print("  delete <имя_таблицы> <условие> - Удалить записи")
    print("  list - Показать все таблицы")
    print("  debug - Показать внутреннее состояние базы данных")
    print("  help - Показать справку")
    print("  exit - Выйти из программы")

def main():
    db = Database("db.json")
    default_table = None  # Таблица по умолчанию

    while True:
        command = input("> ").strip().split()
        if not command:
            continue

        cmd = command[0].lower()
        if cmd == "exit":
            break
        elif cmd == "help":
            print_help()
        elif cmd == "list":
            print("Таблицы в базе данных:")
            for table_name, table_data in db.tables.items():
                print(f"  {table_name}: {table_data['columns']}")
        elif cmd == "create":
            if len(command) < 2:
                print("Ошибка: недостаточно аргументов. Используйте: create <имя_таблицы> <колонки> или create <колонки>")
                continue

            # Определяем, есть ли имя таблицы
            if len(command) == 2:
                # Формат: create <колонки>
                columns = [col.strip() for col in command[1].split(",")]
                table_name = "default_table"  # Имя таблицы по умолчанию
            else:
                # Формат: create <имя_таблицы> <колонки>
                table_name = command[1]
                columns = [col.strip() for col in command[2].split(",")]

            db.create_table(table_name, columns)
            default_table = table_name  # Устанавливаем таблицу по умолчанию

        elif cmd == "insert":
            if len(command) < 2:
                print("Ошибка: недостаточно аргументов. Используйте: insert <имя_таблицы> <значения> или insert <значения>")
                continue

            # Определяем, есть ли имя таблицы
            if len(command) == 2:
                # Формат: insert <значения>
                if not default_table:
                    print("Ошибка: таблица по умолчанию не установлена. Сначала создайте таблицу.")
                    continue
                table_name = default_table
                values = [val.strip() for val in command[1].split(",")]
            else:
                # Формат: insert <имя_таблицы> <значения>
                table_name = command[1]
                values = [val.strip() for val in command[2].split(",")]

            db.insert(table_name, values)

        elif cmd == "select":
            if len(command) < 2:
                print("Ошибка: недостаточно аргументов. Используйте: select <имя_таблицы> [условие]")
                continue
            table_name = command[1]
            condition = None
            if len(command) > 2:
                condition_str = " ".join(command[2:])
                try:
                    condition = lambda x: eval(condition_str, {}, {"x": x})
                except Exception as e:
                    print(f"Ошибка в условии: {e}")
                    continue
            results = db.select(table_name, condition)
            print(f"Результаты из таблицы {table_name}:")
            for record in results:
                print(record)

        elif cmd == "debug":
            db.print_tables()
        else:
            print(f"Неизвестная команда: {cmd}. Введите 'help' для справки.")

if __name__ == "__main__":
    main()