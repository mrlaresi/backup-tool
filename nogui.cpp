#include "nogui.h"

NoGui::NoGui() {
    fio.read_backup();    
}

void NoGui::backup() {
    fio.backup();
}

int main() {
    NoGui g;
    g.backup();
    return 0;
}