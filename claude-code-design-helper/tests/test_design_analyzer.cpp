#include <iostream>
#include <cassert>
#include "../include/design_analyzer.h"
#include "../include/code_generator.h"

bool testAnalyzerBasic() {
    DesignAnalyzer analyzer;
    
    // Test with a simple file
    auto issues = analyzer.analyzeFile("nonexistent_file.cpp");
    if (issues.empty()) {
        std::cerr << "FAIL: Expected at least one issue for missing file" << std::endl;
        return false;
    }
    
    std::cout << "PASS: analyzer basic test" << std::endl;
    return true;
}

bool testGeneratorBasic() {
    CodeGenerator generator;
    
    auto suggestions = generator.generateSuggestions("singleton pattern");
    if (suggestions.empty()) {
        std::cerr << "FAIL: Expected suggestions for singleton context" << std::endl;
        return false;
    }
    
    bool foundSingleton = false;
    for (const auto& s : suggestions) {
        if (s.pattern == "Singleton") {
            foundSingleton = true;
            break;
        }
    }
    
    if (!foundSingleton) {
        std::cerr << "FAIL: Expected Singleton suggestion" << std::endl;
        return false;
    }
    
    std::cout << "PASS: generator basic test" << std::endl;
    return true;
}

bool testGeneratorClassTemplate() {
    CodeGenerator generator;
    std::string template_code = generator.generateClassTemplate("my_class");
    
    if (template_code.find("MyClass") == std::string::npos) {
        std::cerr << "FAIL: Class template should sanitize name" << std::endl;
        return false;
    }
    
    std::cout << "PASS: class template generation test" << std::endl;
    return true;
}

int main() {
    std::cout << "Running Claude Code Design Helper tests..." << std::endl;
    
    bool allPassed = true;
    allPassed &= testAnalyzerBasic();
    allPassed &= testGeneratorBasic();
    allPassed &= testGeneratorClassTemplate();
    
    if (allPassed) {
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    } else {
        std::cerr << "\nSome tests failed!" << std::endl;
        return 1;
    }
}