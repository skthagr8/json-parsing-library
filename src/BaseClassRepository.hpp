#ifndef BASE_CLASS_REPOSITORY
#define BASE_CLASS_REPOSITORY

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "BaseClass.hpp"

class BaseClassRepository
{
public:
    virtual int parse_number(std::string json, int index) = 0;
    virtual float parse_float(std::string json, int index) = 0;
    virtual std::string parse_string(std::string json, int index) = 0;
    virtual bool parse_boolean(std::string json, int index) = 0;
    virtual std::vector<BaseClass> parse_array(std::string json, int index) = 0;
    virtual BaseClass parse_null(std::string json, int index) = 0;
    virtual std::unordered_map<std::string, BaseClass> parse_nested_object(std::string json, int index) = 0;
    virtual BaseClass parse_object(std::string json) = 0;
};

#endif