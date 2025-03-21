//
// Created by Jay Junior  on 20.03.25.
//

#include "GenerateAst.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace tool {
    class GenerateAst {

    public:
        static void defineAst(const std::string &outputDir, const std::string &baseName, const std::vector<std::string> &types) {
            std::string path = outputDir + "/" + baseName + ".h";
            std::ofstream file(path);
            file << "#ifndef " << baseName << "_H\n";
            file << "#define " << baseName << "_H\n";
            file << "\n";
            file << "#include <string>\n";
            file << "#include <vector>\n";
            file << "#include \"Token.h\"\n";
            file << "#include \"Visitor.h\"\n";
            file << "using string = std::string;\n";
            file << "\n";
            file << "namespace cloven {\n";
            file << "    class " << baseName << " {\n";
            file << "    public:\n";
            file << "        " << baseName << "() = default;\n";
            file << std::endl;
            for (const std::string &type : types) {
                std::vector<std::string> parts = split(type, ':');
                const std::string& className = parts[0];
                const std::string& fields = parts[1];
                defineType(file, baseName, className, fields);
            }
            file << "    };\n";
            file << "}\n";
            file << "\n";
            file << "#endif //" << baseName << "_H\n";

        }

    private:

        static std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::stringstream ss(str);
            std::string token;
            while (std::getline(ss, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        static void defineType(std::ofstream &file, const std::string &baseName, const std::string &className, const std::string &fieldList) {

            file << "        class " << className << " {" << std::endl;
            file << "        public:" << std::endl;
            std::vector<std::string> fields = split(fieldList, ',');
            for (const std::string &field : fields) {
                std::vector<std::string> parts = split(field, ' ');
                const std::string& type = parts[0];
                const std::string& name = parts[1];
                file << "            " << type << " " << name <<  ";" << std::endl;
            }
            file << "            " << className << "(" << fieldList << ") :" << std::endl;
            for (size_t i = 0; i < fields.size(); i++) {
                std::vector<std::string> parts = split(fields[i], ' ');
                const std::string& name = parts[1];
                file << "                " << name << "(" << name << ")";
                if (i < fields.size() - 1) {
                    file << ",";
                }
                file << std::endl;
            }
            file << "            {}" << std::endl;
            file << "            " << "void accept(Visitor& visitor) {" << std::endl;
            file << "                visitor.visit" << className << "(*this);" << std::endl;
            file << "            }" << std::endl;
            file << "        };" << std::endl;
            file << std::endl;

        }

        static void defineVisitor(std::ofstream &file ,const std::string& baseName , std::vector<std::string> &types) {
            file << "        class Visitor {" << std::endl;
        }
    };
}

int main(const int count , char ** args) {
    if (count != 2) {
        std::cerr << "Usage: generate_ast <output directory>" << std::endl;
        exit(1);
    }
    const std::string outputDir = args[1];
    tool::GenerateAst::defineAst(outputDir, "Expr", {
        "Binary:Expr& left,Token& op,Expr& right",
        "Grouping:Expr& expression",
        "Literal:string& value",
        "Unary:Token& op,Expr& right"
    });
}


