#include "core.h"
#include "invoker.h"
#include "commands.h"
#include "nogui.h"

void init_invoker(Invoker *inv, Core *core) {
    inv->set_backup(new Backup(core));
}

int main(int agrc, char *argv[]) {
    Core core;
    Invoker inv;
    init_invoker(&inv, &core);
    NoGui gui(&inv);
    gui.nogui_loop();
    return 0;
}