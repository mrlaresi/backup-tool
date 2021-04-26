#include "invoker.h"

Invoker::Invoker() {};


Invoker::~Invoker() {
    delete backup;
};


void Invoker::set_backup(BaseCommand *command) {
    this->backup = command;
};


void Invoker::do_backup() {
    this->backup->execute();
}