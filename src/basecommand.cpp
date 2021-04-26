#include "basecommand.h"
#include <string>

BaseCommand::~BaseCommand() {}

std::string BaseCommand::get_result() {
    return result;
};

void BaseCommand::set_core(Core *core) {
    this->core = core; 
};