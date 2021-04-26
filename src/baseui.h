#ifndef BACKUP_BASEUI
#define BACKUP_BASEUI

#include <string>
#include <vector>

class BaseUI {
    public:
        virtual ~BaseUI();
        virtual void backup() = 0;
};

#endif