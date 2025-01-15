#include "Record.h"

namespace db {

    Record::Record(int id) : recordId(id) {}

    Record::~Record() {}

    int Record::getRecordId() const {
        return recordId;
    }

    std::string Record::getValue(const std::string& fieldName) const {
        auto it = fields.find(fieldName);
        if (it != fields.end()) {
            return it->second;
        }
        return "";
    }

    void Record::setValue(const std::string& fieldName, const std::string& value) {
        fields[fieldName] = value;
    }

}