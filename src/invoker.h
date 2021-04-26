#ifndef BACKUP_INVOKER
#define BACKUP_INVOKER
#include "basecommand.h"

/**
* Invokes commands
*/
class Invoker {
    private:
        BaseCommand *backup;
    public:
        Invoker();

        ~Invoker();

        void set_backup(BaseCommand *command);

        void do_backup();
};

#endif