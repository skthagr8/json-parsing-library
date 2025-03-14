#include <iostream>
#include <string>
#include <stack>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <any>

using Map = std::unordered_map<std::string, std::any>;

static std::string trimString(const std::string& json){
    size_t start = json.find_first_not_of(" \t\n\r");
    size_t end = json.find_last_not_of(" \t\n\r");

    // Check if string is empty
    if (start == std::string::npos) {
        std::cout << "String is empty" << std::endl;
    }
    return json.substr(start, end-start+1);;
}

static std::string parseNull(int starting_index, const std::string&json){
    if(json.substr(starting_index, 4) == "null"){
        return "null";
    }
    return "";
}

static std::string parseBool(int& starting_index, const std::string& json) {
    if (json.compare(starting_index, 4, "true") == 0) {
        starting_index += 4;  // Move past "true"
        return "true";
    } else if (json.compare(starting_index, 5, "false") == 0) {
        starting_index += 5;  // Move past "false"
        return "false";
    } else {
        throw std::runtime_error("Invalid boolean value at index " + std::to_string(starting_index));
    }
}

static double parseNumber(int starting_index, const std::string& json)
{
    size_t end = starting_index;
    
    // Allow negative numbers
    if (json[end] == '-') {
        end++;
    }

    // Consume digits (before decimal)
    while (end < json.size() && std::isdigit(json[end])) {
        end++;
    }

    // Check for decimal point
    if (end < json.size() && json[end] == '.') {
        end++;
        while (end < json.size() && std::isdigit(json[end])) {
            end++;
        }
    }

    // Check for exponent notation
    if (end < json.size() && (json[end] == 'e' || json[end] == 'E')) {
        end++;
        // Allow optional `+` or `-` sign
        if (end < json.size() && (json[end] == '+' || json[end] == '-')) {
            end++;
        }
        while (end < json.size() && std::isdigit(json[end])) {
            end++;
        }
    }

    return std::stod(json.substr(starting_index, end - starting_index));
}

static std::string parseString(int starting_index, const std::string& js){
    size_t closing_quote = js.find("\"", starting_index + 1);
    if(closing_quote == std::string::npos){
        std::cout << "No closing quote found" << std::endl;
    }
    return js.substr(starting_index + 1, closing_quote - starting_index - 1);

}

std::string remove_brackets(const std::string& json) {
    // First position of the first bracket
    size_t starting_index = json.find("{");

    // Last position of the last bracket
    size_t ending_index = json.rfind("}");  // Use rfind() to find the last '}'

    if (starting_index == std::string::npos || ending_index == std::string::npos || starting_index > ending_index) {
        std::cout << "No brackets found" << std::endl;
    }

    return json.substr(starting_index + 1, ending_index - starting_index - 1);
}

static std::vector<std::any> parseArray(const std::string& json, int& starting_index){
    std::vector<std::any> array_variables;
    std::stack<char> s;
    std::string string_buffer;

    // Push the first element to the stack
    s.push('[');

    // Move past the opening bracket
    starting_index++;

    // Initialize loop till the end of the JSON string
    while(starting_index < json.size()){
        char character = json[starting_index];

        // Handle Arrays or Objects
        if(character == '[' || character == '{'){
            s.push(character);

           if(character == '{'){
               int starting_obj = starting_index;
               int obj_index = starting_index;
               std::string obj = json.substr(starting_obj, json.size() - starting_obj);
               array_variables.push_back(obj);
               starting_index = obj_index;
               continue;

           }
        } else if(character == ']' || character =='}'){
            s.pop();
            if(s.empty()){
                if(!string_buffer.empty()){
                    array_variables.push_back(string_buffer);
                    string_buffer.clear();
                }
                return array_variables;
            }
        } else if( character == ',' && s.size() == 1){
            array_variables.push_back(trimString(string_buffer));
            string_buffer.clear();
        } else {
            string_buffer += character;
        }
        starting_index++;
    }
    return array_variables;

}

Map detector(const std::string& json, int& starting_index){
    Map map;
    std::vector<std::any> array_variables;

    // Set the starting index to 0
    starting_index = 0;

    // Remove the brackets
    std::string new_json = remove_brackets(json);
    
    // Loop through the json string
    while(starting_index < new_json.size()){

        // Find opening quote of the key
        size_t quote = new_json.find("\"", starting_index);
        if(quote == std::string::npos){
            std::cout << "No opening quote found" << std::endl;
            break;
        }
        
        // Find closing quote of the key
        size_t next_quote = new_json.find("\"", quote + 1);
        if(next_quote == std::string::npos){
            std::cout << "No closing quote found" << std::endl;
            break;
        }

        // Extract Key
        std::string key = trimString(new_json.substr(quote + 1, next_quote - quote - 1));
        std::cout << "Key: " << key << std::endl;

        // Find the Colon
        starting_index = new_json.find(":", next_quote + 1);
        if(starting_index == std::string::npos){
            std::cout << "No colon found" << std::endl;
            break;
        }

        // Move past the colon
        starting_index++;

        // Detect array or object
        if(new_json[starting_index] == '['){
            array_variables = parseArray(new_json, starting_index);
            map[key] = array_variables;           
        }
        
        // If starting character after the colon is an object
        else if(new_json[starting_index] == '{'){
            std::stack<char> s;
            s.push('{');
            int obj_index = starting_index;
            starting_index++;
            while(!s.empty() && starting_index < new_json.size()){
                if(new_json[starting_index] == '{'){
                    s.push(new_json[starting_index]);
                } else if(new_json[starting_index] == '}'){
                    s.pop();
                }
                starting_index++;
            }
            std::string nested_json = new_json.substr(obj_index, starting_index - obj_index);
            map[key] = detector(nested_json, obj_index);
        } 
        // If starting character after the colon is 'null'
        else if(new_json[starting_index] == 'n'){
            std::string value = trimString(parseNull(starting_index, new_json));
            map[key] = value;
            std::cout << "Value: " << value << std::endl;  
        }
        // If starting character after the colon is 'true'
        else if(new_json[starting_index] == 't' || new_json[starting_index] == 'f'){
            std::string value = trimString(parseBool(starting_index, new_json));
            map[key] = value;
            std::cout << "Value: " << value << std::endl;       
        }
        // If starting character after the colon is a string
        else if(new_json[starting_index] == '"'){
            std::string value  = trimString(parseString(starting_index, new_json));
            map[key] = value;
            std::cout << "Value: " << value << std::endl;   
        }
        // If starting character after the colon is a number
        else if(isdigit(new_json[starting_index])){
            double value = parseNumber(starting_index, new_json);
            std::cout << "Value: " << value << std::endl;
            map[key] = value;
        }

        // Find the next comma
        size_t comma = new_json.find(",", starting_index);
        if(comma == std::string::npos){
            break;
        }
        starting_index = comma + 1;
        }    
    return map;
    }
     

    void printAny(const std::any& value) {
        if (value.type() == typeid(std::string)) {
            std::cout << std::any_cast<std::string>(value);
        } else if (value.type() == typeid(int)) {
            std::cout << std::any_cast<int>(value);
        } else if (value.type() == typeid(double)) {
            std::cout << std::any_cast<double>(value);
        } else if (value.type() == typeid(bool)) {
            std::cout << (std::any_cast<bool>(value) ? "true" : "false");
        } else if (value.type() == typeid(std::vector<std::any>)) {
            std::cout << "[ ";
            for (const auto& item : std::any_cast<std::vector<std::any>>(value)) {
                printAny(item);
                std::cout << " ";
            }
            std::cout << "]";
        } else if (value.type() == typeid(std::unordered_map<std::string, std::any>)) {
            std::cout << "{ ";
            for (const auto& [k, v] : std::any_cast<std::unordered_map<std::string, std::any>>(value)) {
                std::cout << k << ": ";
                printAny(v);
                std::cout << " ";
            }
            std::cout << "}";
        } else {
            std::cout << "Unsupported type";
        }
    }

int main(){
    std::string str2 = "{\"stringKey\":\"stringValue\",\"nullKey\":null,\"trueKey\":true,\"falseKey\":false,\"intKey\":42,\"arrayKey\":[1,2,3,\"four\",null,true,false],\"nestedObjectKey\":{\"nestedStringKey\":\"nestedStringValue\",\"nestedIntKey\":100,\"nestedArrayKey\":[10,20,30]},\"nestedArrayKey\":[[1,2,3],[\"a\",\"b\",\"c\"],[true,false,null]]}";

    int starting_index = 0;
    Map object = detector(str2, starting_index);

    std::cout << "\nObject:\n";
    for (const auto& [key, value] : object) {
        std::cout << key << " : ";
        printAny(value);
        std::cout << std::endl;
    }

    return 0;

return 0;
}