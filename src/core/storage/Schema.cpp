#include "Schema.h"

void Schema::addColumn(const std::string& name, DataType type, bool isNullable) {
    columns.push_back({name, type, isNullable});
}

const Schema::Column& Schema::getColumn(const std::string& name) const {
    for (const auto& col : columns) {
        if (col.name == name)
            return col;
    }
    throw std::out_of_range("Column not found");
}