#include "core.h"

#include <iostream>
#include <fstream>
#include <thread>

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


std::string Core::backup() {
    fio.backup();
    return "";
}


std::string Core::add_backup(const std::string &input) {
    fs::path p = Validator::validate_path(input);
    if (p == "") { return 0; }
    fio.add_backup(p);
    return "";
}


std::string Core::remove_backup(const std::string &input) {
    fs::path p = Validator::validate_path(input);
    if (p == "") { return 0; }
    fio.remove_backup(p);
    return "";
}


int Core::parse_input(const std::string& setting, const std::string& input) {
    
    return 1;
}


std::string Core::get_backups() {
    return fio.get_backups();
}


std::string Core::get_destination() {
    return fio.get_destination();
}


/*int Core::backup_loop() {
    while (true) {
        std::cout << fio.get_destination() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout << fio.get_destination() << "\n";
        return 1;
    }
}*/


void Core::set_settings(const std::vector<std::string>& settings) {
    std::stringstream ss;
    std::string setting, value;
    for (unsigned i = 0; i < settings.size(); i++) {
        ss << settings[i];
        std::getline(ss, setting, '=');
        ss >> value;
        if (setting == "destination") {
            std::filesystem::path p = Validator::validate_path(value);
            if (p == "") { continue; }
            fio.set_backup_dest(p);
        }
        if (setting == "saveInterval") {

        }
        // clear stringstream
        std::stringstream().swap(ss);
    }
}