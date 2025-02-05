

#ifndef CLOVEN_H
#define CLOVEN_H


#include <string>
#include <vector>
#include "Scanner.h"
#include "Token.h"

class Cloven {
public:
    static int main(int count, char** args);
    static void run(const std::string& source);
    static void error(int line, const std::string& message);
private:
    bool hadError = false;
    static void runFile(const std::string& path);
    static void runPrompt();
    static void report(int line, const std::string& where, const std::string& message);
};


#endif //CLOVEN_H
