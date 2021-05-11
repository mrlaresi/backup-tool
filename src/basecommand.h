#ifndef BACKUP_BASECOMMAND
#define BACKUP_BASECOMMAND

#include "core.h"

#include <string>

/**
* Abstract class used to build commands from.
*/
class BaseCommand {
    protected:
        Core *core;
    public:
        virtual ~BaseCommand();

        /**
        * Execute command
        */ 
        virtual std::string execute(const std::string& = "") = 0;

        /**
        * Set core pointer
        * @param core pointer to core
        */
        void set_core(Core*);
};

#endif