#include "Table.h"
#include <algorithm>

namespace db {

    Table::Table(const std::string& name, const Schema& schema)
        : tableName(name), schema(schema), nextRecordId(1) {}

    void Table::insertRecord(const Record& record) {
        // Validate record against schema
        records.push_back(Record(nextRecordId));
        // Update indexes
        ++nextRecordId;
    }

    void Table::deleteRecord(int recordId) {
        records.erase(std::remove_if(records.begin(), records.end(),
            [recordId](const Record& r) { return r.getRecordId() == recordId; }), records.end());
        // Update indexes
    }

    void Table::updateRecord(int recordId, const std::map<std::string, Value>& newValues) {
        // Find and update record
        // Update indexes
    }

    Record Table::getRecord(int recordId) const {
        // Find and return record
        return Record(-1); // Placeholder
    }

    void Table::addIndex(const std::string& fieldName) {
        // Create and add index
    }

}