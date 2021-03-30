#include "core.h"
#include <iostream>

namespace fs = std::filesystem;

Core::Core() {

}

int Core::read_backup() {
    fio.read_backup();
    return 1;
}

int Core::backup() {
    fio.backup();
    return 1;
}

int Core::add_backup(const std::vector<std::string>& inputs) {
    fs::path p = Validator::validate_path(inputs[1]);
    if (p == "") { return 0; }
    fio.add_backup(p);
    return 1;
}

int Core::remove_backup(const std::vector<std::string>& inputs) {
    fs::path p = Validator::validate_path(inputs[1]);
    if (p == "") { return 0; }
    fio.remove_backup(p);
    return 1;
}