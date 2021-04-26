#ifndef BACKUP_COMMANDS
#define BACKUP_COMMANDS

#include <string>
#include "basecommand.h"

class Backup : public BaseCommand {
    public:
        Backup(Core *core);
        void execute() override;
};

#endif