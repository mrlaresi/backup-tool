#include "core.h"
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;


Core::Core() {

}


int Core::load_settings() {
    fs::path p = "./settings.ini";
    std::error_code error;
    fs::canonical(p, error);
    if (error) {
        //first_time();
        return 0;
    }
    std::vector<std::string> content = fio.read_file(p);
    for (int i = 0; i < content.size(); i++) {
        std::cout << content[i] << "\n";
    }
    return 1;
}


int Core::is_first() {
    // TODO: replace with some other location in the future?
    fs::path p = "./settings.ini";
    return Validator::validate_file(p);
}


int Core::first_time() {
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


int Core::parse_input(const std::string& setting, const std::string& input) {
    
    return 1;
}