#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Database {
public:
    Database(const std::string& db_name);
    void create_table(const std::string& table_name, const std::vector<std::string>& columns);
    void insert(const std::string& table_name, const std::vector<std::string>& record);
    std::vector<std::vector<std::string>> select(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition = nullptr);
    void update(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition, const std::vector<std::string>& new_values);
    void delete_records(const std::string& table_name, std::function<bool(const std::vector<std::string>&)> condition);
    void save();
    void load();
    void print_tables();

    const std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>>& get_tables() const;

private:
    std::string db_name;
    std::map<std::string, std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>> tables;
};

#endif