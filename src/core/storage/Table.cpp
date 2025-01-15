#include "Table.h"

namespace db {

    Table::Table(const std::string& name)
        : tableName(name), nextRecordId(1) {}

    int Table::getNextRecordID() {
        return nextRecordId++;
    }

    void Table::insertRecord(const Record& record) {
        // Implement insert logic
    }

    void Table::updateRecord(int recordID, const Record& newRecord) {
        // Implement update logic
    }

    void Table::deleteRecord(int recordID) {
        // Implement delete logic
    }

}