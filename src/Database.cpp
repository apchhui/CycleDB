#include "../include/Database.h"
#include <iostream>
#include <fstream>

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& vec) {
    for (const auto& item : vec) {
        os << item << " ";
    }
    return os;
}

Database::Database(const std::string& db_name) : db_name(db_name) {
    load();
}


void Database::create_table(const std::string& table_name, const std::vector<std::string>& columns) {
    if (tables.find(table_name) != tables.end()) {
        std::cout << "Таблица " << table_name << " уже существует." << std::endl;
        return;
    }
    if (columns.empty()) {
        std::cout << "Ошибка: таблица должна иметь хотя бы одну колонку." << std::endl;
        return;
    }
    tables[table_name] = {columns, {}};
    std::cout << "Таблица " << table_name << " создана." << std::endl;
    save();
}

void Database::insert(const std::string& table_name, const std::vector<std::string>& record) {
    if (tables.find(table_name) == tables.end()) {
        std::cout << "Таблица " << table_name << " не существует." << std::endl;
        return;
    }
    const auto& columns = tables[table_name].first;
    if (record.size() != columns.size()) {
        std::cout << "Ошибка: количество полей не совпадает с колонками таблицы." << std::endl;
        return;
    }
    tables[table_name].second.push_back(record);
    std::cout << "Запись " << record << " добавлена в таблицу " << table_name << "." << std::endl;
    save();
}

std::vector<std::vector<std::string>> Database::select(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition) {
    if (tables.find(table_name) == tables.end()) {
        std::cout << "Таблица " << table_name << " не существует." << std::endl;
        return {};
    }
    const auto& data = tables[table_name].second;
    if (!condition) {
        return data;
    }
    std::vector<std::vector<std::string>> result;
    for (const auto& record : data) {
        if (condition(record)) {
            result.push_back(record);
        }
    }
    return result;
}

void Database::update(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition, const std::vector<std::string>& new_values) {
    if (tables.find(table_name) == tables.end()) {
        std::cout << "Таблица " << table_name << " не существует." << std::endl;
        return;
    }
    auto& data = tables[table_name].second;
    for (auto& record : data) {
        if (condition(record)) {
            record = new_values;
        }
    }
    std::cout << "Записи в таблице " << table_name << " обновлены." << std::endl;
    save();
}

void Database::delete_records(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition) {
    if (tables.find(table_name) == tables.end()) {
        std::cout << "Таблица " << table_name << " не существует." << std::endl;
        return;
    }
    auto& data = tables[table_name].second;
    data.erase(std::remove_if(data.begin(), data.end(), condition), data.end());
    std::cout << "Записи из таблицы " << table_name << " удалены." << std::endl;
    save();
}

void Database::save() {
    try {
        json j;
        for (const auto& table : tables) {
            json table_json;
            table_json["columns"] = table.second.first;
            json data_json = json::array();
            for (const auto& record : table.second.second) {
                data_json.push_back(record);
            }
            table_json["data"] = data_json;
            j[table.first] = table_json;
        }
        std::ofstream file(db_name);
        file << j.dump(4);
        std::cout << "База данных сохранена в файл " << db_name << "." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при сохранении базы данных: " << e.what() << std::endl;
    }
}

void Database::load() {
    if (std::ifstream file(db_name); file.good()) {
        try {
            json j;
            file >> j;
            tables.clear();
            for (auto it = j.begin(); it != j.end(); ++it) {
                std::string table_name = it.key();
                std::vector<std::string> columns = it.value()["columns"];
                std::vector<std::vector<std::string>> data = it.value()["data"];
                tables[table_name] = {columns, data};
            }
            std::cout << "База данных загружена из файла " << db_name << "." << std::endl;
        } catch (const json::exception& e) {
            std::cerr << "Ошибка при загрузке базы данных: " << e.what() << std::endl;
            tables.clear();
        }
    } else {
        tables.clear();
        std::cout << "Файл " << db_name << " не существует или пуст. Создана новая база данных." << std::endl;
    }
}

void Database::print_tables() {
    std::cout << json(tables).dump(4) << std::endl;
}

const std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>>& Database::get_tables() const {
    return tables;
}