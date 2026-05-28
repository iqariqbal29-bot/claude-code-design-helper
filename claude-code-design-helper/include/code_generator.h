#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <vector>

class CodeGenerator {
public:
    struct Suggestion {
        std::string pattern;
        std::string code;
        std::string description;
    };

    CodeGenerator();
    std::vector<Suggestion> generateSuggestions(const std::string& context);
    std::string generateClassTemplate(const std::string& className);
    std::string generateSingleton(const std::string& className);
    
private:
    std::string sanitizeClassName(const std::string& name);
};

#endif