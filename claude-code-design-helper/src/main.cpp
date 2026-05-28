#include <iostream>
#include <string>
#include <vector>
#include "design_analyzer.h"
#include "code_generator.h"

void printUsage() {
    std::cout << "Claude Code Design Helper v1.0.0\n"
              << "Usage:\n"
              << "  claude-code-design-helper --analyze <file>\n"
              << "  claude-code-design-helper --generate <context>\n"
              << "  claude-code-design-helper --test\n"
              << "  claude-code-design-helper --help\n";
}

int runAnalyzer(const std::string& filepath) {
    DesignAnalyzer analyzer;
    auto issues = analyzer.analyzeFile(filepath);
    
    if (issues.empty()) {
        std::cout << "No design issues found in " << filepath << std::endl;
        return 0;
    }
    
    std::cout << "Found " << issues.size() << " design issue(s):\n";
    for (const auto& issue : issues) {
        std::cout << "[" << issue.severity << "] " << issue.file 
                  << ":" << issue.line << " - " << issue.description << "\n";
    }
    return issues.size();
}

int runGenerator(const std::string& context) {
    CodeGenerator generator;
    auto suggestions = generator.generateSuggestions(context);
    
    if (suggestions.empty()) {
        std::cout << "No suggestions for context: " << context << std::endl;
        return 0;
    }
    
    std::cout << "Generated " << suggestions.size() << " suggestion(s):\n";
    for (const auto& suggestion : suggestions) {
        std::cout << "\n--- " << suggestion.pattern << " ---\n"
                  << suggestion.description << "\n\n"
                  << suggestion.code << "\n";
    }
    return suggestions.size();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    
    std::string command = argv[1];
    
    if (command == "--help") {
        printUsage();
        return 0;
    }
    
    if (command == "--test") {
        DesignAnalyzer analyzer;
        bool passed = analyzer.runTests();
        return passed ? 0 : 1;
    }
    
    if (command == "--analyze" && argc >= 3) {
        return runAnalyzer(argv[2]);
    }
    
    if (command == "--generate" && argc >= 3) {
        return runGenerator(argv[2]);
    }
    
    std::cerr << "Unknown command: " << command << std::endl;
    printUsage();
    return 1;
}