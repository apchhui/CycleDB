#ifndef SCHEMA_H
#define SCHEMA_H

#include <vector>
#include <string>
#include "DataType.h"

class Schema {
public:
    struct Column {
        std::string name;
        DataType type;
        bool isNullable;
    };

    void addColumn(const std::string& name, DataType type, bool isNullable = false);
    const Column& getColumn(const std::string& name) const;

private:
    std::vector<Column> columns;
};

#endif // SCHEMA_H