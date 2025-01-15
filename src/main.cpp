#include "Database.h"
#include "helpers.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Database db("db.json");
    std::string default_table;

    while (true) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) continue;

        std::vector<std::string> command;
        std::string part;
        for (char c : input) {
            if (c == ' ') {
                command.push_back(part);
                part.clear();
            } else {
                part += c;
            }
        }
        command.push_back(part);

        std::string cmd = command[0];
        if (cmd == "exit") break;
        else if (cmd == "help") print_help();
        else if (cmd == "list") {
            std::cout << "Таблицы в базе данных:" << std::endl;
            for (const auto& table : db.get_tables()) {
                std::cout << "  " << table.first << ": ";
                for (const auto& col : table.second.first) {
                    std::cout << col << " ";
                }
                std::cout << std::endl;
            }
        } else if (cmd == "create") {
            if (command.size() < 2) {
                std::cout << "Ошибка: недостаточно аргументов. Используйте: create <имя_таблицы> <колонки> или create <колонки>" << std::endl;
                continue;
            }
            if (command.size() == 2) {
                std::vector<std::string> columns;
                std::string cols_str = command[1];
                std::string col;
                for (char c : cols_str) {
                    if (c == ',') {
                        columns.push_back(col);
                        col.clear();
                    } else {
                        col += c;
                    }
                }
                columns.push_back(col);
                std::string table_name = "default_table";
                db.create_table(table_name, columns);
                default_table = table_name;
            } else {
                std::string table_name = command[1];
                std::vector<std::string> columns;
                std::string cols_str = command[2];
                std::string col;
                for (char c : cols_str) {
                    if (c == ',') {
                        columns.push_back(col);
                        col.clear();
                    } else {
                        col += c;
                    }
                }
                columns.push_back(col);
                db.create_table(table_name, columns);
                default_table = table_name;
            }
        } else if (cmd == "insert") {
            if (command.size() < 2) {
                std::cout << "Ошибка: недостаточно аргументов. Используйте: insert <имя_таблицы> <значения> или insert <значения>" << std::endl;
                continue;
            }
            if (command.size() == 2) {
                if (default_table.empty()) {
                    std::cout << "Ошибка: таблица по умолчанию не установлена. Сначала создайте таблицу." << std::endl;
                    continue;
                }
                std::string table_name = default_table;
                std::string values_str = command[1];
                std::vector<std::string> values;
                std::string val;
                for (char c : values_str) {
                    if (c == ',') {
                        values.push_back(val);
                        val.clear();
                    } else {
                        val += c;
                    }
                }
                values.push_back(val);
                db.insert(table_name, values);
            } else {
                std::string table_name = command[1];
                std::string values_str = command[2];
                std::vector<std::string> values;
                std::string val;
                for (char c : values_str) {
                    if (c == ',') {
                        values.push_back(val);
                        val.clear();
                    } else {
                        val += c;
                    }
                }
                values.push_back(val);
                db.insert(table_name, values);
            }
        } else if (cmd == "select") {
            if (command.size() < 2) {
                std::cout << "Ошибка: недостаточно аргументов. Используйте: select <имя_таблицы> [условие]" << std::endl;
                continue;
            }
            std::string table_name = command[1];
            if (command.size() < 3) {
                auto results = db.select(table_name);
                std::cout << "Результаты из таблицы " << table_name << ":" << std::endl;
                for (const auto& record : results) {
                    for (const auto& val : record) {
                        std::cout << val << " ";
                    }
                    std::cout << std::endl;
                }
            } else {
                std::string condition_str = command[2];
                auto results = db.select(table_name);
                std::cout << "Результаты из таблицы " << table_name << ":" << std::endl;
                for (const auto& record : results) {
                    for (const auto& val : record) {
                        std::cout << val << " ";
                    }
                    std::cout << std::endl;
                }
            }
        } else if (cmd == "debug") {
            db.print_tables();
        } else {
            std::cout << "Неизвестная команда: " << cmd << ". Введите 'help' для справки." << std::endl;
        }
    }
    return 0;
}