#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <stdexcept>

namespace db {
    enum class DataType {
        INT,
        FLOAT,
        STRING,
        BOOL,
        DATE
    };

    class Value {
    public:
        DataType type;
        std::string data;

        Value(int val);
        Value(float val);
        Value(const std::string& val);
        Value(bool val);

        int asInt() const;
        float asFloat() const;
        std::string asString() const;
        bool asBool() const;
    };
}

#endif // VALUE_H