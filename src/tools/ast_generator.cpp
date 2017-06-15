#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace so_utils {
    // source:
    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    static std::vector<std::string> split(const std::string& str,
                                          const std::string& delim) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos)
                pos    = str.length();
            auto token = str.substr(prev, pos - prev);
            if (!token.empty())
                tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }
}

class ASTGenerator {
  public:
    using ASTSpecification = std::pair<std::string, std::vector<std::string>>;
    ASTGenerator(const std::string& aDir, const ASTSpecification aSpec)
        : outDir(aDir)
        , astSpec(aSpec) {}
    void generate() {
        std::cout << outDir << std::endl;
        defineAST();
    }
    void defineAST() {
        auto baseName = astSpec.first;
        auto path     = outDir + "/" + baseName + ".hpp";
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cout << "Unable to open file." << std::endl;
            return;
        }

        // Expr base abstract interface
        file << "#include \"scanner/token.hpp\"" << std::endl;
        file << "using namespace lox;" << std::endl;
        file << "class " << baseName << "; // forward declare" << std::endl;

        defineVisitor(file, baseName);

        file << "class " << baseName << " {" << std::endl;
        file << "public:" << std::endl;
        file << "virtual ~" << baseName << "() = 0;" << std::endl;
        file << "virtual void accept(" << baseName + "Visitor* visitor) = 0;"
             << std::endl;
        file << "};" << std::endl;
        file << baseName << "::~" << baseName << "() {}" << std::endl;

        // Derived concrete classes
        for (auto type : astSpec.second) {
            auto className = type.substr(0, type.find(":"));
            auto fields    = type.substr(type.find(":") + 1, type.size());
            defineType(file, baseName, className, fields);
        }

        file.close();
    }
    void defineType(std::ofstream& file, const std::string& baseName,
                    const std::string& className, const std::string fields) {
        file << "class " + className + " : public " + baseName + " { "
             << std::endl;
        file << "public: " << std::endl;
        file << className + "(";
        auto fieldList = so_utils::split(fields, ",");
        bool first     = true;
        for (auto field : fieldList) {
            if (!first)
                file << ", ";
            if (first)
                first      = false;
            auto fieldType = so_utils::split(field, " ")[0];
            auto fieldName = so_utils::split(field, " ")[1];
            if (!fieldType.compare(baseName)) {
                file << fieldType + "* " + fieldName;
            } else {
                file << fieldType + " " + fieldName;
            }
        }
        file << ")  : ";
        first = true;
        for (auto field : fieldList) {
            if (!first)
                file << ", ";
            if (first)
                first      = false;
            auto fieldName = so_utils::split(field, " ")[1];
            file << fieldName + "(" + fieldName + ")";
        }
        file << " {}" << std::endl;
        file << "void accept(" << baseName + "Visitor* visitor) override {"
             << std::endl;
        file << "visitor->visit" << className << "(this);" << std::endl;
        file << "}" << std::endl;
        file << "private: " << std::endl;
        for (auto field : fieldList) {
            auto fieldType = so_utils::split(field, " ")[0];
            auto fieldName = so_utils::split(field, " ")[1];
            if (!fieldType.compare(baseName)) {
                file << fieldType + "* " + fieldName + ";" << std::endl;
            } else {
                file << fieldType + " " + fieldName + ";" << std::endl;
            }
        }
        file << "};" << std::endl;
    }
    void defineVisitor(std::ofstream& file, const std::string& baseName) {
        auto visitorClassName = baseName + "Visitor";
        file << "class " << visitorClassName << " {" << std::endl;
        file << "public:" << std::endl;
        file << "virtual ~" << visitorClassName << "() = 0;" << std::endl;
        for (auto type : astSpec.second) {
            auto className = type.substr(0, type.find(":"));
            file << "virtual void "
                 << "visit" + className << "(" << baseName << "* " << baseName
                 << ") = 0;" << std::endl;
        }
        file << "};" << std::endl;
        file << visitorClassName << "::~" << visitorClassName << "() {}"
             << std::endl;
    }

  private:
    const std::string outDir;
    const ASTSpecification astSpec;
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ast_generator <output directory>" << std::endl;
    } else {
        const std::string outDir                     = argv[1];
        const ASTGenerator::ASTSpecification astSpec = {
            "Expr",
            {"BinaryExpr   :Expr left,Token Operator,Expr right",
             "GroupingExpr :Expr expression", "Literal  :std::string value",
             "UnaryExpr    :Token Operator,Expr right"}};
        ASTGenerator astGenerator(outDir, astSpec);
        astGenerator.generate();
    }
    return 0;
}
