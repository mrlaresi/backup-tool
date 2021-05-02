#ifndef BACKUP_NOGUI_H
#define BACKUP_NOGUI_H

#include "baseui.h"
#include "core.h"
#include "invoker.h"

#include <vector>

class NoGui : public BaseUI {
    private:
        Invoker *invoker;

    public:
        /** 
        * Default constructor 
        * */
        NoGui(Invoker*);
        ~NoGui();

        /** 
        * Backups modified files 
        */
        void backup() override;

        /** 
        * Adds filepath to be backed up 
        * @param input filepath to a directory or a file
        */
        void add_backup(const std::string&) override;

        /** 
        * Removes filepath from the list of files that will be backed up
        * @param input filepath to a directory or a file
        */
        void remove_backup(const std::string&) override;

        /** 
        * Prints list of backup paths 
        */
        void get_backups() override;
        
        /** 
        * Prints backup destination 
        */
        void get_destination() override;

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
        * Prints stuff to standard output
        * @param input text that will be printed to standard output
        */
        void print(const std::string&);

        /**
        * Main loop for terminal program
        */
        int nogui_loop();


        //int backup_loop();

    private:
        void first_time();
};

#endif
