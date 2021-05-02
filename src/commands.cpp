#include "commands.h"

Backup::Backup(Core *core) {
    set_core(core);
}


std::string Backup::execute(const std::string &_unused) {
    return core->backup();
}


AddBackup::AddBackup(Core *core) {
    set_core(core);
}


std::string AddBackup::execute(const std::string &input) {
    return core->add_backup(input);
}


RemoveBackup::RemoveBackup(Core *core) {
    set_core(core);
}


std::string RemoveBackup::execute(const std::string &input) {
    return core->remove_backup(input);
}


GetBackups::GetBackups(Core *core) {
    set_core(core);
}


std::string GetBackups::execute(const std::string &_unused) {
    return core->get_backups();
}


GetDestination::GetDestination(Core *core) {
    set_core(core);
}


std::string GetDestination::execute(const std::string &_unused) {
    return core->get_destination();
}