#include "../include/helpers.h"
#include <iostream>

void print_help() {
    std::cout << "Доступные команды:" << std::endl;
    std::cout << "  create <имя_таблицы> <колонка1,колонка2,...> - Создать таблицу" << std::endl;
    std::cout << "  create <колонка1,колонка2,...> - Создать таблицу с именем по умолчанию" << std::endl;
    std::cout << "  insert <имя_таблицы> <значение1,значение2,...> - Вставить запись" << std::endl;
    std::cout << "  insert <значение1,значение2,...> - Вставить запись в таблицу по умолчанию" << std::endl;
    std::cout << "  select <имя_таблицы> [условие] - Выбрать записи" << std::endl;
    std::cout << "  update <имя_таблицы> <условие> <новые_значения> - Обновить записи" << std::endl;
    std::cout << "  delete <имя_таблицы> <условие> - Удалить записи" << std::endl;
    std::cout << "  list - Показать все таблицы" << std::endl;
    std::cout << "  debug - Показать внутреннее состояние базы данных" << std::endl;
    std::cout << "  help - Показать справку" << std::endl;
    std::cout << "  exit - Выйти из программы" << std::endl;
}