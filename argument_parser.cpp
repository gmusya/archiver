#include "argument_parser.h"

#include <iostream>
#include <string>

namespace {
    ArgumentParser::Action FindAction(int argc, char* argv[]) {
        if (argc <= 1) {
            return ArgumentParser::Action::Unknown;
        }
        std::string param1(argv[1]);
        if (param1 == "-c") {
            if (argc == 2) {
                return ArgumentParser::Action::Unknown;
            } else {
                return ArgumentParser::Action::Encode;
            }
        } else if (param1 == "-d") {
            if (argc != 4) {
                return ArgumentParser::Action::Unknown;
            } else {
                return ArgumentParser::Action::Decode;
            }
        } else if (param1 == "-h") {
            if (argc != 2) {
                return ArgumentParser::Action::Unknown;
            } else {
                return ArgumentParser::Action::Help;
            }
        }
        return ArgumentParser::Action::Unknown;
    }
}// namespace


ArgumentParser::ArgumentParser(int argc, char* argv[]) {
    action = FindAction(argc, argv);
    if (action == Action::Encode || action == Action::Decode) {
        for (int i = 2; i + 1 < argc; ++i) {
            file_names_.push_back(argv[i]);
        }
        if (action == Action::Decode) {
            folder_name_ = argv[argc - 1];
        } else {
            file_names_.push_back(argv[argc - 1]);
        }
    }
}

char* ArgumentParser::FileName(size_t index) const {
    return file_names_[index];
}

char* ArgumentParser::FolderName() const {
    return folder_name_;
}

size_t ArgumentParser::GetFilesCount() const {
    return file_names_.size();
}

void PrintHelp(std::ostream& os) {
    os << std::endl;
    os << "> To encode use command \"archiver -c archive_name file1 [file2 ...]\"" << std::endl;
    os << "> To decode use command \"archiver -d archive_name folder_name\"" << std::endl;
    os << "> To get help use command \"archiver -h\"" << std::endl;
}
