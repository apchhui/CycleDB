#ifndef SCHEMA_H
#define SCHEMA_H

#include <vector>
#include <string>
#include "core/storage/Value.h"

namespace db {
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
}

#endif // SCHEMA_H