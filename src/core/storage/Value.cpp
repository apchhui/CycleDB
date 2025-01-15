#include "Value.h"

db::Value::Value(int val)
    : type(DataType::INT), data(std::to_string(val)) {}

db::Value::Value(float val)
    : type(DataType::FLOAT), data(std::to_string(val)) {}

db::Value::Value(const std::string& val)
    : type(DataType::STRING), data(val) {}

db::Value::Value(bool val)
    : type(DataType::BOOL), data(val ? "true" : "false") {}

int db::Value::asInt() const {
    if (type != DataType::INT)
        throw std::runtime_error("Type mismatch");
    return std::stoi(data);
}

float db::Value::asFloat() const {
    if (type != DataType::FLOAT)
        throw std::runtime_error("Type mismatch");
    return std::stof(data);
}

std::string db::Value::asString() const {
    return data;
}

bool db::Value::asBool() const {
    if (type != DataType::BOOL)
        throw std::runtime_error("Type mismatch");
    return data == "true";
}