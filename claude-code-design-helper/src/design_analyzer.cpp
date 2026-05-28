#include "design_analyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

DesignAnalyzer::DesignAnalyzer() {}

std::vector<DesignAnalyzer::DesignIssue> DesignAnalyzer::analyzeFile(const std::string& filepath) {
    std::vector<DesignIssue> issues;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        issues.push_back({"", 0, "Cannot open file: " + filepath, "high"});
        return issues;
    }

    std::string line;
    int lineNum = 0;
    
    while (std::getline(file, line)) {
        lineNum++;
        DesignIssue issue;
        
        if (checkNamingConvention(line, issue)) {
            issue.line = lineNum;
            issue.file = filepath;
            issues.push_back(issue);
        }
        
        if (checkCommentDensity(line, lineNum, issue)) {
            issue.file = filepath;
            issues.push_back(issue);
        }
        
        if (checkFunctionLength(line, lineNum, issue)) {
            issue.file = filepath;
            issues.push_back(issue);
        }
    }
    
    file.close();
    return issues;
}

bool DesignAnalyzer::checkNamingConvention(const std::string& line, DesignIssue& issue) {
    if (line.find("class ") != std::string::npos && line.find(":") == std::string::npos) {
        size_t pos = line.find("class ") + 6;
        std::string name = line.substr(pos);
        name = name.substr(0, name.find(" "));
        name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
        
        if (!name.empty() && islower(name[0])) {
            issue.description = "Class name '" + name + "' should start with uppercase";
            issue.severity = "medium";
            return true;
        }
    }
    return false;
}

bool DesignAnalyzer::checkCommentDensity(const std::string& line, int lineNum, DesignIssue& issue) {
    static int codeLines = 0;
    static int commentLines = 0;
    static bool checked = false;
    
    if (line.empty() || line.find("#include") != std::string::npos) {
        return false;
    }
    
    if (line.find("//") != std::string::npos || line.find("/*") != std::string::npos) {
        commentLines++;
    } else {
        codeLines++;
    }
    
    if (!checked && lineNum > 20 && codeLines > 0) {
        double ratio = static_cast<double>(commentLines) / codeLines;
        if (ratio < 0.1) {
            issue.description = "Low comment density (" + std::to_string(ratio * 100) + "%)";
            issue.severity = "low";
            checked = true;
            return true;
        }
    }
    
    return false;
}

bool DesignAnalyzer::checkFunctionLength(const std::string& line, int lineNum, DesignIssue& issue) {
    if (line.find("{") != std::string::npos && 
        line.find("int ") != std::string::npos || 
        line.find("void ") != std::string::npos || 
        line.find("string ") != std::string::npos) {
        // Simplified check - real implementation would track brace depth
        if (line.length() > 80) {
            issue.description = "Long function signature at line " + std::to_string(lineNum);
            issue.severity = "low";
            return true;
        }
    }
    return false;
}

bool DesignAnalyzer::runTests() {
    std::cout << "Running DesignAnalyzer tests..." << std::endl;
    
    // Test 1: Analyze non-existent file
    auto issues = analyzeFile("nonexistent.cpp");
    if (issues.empty() || issues[0].severity != "high") {
        std::cerr << "FAIL: File not found test" << std::endl;
        return false;
    }
    std::cout << "PASS: File not found test" << std::endl;
    
    // Test 2: Check naming convention
    std::string testLine = "class myClass {";
    DesignIssue issue;
    if (!checkNamingConvention(testLine, issue)) {
        std::cerr << "FAIL: Naming convention check" << std::endl;
        return false;
    }
    std::cout << "PASS: Naming convention check" << std::endl;
    
    return true;
}