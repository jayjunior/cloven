

#ifndef CLOVEN_H
#define CLOVEN_H



class Cloven {
public:
    static int main(int count, char** args);
    static void run(const std::string& source);
    static void error(int line, const std::string& message);
    static void runPrompt();
private:
    bool hadError = false;
    static void runFile(const std::string& path);
    static void report(int line, const std::string& where, const std::string& message);
};


#endif //CLOVEN_H
