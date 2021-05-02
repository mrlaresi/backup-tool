#ifndef BACKUP_COMMANDS
#define BACKUP_COMMANDS

#include <string>
#include "basecommand.h"

class Backup : public BaseCommand {
    public:
        Backup(Core *core);
        std::string execute(const std::string&) override;
};

class AddBackup : public BaseCommand {
    public:
        AddBackup(Core *core);
        std::string execute(const std::string&) override;
};

class RemoveBackup : public BaseCommand {
    public:
        RemoveBackup(Core *core);
        std::string execute(const std::string&) override;
};

class GetBackups : public BaseCommand {
    public:
        GetBackups(Core *core);
        std::string execute(const std::string&) override;
};

class GetDestination : public BaseCommand {
    public:
        GetDestination(Core *core);
        std::string execute (const std::string&) override;
};

#endif