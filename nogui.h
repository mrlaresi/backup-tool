#ifndef NOGUI_H
#define NOGUI_H

#include "fileinout.h"

class NoGui {
    private:
        FileInOut fio;


    public:
        /** Default constructor */
        NoGui();

        /** Backups modified files */
        void backup();

        void add_backup(const std::vector<std::string>&);

        /** 
         * Handle user input from cin
         * @return vector containing user input split from whitespaces
        */
        std::vector<std::string> get_input();

        void help();
};

#endif
