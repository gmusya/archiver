#include <cstddef>
#include <iostream>

#include "argument_parser.h"
#include "decoder.h"
#include "encoder.h"

void Encode(const ArgumentParser& argument_parser) {
    std::ofstream out(std::string(argument_parser.FileName(0)), std::ios::binary);
    Writer writer(out);
    for (size_t i = 1; i < argument_parser.GetFilesCount(); ++i) {
        try {
            std::string file_name(std::string(argument_parser.FileName(i)));
            std::ifstream in(file_name, std::ios::binary);
            if (in.fail()) {
                throw std::ios_base::failure(std::string("Cannot open file ") + file_name);
            }
            std::cout << file_name << " encoding started" << std::endl;
            Encoder encoder(file_name);
            encoder.Encode(i + 1 == argument_parser.GetFilesCount(), writer);
            std::cout << file_name << " encoding ended" << std::endl;
        } catch (std::ios_base::failure& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Decode(const ArgumentParser& argument_parser) {
    std::ifstream in(std::string(argument_parser.FileName(0)), std::ios::binary);
    if (in.fail()) {
        throw std::ios_base::failure(std::string("Cannot open file ") + std::string(argument_parser.FileName(0)));
    }
    Reader reader(in);
    bool is_end = false;
    while (!is_end) {
        Decoder decoder;
        decoder.Decode(reader, is_end, argument_parser.FolderName());
    }
}

int main(int argc, char* argv[]) {
    ArgumentParser argument_parser(argc, argv);
    if (argument_parser.action == ArgumentParser::Action::Unknown) {
        std::cout << "To get help use command \"archiver -h\"";
        return 0;
    } else if (argument_parser.action == ArgumentParser::Action::Help) {
        PrintHelp(std::cout);
        return 0;
    } else if (argument_parser.action == ArgumentParser::Action::Encode) {
        Encode(argument_parser);
    } else {
        Decode(argument_parser);
    }
    std::cout << "Everything is fine\n";
    return 0;
}
