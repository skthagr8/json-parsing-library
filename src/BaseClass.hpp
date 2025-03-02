#ifndef BASE_CLASS
#define BASE_CLASS

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class BaseClass
{
public:
    enum Type
    {
        Null,
        Number,
        Float,
        String,
        True,
        False,
        Array,
        NestedObject
    } type;
    int number;
    float fnumber;
    std::string str;
    std::vector<BaseClass> array;
    std::unordered_map<std::string, BaseClass> JsonValue;
    bool boolean;

    // Handle int
    explicit BaseClass(int number) : number(number), type(Number) {}
    // Handle float
    explicit BaseClass(float fnumber) : fnumber(fnumber), type(Float) {}
    // Handle string
    explicit BaseClass(std::string str) : str(str), type(String) {}
    // Handle boolean
    explicit BaseClass(bool boolean) : boolean(boolean), type(boolean ? True : False) {}
    // Handle array
    explicit BaseClass(std::vector<BaseClass> array) : array(array), type(Array) {}
    // Handle nested object
    explicit BaseClass(std::unordered_map<std::string, BaseClass> JsonValue) : JsonValue(JsonValue), type(NestedObject) {}
    // Handle null
    explicit BaseClass() : type(Null) {}
};

#endif