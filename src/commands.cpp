#include "commands.h"

Backup::Backup(Core *core) {
    set_core(core);
}


void Backup::execute() {
    result = this->core->backup();
}