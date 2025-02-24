#ifndef JSON_PARSE_ERROR_CLASS
#define JSON_PARSE_ERROR_CLASS  

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

//

class JSONEmptyString : public std::runtime_error {
    public:
    JSONEmptyString(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};
class JSONUnexpectedEOF : public std::runtime_error {
    public:
    JSONUnexpectedEOF(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONMismatchedBrackets : public std::runtime_error {
    public:
    JSONMismatchedBrackets(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONMissingOpenBracket : public std::runtime_error {
    public:
    JSONMissingOpenBracket(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONUnquotedKey : public std::runtime_error {
    public:
    JSONUnquotedKey(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONInvalidNumberFormat : public std::runtime_error {
    public:
    JSONInvalidNumberFormat(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONTrailingComma : public std::runtime_error {
    public:
    JSONTrailingComma(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONInvalidLiteral : public std::runtime_error {
    public:
    JSONInvalidLiteral(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONInvalidStringFormat : public std::runtime_error {
    public:
    JSONInvalidStringFormat(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONDuplicateKey : public std::runtime_error {
    public:
    JSONDuplicateKey(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

class JSONInvalidEscapeSequence : public std::runtime_error {
    public:
    JSONInvalidEscapeSequence(const std::string& msg) : std::runtime_error("JSON Parser Error"+ msg) {}
};

#endif