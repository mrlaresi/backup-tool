#ifndef NOGUI_H
#define NOGUI_H

#include "fileinout.h"

class NoGui {
    private:
        FileInOut fio;
    public:
        /** Default constructor */
        NoGui();

        /** Backups modified files */
        void backup();
};

#endif
