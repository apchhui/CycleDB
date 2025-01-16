#include "../include/Database.h"
#include <cassert>
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Database db("test_db.json");

    db.create_table("users", {"id", "name", "email"});
    assert(db.get_tables().count("users") == 1);

    db.insert("users", {"1", "Alice", "alice@example.com"});
    auto results = db.select("users");
    assert(results.size() == 1);
    assert(results[0][1] == "Alice");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
