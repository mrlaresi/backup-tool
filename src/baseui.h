#ifndef BACKUP_BASEUI
#define BACKUP_BASEUI

#include <string>
#include <vector>

class BaseUI {
    public:
        virtual ~BaseUI() {};
        virtual void backup() = 0;
        virtual void add_backup(const std::string&) = 0;
        virtual void remove_backup(const std::string&) = 0;
        virtual void get_backups() = 0;
        virtual void get_destination() = 0;
};

#endif