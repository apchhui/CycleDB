#ifndef INDEX_H
#define INDEX_H

#include <map>
#include <string>
#include "Record.h"

namespace db {
    class Index {
    public:
        Index(const std::string& fieldName);
        ~Index();

        void insertRecord(const db::Record& record);
        void deleteRecord(int recordId);
        std::map<int, db::Record> search(const std::string& key) const;

    private:
        std::string indexFieldName;
        std::map<std::string, std::map<int, db::Record>> indexData;
    };
}

#endif