#include "core.h"
#include "invoker.h"
#include "commands.h"
#include "nogui.h"

void init_invoker(Invoker *inv, Core *core) {
    inv->set_backup(new Backup(core));
    inv->set_add_backup(new AddBackup(core));
    inv->set_remove_backup(new RemoveBackup(core));
    inv->set_get_backups(new GetBackups(core));
    inv->set_get_destination(new GetDestination(core));
}

int main(int agrc, char *argv[]) {
    Core core;
    Invoker inv;
    init_invoker(&inv, &core);
    NoGui gui(&inv);
    gui.nogui_loop();
    return 0;
}