#include "core.h"
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

fs::path settings = "./settings.ini";

Core::Core() {

}


int Core::load_settings() {
    std::error_code error;
    settings = Validator::validate_path(settings);
    if (error) {
        //first_time();
        return 0;
    }
    std::vector<std::string> content = fio.read_file(settings);
    set_settings(content);
    return 1;
}


int Core::is_first() {
    // TODO: replace with some other location in the future?
    return Validator::validate_file(settings);
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
    return fio.add_backup(p);
}


int Core::remove_backup(const std::vector<std::string>& inputs) {
    fs::path p = Validator::validate_path(inputs[1]);
    if (p == "") { return 0; }
    return fio.remove_backup(p);
}


int Core::parse_input(const std::string& setting, const std::string& input) {
    
    return 1;
}


std::vector<std::string> Core::get_backups() {
    return fio.get_backups();
}


std::string Core::get_destination() {
    return fio.get_destination();
}


void Core::set_settings(const std::vector<std::string>& settings) {
    std::stringstream ss;
    std::string setting, value;
    for (unsigned i = 0; i < settings.size(); i++) {
        ss << settings[i];
        ss >> setting >> value;
        if (setting == "destination") {
            std::filesystem::path p = Validator::validate_path(value);
            if (p == "") { continue; }
            fio.set_backup_dest(p);
        }
        // clear stringstream
        std::stringstream().swap(ss);
    }
}