#ifndef RECORD_H
#define RECORD_H

#include <map>
#include <string>

namespace db {
    class Record {
    public:
        Record(int id);
        ~Record();

        int getRecordId() const;
        std::string getValue(const std::string& fieldName) const;
        void setValue(const std::string& fieldName, const std::string& value);

    private:
        int recordId;
        std::map<std::string, std::string> fields;
    };
}

#endif