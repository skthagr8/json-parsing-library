#include <iostream>
#include <sstream>
#include <variant>
#include "JSONParseError.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

class Json {
public:
    // JSON value types (supports objects, arrays, numbers, strings, booleans, null)
    using Object = std::unordered_map<std::string, Json>;
    using Array = std::vector<Json>;
    using Value = std::variant<std::nullptr_t, bool, double, std::string, Array, Object>;

private:
    Value value;

public:
    // Constructors for different JSON types
    Json() : value(nullptr) {}                        // null
    Json(bool b) : value(b) {}                        // boolean
    Json(double num) : value(num) {}                  // number
    Json(int num) : value(static_cast<double>(num)) {} // integer
    Json(const std::string& s) : value(s) {}          // string
    Json(const char* s) : value(std::string(s)) {}    // string (C-string)
    Json(const Array& arr) : value(arr) {}            // array
    Json(const Object& obj) : value(obj) {}           // object

    // Factory methods for readability
    static Json ObjectType() { return Json(Object{}); }
    static Json ArrayType() { return Json(Array{}); }

    // Accessors (assume valid type, otherwise throws std::bad_variant_access)
    bool asBool() const { return std::get<bool>(value); }
    double asNumber() const { return std::get<double>(value); }
    const std::string& asString() const { return std::get<std::string>(value); }
    const Array& asArray() const { return std::get<Array>(value); }
    Array& asArray() { return std::get<Array>(value); }
    const Object& asObject() const { return std::get<Object>(value); }

    // Operator overloads for intuitive access
    Json& operator[](const std::string& key) {
        return std::get<Object>(value)[key]; 
    }
    
    Json& operator[](size_t index) {
        return std::get<Array>(value).at(index);
    }

    // Serialization
    /*
    std::string stringify(int indent) const {
    std::ostringstream oss;
    std::string indentStr(indent, ' ');

    std::visit([&oss, &indentStr, indent](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::nullptr_t>)
            oss << "null";
        else if constexpr (std::is_same_v<T, bool>)
            oss << (arg ? "true" : "false");
        else if constexpr (std::is_same_v<T, double>)
            oss << arg;
        else if constexpr (std::is_same_v<T, std::string>)
            oss << "\"" << arg << "\"";
        else if constexpr (std::is_same_v<T, Object>) {
            oss << "{\n";
            for (auto it = arg.begin(); it != arg.end(); ++it) {
                if (it != arg.begin()) oss << ",\n";
                oss << indentStr << "  \"" << it->first << "\": " << it->second.stringify(indent + 2);
            }
            oss << "\n" << indentStr << "}";
        } else if constexpr (std::is_same_v<T, Array>) {
            oss << "[\n";
            for (size_t i = 0; i < arg.size(); ++i) {
                if (i != 0) oss << ",\n";
                oss << indentStr << "  " << arg[i].stringify(indent + 2);
            }
            oss << "\n" << indentStr << "]";
        }
    }, value);

    return oss.str();
}

*/
    // Parsing
    static Json parse(const std::string& jsonStr){
        Json json;
        return json;
    }

    // Helpers
    bool isNull() const { return std::holds_alternative<std::nullptr_t>(value); }
    bool isBool() const { return std::holds_alternative<bool>(value); }
    bool isNumber() const { return std::holds_alternative<double>(value); }
    bool isString() const { return std::holds_alternative<std::string>(value); }
    bool isArray() const { return std::holds_alternative<Array>(value); }
    bool isObject() const { return std::holds_alternative<Object>(value); }
};



/*

*/

#include <iostream>

int main() {
    // Create JSON object
    Json obj = Json::ObjectType();
    obj["name"] = "Alice";
    obj["age"] = 25;
    obj["is_student"] = false;
    obj["scores"] = Json::ArrayType();
    obj["scores"].asArray().push_back(95);
    obj["scores"].asArray().push_back(88);
    
 
    // Parse from string
   // Json parsed = Json::parse(R"({"city": "New York", "population": 8419600})");
   // std::cout << parsed["city"].asString() << std::endl;
    
    return 0;
}
