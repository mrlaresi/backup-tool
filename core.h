#ifndef BACKUP_CORE_H
#define BACKUP_CORE_H

#include "validator.h"
#include "fileinout.h"

class Core {
    private:
        FileInOut fio;
    public:
        Core();
        int add_backup(const std::vector<std::string>&);
        int remove_backup(std::vector<std::string>&);
    private:
};

#endif