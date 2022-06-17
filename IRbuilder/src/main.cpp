#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <c1recognizer/recognizer.h>
#include <irbackend/LLVMContext.h>
#include <irbackend/Module.h>
#include <irbackend/ModuleAnalyse.h>

#include "assembly_builder.h"
// #define Codegen_Debug

using namespace YAL;
using namespace std;
using namespace c1_recognizer;
using namespace syntax_tree;
using namespace std::literals::string_literals;

// 功能测试：compiler testcase.sy -S -o testcase.s
// 性能测试：compiler testcase.sy -S -o testcase.s -O2
// Debug：  compiler testcase.sy -S -D
int main(int argc, char **argv)
{
    string target_path;
    string input_path;
    bool compile = false;
    bool assemble = false;
    bool opt = false;
    if (input_path.empty()) {
        input_path = argv[1];
    }
    if(argv[2] == "-S"s){
        assemble = true;
    }
    if(argv[3] == "-o"s){
        if (target_path.empty()) {
            target_path = argv[4];
        }
    }
    else if(argv[3] == "-D"s){
        compile = true;
    }
    if(argc > 5){
        if(argv[5] == "-O2"s){
            opt = true;
        }
    }

    if (target_path.empty()) {
        auto pos = input_path.rfind('.');
        if (pos == std::string::npos) {
            std::cerr << argv[0] << ": input file " << input_path << " has unknown filetype!" << std::endl;
            return -1;
        } 
        else {
            if (input_path.substr(pos) != ".sy") {
                std::cerr << argv[0] << ": input file " << input_path << " has unknown filetype!" << std::endl;
                return -1;
            }
            target_path = input_path.substr(0, pos);
            if(compile){
                target_path += ".ll"s;
            }
            else{
                target_path += ".s"s;
            }
        }
    }


    ifstream in_stream(input_path);
    recognizer c1r(in_stream);

    error_reporter err(cerr);
    if (!c1r.execute(err))
    {
        cerr << "Parsing failed. Exiting." << endl;
        return 2;
    }

    auto ast = c1r.get_syntax_tree();

    // std::cout<<"Finish AST Building"<<std::endl;

    string name = input_path;
    name = name.substr(name.find_last_of("/\\") + 1);

    LLVMContext YAL_ctx;
    assembly_builder builder(YAL_ctx, err);

    builder.build(name, ast);
    auto module = builder.get_module();

    std::error_code err_message;
    if (!module)
    {
        cerr << "Semantic failed. Exiting." << endl;
        return 3;
    }

    if(compile){
        module->print(target_path);
        auto command_string = std::string("llvm-link ") + target_path + ".ll ../src/io.ll -o " + target_path+".bc";
        std::system(command_string.c_str());
        command_string = std::string("llc ") + target_path + ".bc -filetype=obj";
        std::system(command_string.c_str());
        command_string = std::string("clang ") + target_path + ".o -o " +target_path;
        std::system(command_string.c_str());
        return 0;
    }
    if(assemble){
        if(opt){
            ;
        }
        auto result = semimachine::moduleTransform(module.get());
        result.print(target_path);
        result.deleteBlock();
    }
    return 0;
}
