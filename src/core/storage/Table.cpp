#include "Table.h"
#include <algorithm>

namespace db {

    Table::Table(const std::string& name) : tableName(name), nextRecordId(1) {}

    Table::~Table() {}

    void Table::insertRecord(const db::Record& record) {
        records.push_back(record);
        for (auto& index : indexes) {
            index.second.insertRecord(record);
        }
        ++nextRecordId;
    }

    void Table::deleteRecord(int recordId) {
        records.erase(
            std::remove_if(records.begin(), records.end(),
                [recordId](const db::Record& r) { return r.getRecordId() == recordId; }),
            records.end());
        for (auto& index : indexes) {
            index.second.deleteRecord(recordId);
        }
    }

    void Table::updateRecord(int recordId, const std::map<std::string, std::string>& newValues) {
        for (auto& record : records) {
            if (record.getRecordId() == recordId) {
                for (const auto& pair : newValues) {
                    record.setValue(pair.first, pair.second);
                }
                break;
            }
        }
        for (auto& index : indexes) {
            auto it = std::find_if(records.begin(), records.end(),
                [recordId](const db::Record& r) { return r.getRecordId() == recordId; });
            if (it != records.end()) {
                index.second.insertRecord(*it);
            }
        }
    }

    db::Record Table::getRecord(int recordId) const {
        for (const auto& record : records) {
            if (record.getRecordId() == recordId) {
                return record;
            }
        }
        return db::Record(-1);
    }

    void Table::addIndex(const std::string& fieldName) {
        indexes[fieldName] = db::Index(fieldName);
        for (const auto& record : records) {
            indexes[fieldName].insertRecord(record);
        }
    }

    std::map<int, db::Record> Table::searchIndex(const std::string& fieldName, const std::string& key) const {
        auto it = indexes.find(fieldName);
        if (it != indexes.end()) {
            return it->second.search(key);
        }
        return {};
    }

}