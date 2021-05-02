#include "invoker.h"

Invoker::Invoker() {};


Invoker::~Invoker() {
    delete backup;
    delete add_backup;
    delete remove_backup;
    delete get_backups;
    delete get_destination;
};


void Invoker::set_backup(BaseCommand *command) {
    backup = command;
};


void Invoker::set_add_backup(BaseCommand *command) {
    add_backup = command;
}


void Invoker::set_remove_backup(BaseCommand *command) {
    remove_backup = command;
}


void Invoker::set_get_backups(BaseCommand *command) {
    get_backups = command;
}


void Invoker::set_get_destination(BaseCommand *command) {
    get_destination = command;
}


std::string Invoker::do_backup() {
    return backup->execute();
}


std::string Invoker::do_add_backup(const std::string &input) {
    return add_backup->execute(input);
}


std::string Invoker::do_remove_backup(const std::string &input) {
    return remove_backup->execute(input);
}


std::string Invoker::do_get_backups() {
    return get_backups->execute();
}


std::string Invoker::do_get_destination() {
    return get_destination->execute();
}