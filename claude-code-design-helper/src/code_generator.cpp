#include "code_generator.h"
#include <algorithm>
#include <cctype>

CodeGenerator::CodeGenerator() {}

std::string CodeGenerator::sanitizeClassName(const std::string& name) {
    std::string sanitized = name;
    if (!sanitized.empty()) {
        sanitized[0] = std::toupper(sanitized[0]);
    }
    for (size_t i = 1; i < sanitized.length(); i++) {
        if (sanitized[i] == '_' && i + 1 < sanitized.length()) {
            sanitized[i + 1] = std::toupper(sanitized[i + 1]);
            sanitized.erase(i, 1);
        }
    }
    return sanitized;
}

std::vector<CodeGenerator::Suggestion> CodeGenerator::generateSuggestions(const std::string& context) {
    std::vector<Suggestion> suggestions;
    
    if (context.find("singleton") != std::string::npos) {
        suggestions.push_back({"Singleton", generateSingleton("MyClass"), 
            "Use Singleton for global state management"});
    }
    
    if (context.find("factory") != std::string::npos) {
        suggestions.push_back({"Factory", 
            "class Factory {\npublic:\n    static std::unique_ptr<Product> create(Type t);\n};",
            "Use Factory Method to decouple object creation"});
    }
    
    suggestions.push_back({"ClassTemplate", generateClassTemplate("NewClass"),
        "Standard class template with RAII"});
    
    return suggestions;
}

std::string CodeGenerator::generateClassTemplate(const std::string& className) {
    std::string name = sanitizeClassName(className);
    std::string headerGuard = name + "_H";
    std::transform(headerGuard.begin(), headerGuard.end(), headerGuard.begin(), ::toupper);
    
    return "#ifndef " + headerGuard + "\n" +
           "#define " + headerGuard + "\n\n" +
           "class " + name + " {\n" +
           "public:\n" +
           "    " + name + "();\n" +
           "    ~" + name + "();\n" +
           "    " + name + "(const " + name + "&) = delete;\n" +
           "    " + name + "& operator=(const " + name + "&) = delete;\n\n" +
           "private:\n" +
           "    // TODO: Add members\n" +
           "};\n\n" +
           "#endif\n";
}

std::string CodeGenerator::generateSingleton(const std::string& className) {
    std::string name = sanitizeClassName(className);
    
    return "class " + name + " {\n" +
           "public:\n" +
           "    static " + name + "& getInstance() {\n" +
           "        static " + name + " instance;\n" +
           "        return instance;\n" +
           "    }\n\n" +
           "    " + name + "(const " + name + "&) = delete;\n" +
           "    " + name + "& operator=(const " + name + "&) = delete;\n\n" +
           "private:\n" +
           "    " + name + "() = default;\n" +
           "    ~" + name + "() = default;\n" +
           "};\n";
}