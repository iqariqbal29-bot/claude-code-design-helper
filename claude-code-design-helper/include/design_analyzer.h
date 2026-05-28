#ifndef DESIGN_ANALYZER_H
#define DESIGN_ANALYZER_H

#include <string>
#include <vector>

class DesignAnalyzer {
public:
    struct DesignIssue {
        std::string file;
        int line;
        std::string description;
        std::string severity; // "low", "medium", "high"
    };

    DesignAnalyzer();
    std::vector<DesignIssue> analyzeFile(const std::string& filepath);
    bool runTests();
    
private:
    bool checkNamingConvention(const std::string& line, DesignIssue& issue);
    bool checkCommentDensity(const std::string& line, int lineNum, DesignIssue& issue);
    bool checkFunctionLength(const std::string& line, int lineNum, DesignIssue& issue);
};

#endif