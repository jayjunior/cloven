#include <fstream>
#include <iostream>
#include <string>
#include "Scanner.h"
#include "Token.h"
#include "Cloven.h"

using string = std::string;

namespace cloven {
    class Cloven {
    public:
        static int main(int count , char ** args) {
            if (count > 1) {
                std::cout << "Usage: cloven [script]" << std::endl;
            }else if (count == 1) {
                runFile(args[1]);
            }else {
                runPrompt();
            }
            return 0;
        }
        static void run(const string& source) {
            auto scanner = Scanner(source);
            for (const std::vector<Token> tokens = scanner.scanTokens(); const Token& token : tokens) {
                std::cout << token << std::endl;
            }
        }
        static void error(const int line , const string &message) {
            report(line,"   ",message);
        }
    private:
        bool hadError = false;

        static void runFile(const std::string& path) {
            std::ifstream file(path);
            std::string line;
            while (std::getline(file, line)) {
                run(line);
            }
        }

        static void runPrompt() {
            for(;;) {
                std::cout << "> ";
                std::string line;
                std::getline(std::cin, line);
                if (line.empty()) break;
                run(line);
            }
        }



        static void report(const int line , const string& where , const string& message) {
            std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
        }
    };
}

