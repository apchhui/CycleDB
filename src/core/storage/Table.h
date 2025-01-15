#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "Record.h"

namespace db {
    class Table {
    public:
        Table(const std::string& name);
        int getNextRecordID();
        void insertRecord(const Record& record);
        void updateRecord(int recordID, const Record& newRecord);
        void deleteRecord(int recordID);

    private:
        std::string tableName;
        std::vector<Record> records;
        int nextRecordId;
    };
}

#endif // TABLE_H