#ifndef BACKUP_INVOKER
#define BACKUP_INVOKER

#include "basecommand.h"

/**
* Invokes commands
*/
class Invoker {
    private:
        BaseCommand *backup;
        BaseCommand *add_backup;
        BaseCommand *remove_backup;
        BaseCommand *get_backups;
        BaseCommand *get_destination;
    public:
        Invoker();
        ~Invoker();

        void set_backup(BaseCommand *command);
        void set_add_backup(BaseCommand *command);
        void set_remove_backup(BaseCommand *command);
        void set_get_backups(BaseCommand *command);
        void set_get_destination(BaseCommand *command);

        std::string do_backup();
        std::string do_add_backup(const std::string&);
        std::string do_remove_backup(const std::string&);
        std::string do_get_backups();
        std::string do_get_destination();
};

#endif