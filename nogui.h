#ifndef BACKUP_NOGUI_H
#define BACKUP_NOGUI_H

#include "core.h"
#include <vector>

class NoGui {
    private:
        Core core;

    public:
        /** 
        * Default constructor 
        * */
        NoGui();

        /** 
        * Backups modified files 
        */
        void backup();

        /** 
        * Adds filepath to be backed up 
        * @param input filepath to a directory or a file
        */
        void add_backup(const std::vector<std::string>&);

        /** 
        * Removes filepath from the list of files that will be backed up
        * @param input filepath to a directory or a file
        */
        void remove_backup(const std::vector<std::string>&);

        /** 
        * Prints list of backup paths 
        */
        void get_backups();
        
        /** 
        * Prints backup destination 
        */
        void get_destination();

        /** 
         * Handle user input from cin
         * @return vector containing user input split from whitespaces
        */
        std::vector<std::string> get_input();

        /**
        * Prints list of known commands
        */
        void help();

        /**
        * Main loop for terminal program
        */
        int nogui_loop();

    private:
        void first_time();
};

#endif
