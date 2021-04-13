#ifndef BACKUP_CORE_H
#define BACKUP_CORE_H

#include "validator.h"
#include "fileinout.h"

class Core {
    private:
        FileInOut fio;
        std::vector<std::string> user_settings = {
            "destination",
            "interval",
            "storedCount"
        };
    public:
        /** Default constructor */
        Core();
        /** Loads the program settings from .ini file */
        int load_settings();
        /** Checks if it's the first time starting the program */
        int is_first();
        /** Performs first time setup operation */
        int first_time();
        /** Performs backup operation */
        int backup();
        /** Adds filepath to files to be backed up */
        int add_backup(const std::vector<std::string>&);
        /** Removes filepath from the backup list */
        int remove_backup(const std::vector<std::string>&);

        /** 
        * Parses user input from first time setup 
        * @param setting name of the setting
        * @param input user input
        * @return 1 if valid, otherwise 0
        */
        int parse_input(const std::string&, const std::string&);
    private:
};

#endif