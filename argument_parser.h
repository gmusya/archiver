#pragma once

#include <string>
#include <vector>

class ArgumentParser {
public:
    enum Action {
        Decode,
        Encode,
        Help,
        Unknown
    };
    ArgumentParser(int argc, char* argv[]);
    Action action;
    char* FileName(size_t index) const;
    char* FolderName() const;
    size_t GetFilesCount() const;

private:
    std::vector<char*> file_names_;
    char* folder_name_;
};

void PrintHelp(std::ostream& os);

