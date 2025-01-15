#include "Value.h"

Value::Value(int val)
    : type(DataType::INT), data(std::to_string(val)) {}

Value::Value(float val)
    : type(DataType::FLOAT), data(std::to_string(val)) {}

Value::Value(const std::string& val)
    : type(DataType::STRING), data(val) {}

Value::Value(bool val)
    : type(DataType::BOOL), data(val ? "true" : "false") {}

int Value::asInt() const {
    if (type != DataType::INT)
        throw std::runtime_error("Type mismatch");
    return std::stoi(data);
}

float Value::asFloat() const {
    if (type != DataType::FLOAT)
        throw std::runtime_error("Type mismatch");
    return std::stof(data);
}

std::string Value::asString() const {
    return data;
}

bool Value::asBool() const {
    if (type != DataType::BOOL)
        throw std::runtime_error("Type mismatch");
    return data == "true";
}