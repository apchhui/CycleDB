#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <map>
#include <string>
#include "Record.h"
#include "Index.h"

namespace db {
    class Table {
    public:
        Table(const std::string& name);
        ~Table();

        void insertRecord(const db::Record& record);
        void deleteRecord(int recordId);
        void updateRecord(int recordId, const std::map<std::string, std::string>& newValues);
        db::Record getRecord(int recordId) const;

        void addIndex(const std::string& fieldName);
        std::map<int, db::Record> searchIndex(const std::string& fieldName, const std::string& key) const;

    private:
        std::string tableName;
        std::vector<db::Record> records;
        std::map<std::string, db::Index> indexes;
        int nextRecordId;
    };
}

#endif