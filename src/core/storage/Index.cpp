#include "Index.h"

namespace db {

    Index::Index(const std::string& fieldName) : indexFieldName(fieldName) {}

    Index::~Index() {}

    void Index::insertRecord(const db::Record& record) {
        std::string keyValue = record.getValue(indexFieldName);
        indexData[keyValue][record.getRecordId()] = record;
    }

    void Index::deleteRecord(int recordId) {
        for (auto& pair : indexData) {
            pair.second.erase(recordId);
        }
    }

    std::map<int, db::Record> Index::search(const std::string& key) const {
        auto it = indexData.find(key);
        if (it != indexData.end()) {
            return it->second;
        }
        return {};
    }

}