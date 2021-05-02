#include "basecommand.h"
#include <string>

BaseCommand::~BaseCommand() {}

void BaseCommand::set_core(Core *core) {
    this->core = core; 
};