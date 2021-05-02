#ifndef BACKUP_CORE_H
#define BACKUP_CORE_H

#include "validator.h"
#include "fileinout.h"

class Core {
    private:
        FileInOut fio;


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
        std::string backup();
        
        /** 
        * Adds filepath to files to be backed up 
        * @param input path to a directory or a file
        * @return status message
        */
        std::string add_backup(const std::string&);

        /** 
        * Removes filepath from the backup list 
        * @param input path to a directory or a file
        * @return status message
        */
        std::string remove_backup(const std::string&);

        /** 
        * Parses user input from first time setup 
        * @param setting name of the setting
        * @param input user input
        * @return 1 if valid, otherwise 0
        */
        int parse_input(const std::string&, const std::string&);

        /**
        * Gets list of paths to be backed up inside a vector in string format
        * @return vector containing backup paths in string format
        */ 
        std::string get_backups();
        
        /**
        * Gets backup destination
        * @return backup destination
        */
        std::string get_destination();

        //int backup_loop();

    private:
        void set_settings(const std::vector<std::string>&);
};

#endif