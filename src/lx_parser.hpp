#include <iostream>
#include <fstream>
#include <string>

class lx_parser {
public:
    class _PARSE_ {
    public:
        std::string lx_project_name = "Html Compiles - LX NATIVE BINARIES";
        std::string lx_project_out;
        std::string lx_project_port = "6738";
        std::string lx_project_fs;
        std::string lx_project_include;
        std::string lx_project_pckg = "com.htmlcompiles.lxnative";

        void lx_project_info(const std::string& lx_project_path) {
            std::string project_meta_file_path = lx_project_path + "/project.lxnative";
            std::ifstream lx_project_meta(project_meta_file_path);
            
            if (lx_project_meta.is_open()) {
                std::cout << "LX PARSER SUCCESS STATUS 1 --> A valid project was found\n"
                          << "LX PARSER SUCCESS STATUS --> Parsing project to tokenizer.\n"
                          << " on path '" << project_meta_file_path << "'\n";
                
                std::string temp_project_data;
                while (std::getline(lx_project_meta, temp_project_data)) {
                    if (temp_project_data.find("#") != std::string::npos) {
                        // Ignore comments
                        continue;
                    }
                    else if (temp_project_data.empty()) {
                        // Ignore empty lines
                        continue;
                    }
                    else if (temp_project_data.find("NAME=") != std::string::npos) {
                        std::string keyword = "NAME=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_name = extract;
                        // std::cout << "Project Name: " << lx_project_name << "\n";
                    }
                    else if (temp_project_data.find("EXEC_PCKG=") != std::string::npos) {
                        std::string keyword = "EXEC_PCKG=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_pckg = extract;
                    }
                    else if (temp_project_data.find("PORT=") != std::string::npos) {
                        std::string keyword = "PORT=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_port = extract;
                    }
                    else if (temp_project_data.find("EXEC_PATH=") != std::string::npos) {
                        std::string keyword = "EXEC_PATH=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_out = extract;
                    }
                    else if (temp_project_data.find("EXEC_FS=") != std::string::npos) {
                        std::string keyword = "EXEC_FS=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_fs = extract;
                    }
                    else if (temp_project_data.find("EXEC_INCLUDE=") != std::string::npos) {
                        std::string keyword = "EXEC_INCLUDE=";
                        std::string extract = temp_project_data.substr(temp_project_data.find(keyword) + keyword.length());
                        lx_project_include = extract;
                    }
                    else {
                        std::cout << "LX PARSER ERROR --> In project " << lx_project_name
                                  << " in file project.lxnative on path '" << project_meta_file_path
                                  << "' error found in line '" << temp_project_data
                                  << "' for no such line was expected to compile an executable.\n";
                        break;
                    }
                }

                std::cout << "LX PARSER SUCCESSFUL STATUS 2 --> Successfully parsed the project to main! "
                          << "The rest of the compilation will be handled by the lx main.\n";
            } else {
                std::cout << "LX PARSER ERROR --> This was not an lx native project. "
                          << "Only lx native projects can be compiled into executables; others cannot. "
                          << "Please specify a valid lx native project path.\n";
            }
        }
    };

    _PARSE_ parse;
};
