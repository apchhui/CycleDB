#include "Record.h"

namespace db {

    Record::Record() : recordId(-1) {}

    Record::Record(int id) : recordId(id) {}

    Record::~Record() {}

    int Record::getRecordId() const {
        return recordId;
    }

    Value Record::getValue(const std::string& fieldName) const {
        auto it = fields.find(fieldName);
        if (it != fields.end())
            return it->second;
        throw std::out_of_range("Field not found");
    }

    void Record::setValue(const std::string& fieldName, const Value& value) {
        fields[fieldName] = value;
    }

}