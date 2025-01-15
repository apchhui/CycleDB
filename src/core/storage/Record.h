#ifndef RECORD_H
#define RECORD_H

#include <map>
#include <string>
#include "Value.h"

namespace db {
    class Record {
    public:
        Record();
        Record(int id);
        ~Record();

        int getRecordId() const;
        Value getValue(const std::string& fieldName) const;
        void setValue(const std::string& fieldName, const Value& value);

    private:
        int recordId;
        std::map<std::string, Value> fields;
    };
}

#endif // RECORD_H