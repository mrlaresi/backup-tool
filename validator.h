#ifndef BACKUP_VALIDATOR_H
#define BACKUP_VALIDATOR_H

#include <filesystem>
#include <vector>
#include <string>

class Validator {
    public:
        static std::filesystem::path validate(const std::vector<std::string>&);
        static std::filesystem::path validate_path(const std::string&);
    private:
        int validate_command(const std::string&);
        
};

#endif
