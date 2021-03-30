#ifndef BACKUP_NOGUI_H
#define BACKUP_NOGUI_H

#include "core.h"
#include <vector>

class NoGui {
    private:
        Core core;

    public:
        /** Default constructor */
        NoGui();

        /** Backups modified files */
        void backup();

        void add_backup(const std::vector<std::string>&);

        void remove_backup(const std::vector<std::string>&);

        /** 
         * Handle user input from cin
         * @return vector containing user input split from whitespaces
        */
        std::vector<std::string> get_input();

        void help();

        int nogui_loop();
};

#endif
