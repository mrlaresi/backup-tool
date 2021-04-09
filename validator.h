#ifndef BACKUP_VALIDATOR_H
#define BACKUP_VALIDATOR_H

#include <filesystem>
#include <vector>
#include <string>

class Validator {
    public:
        /**
        * Check if filepath exists
        * @param input filepath 
        * @return filepath in canonical form or a empty filepath
        */ 
        static std::filesystem::path validate_path(const std::string&);

        /** 
        * Check if filepath points to a existing file 
        * @param input filepath to a file
        * @return 1 if filepath points to a file, otherwise 0
        */
        static int validate_file(const std::filesystem::path& path);


    private:
        /**
        * Converts given filepath to canonical form
        * @param path filepath
        * @return canonical filepath or a empty filepath
        */
        static std::filesystem::path canonical(const std::filesystem::path& path);
};

#endif
