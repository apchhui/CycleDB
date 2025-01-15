#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "Record.h"
#include "Schema.h"
#include "Index.h"

namespace db {
    class Table {
    public:
        Table(const std::string& name, const Schema& schema);
        void insertRecord(const Record& record);
        void deleteRecord(int recordId);
        void updateRecord(int recordId, const std::map<std::string, Value>& newValues);
        Record getRecord(int recordId) const;
        void addIndex(const std::string& fieldName);

    private:
        std::string tableName;
        Schema schema;
        std::vector<Record> records;
        std::map<std::string, Index> indexes;
        int nextRecordId;
    };
}

#endif // TABLE_H