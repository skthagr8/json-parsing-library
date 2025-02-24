#include "baseclass.hpp"
#include "BaseClassRepository.hpp"
#include "JSONParseError.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using JsonClass = BaseClass;
using Map = std::unordered_map<std::string,JsonClass>;

class Json{
    public:
   
    std::string trimString(const std::string& json){
        size_t start = json.find_first_not_of(" \t\n\r");
        size_t end = json.find_last_not_of(" \t\n\r");

        // Check if string is empty
        if (start == std::string::npos) {
            throw JSONEmptyString("Empty string");
        }
        return json.substr(start, end-start+1);;
    }
    
    std::string remove_brackets(const std::string& json) {
        size_t starting_index = json.find("{");
        size_t ending_index = json.rfind("}");  // Use rfind() to find the last '}'
    
        if (starting_index == std::string::npos || ending_index == std::string::npos || starting_index > ending_index) {
            throw JSONInvalidStringFormat("Brackets missing or malformed JSON");
        }
    
        return json.substr(starting_index + 1, ending_index - starting_index - 1);
    }



    std::unordered_map< std::string,std::string> parse_object(std::string& json){
        std::unordered_map<std::string, std::string> object;
    
        // Declare the starting index as 0
        int starting_index = 0;
        
        // Remove its brackets
        std::string new_json = remove_brackets(json);
    
       
    
    //    int limit  = 10;
    
        while(starting_index < new_json.size() )
        {   
            // Find the first quote
            size_t quote = new_json.find("\"", starting_index);
            if(quote == std::string::npos){
                break;
            }
        //    std::cout<< "Opening quote found at index: " << quote << std::endl;
    
            // Find the closing quote
            size_t end_quote = new_json.find("\"", quote + 1);
          //  std::cout << "Closing quote found at index: " << end_quote << std::endl;
    
            if (end_quote == std::string::npos)
            {
                std::cout << "No closing quote found" << std::endl;
                break;
            }
            
            // Extract the key
            std::string key = trimString(new_json.substr(quote + 1, end_quote - quote - 1));  
            std::cout << "Key: " << key << std::endl;
            
            // Find the colon after the closing quote
            starting_index = new_json.find(":", end_quote + 1);
            if (starting_index == std::string::npos)
            {
                std::cout << "No colon found" << std::endl;
                break;
            }
        //    std::cout << "Colon found at index: " << starting_index << std::endl;
            starting_index++;
    
            // Find the opening quote after the colon
            size_t next_opening_quote = new_json.find("\"", starting_index + 1);
            if (next_opening_quote == std::string::npos)
            {
                std::cout << "No opening quote found" << std::endl;
                break;
            }
        //    std::cout << "Next opening quote found at index: " << next_opening_quote << std::endl;
            
            // Find the closing quote after the opening quote
            size_t next_closing_quote = new_json.find("\"", next_opening_quote + 1);
            if (next_closing_quote == std::string::npos)
            {
                std::cout << "No closing quote found" << std::endl;
                break;
            }
            
            // Extract the value   
            std::string value = trimString(new_json.substr(next_opening_quote + 1, next_closing_quote - next_opening_quote - 1));
            std::cout << "Value: " << value << std::endl;
    
            // Add the key-value pair to the object
            object[key] = value;
            
            // Set the element after the closing quote as the new starting index
            size_t comma = new_json.find(",", next_closing_quote + 1);
            if(comma == std::string::npos){
                break;
            }
            starting_index = comma + 1;
        }
        return object;
    }
    
};    
    
int main(){
    
    std::string str2 = " {\"name\": \"John\", \"age\": \"30\", \"car\": \"null\" } ";
    
    Json jsonParser;
    std::unordered_map<std::string, std::string> map = jsonParser.parse_object(str2);   
        
    std::cout << std::endl;
    for(std::unordered_map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++){
        std::cout << it->first << " : " << it->second << std::endl;
    }
      
  
     return 0;
    }