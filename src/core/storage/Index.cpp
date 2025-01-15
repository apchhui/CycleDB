#include "Index.h"

namespace db {

    Index::Index(const std::string& fieldName) : indexFieldName(fieldName) {}

    void Index::insertRecord(const Record& record) {
        std::string keyValue = record.getValue(indexFieldName).asString();
        indexData[keyValue][record.getRecordId()] = record;
    }

    void Index::deleteRecord(int recordId) {
        // Remove from index
    }

    std::map<int, Record> Index::search(const std::string& key) const {
        auto it = indexData.find(key);
        if (it != indexData.end())
            return it->second;
        return {};
    }

}