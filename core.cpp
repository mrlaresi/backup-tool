#include "core.h"

namespace fs = std::filesystem;

Core::Core() {
    
}

int Core::add_backup(const std::vector<std::string>& inputs) {
    fs::path p = Validator::validate_path(inputs[1]);
    if (p == "") { return 0; }
    fio.add_backup(p);
}

int Core::remove_backup(std::vector<std::string>&) {

}