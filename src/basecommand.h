#ifndef BACKUP_BASECOMMAND
#define BACKUP_BASECOMMAND

#include "core.h"

#include <string>

class BaseCommand {
    protected:
        std::string result;
        Core *core;
    public:
        virtual ~BaseCommand();

        /**
        * Execute command
        */ 
        virtual void execute() = 0;

        /**
        * Return results from execute action.
        * @return result of the execute command
        */
        std::string get_result();

        /**
        * Set core pointer
        * @param core pointer to core
        */
        void set_core(Core*);
};

#endif