#include <thread>
#include <algorithm> // std::find

#include "core.h"
#include "validator.h"
#include "fileinout.h"

namespace fs = std::filesystem;


Core::Core() {
    load_settings();
    
    fs::path backup_addr = Validator::validate_path(backup_addresses);
    fs::path backup_dest = Validator::validate_path(backup_destination);
    if (backup_addr == "") {
        FileInOut::create_file(backup_addresses);
    }
    
    if (backup_dest == "") {
        FileInOut::create_folder(backup_destination);
    }
    
    backup_addresses = Validator::validate_path(backup_addresses);
    backup_destination = Validator::validate_path(backup_destination);
    read_backup();
}


int Core::load_settings() {
    std::error_code error;
    settings = Validator::validate_path(settings);
    if (error) {
        //first_time();
        return 0;
    }
    std::vector<std::string> content = FileInOut::read_file(settings);
    set_settings(content);
    return 1;
}


std::string Core::backup() {
    time_t current_time = std::time(nullptr);
    unsigned count = 0, skip = 0;
    fs::path time_of_backup = FileInOut::get_time();

    std::stringstream return_message;
    return_message << "Performing backup on " 
        << backup_paths.size() << " locations.\n";

    for (unsigned i = 0; i < backup_paths.size(); i++) {
        if (FileInOut::modify_time(backup_paths[i]) < last_backup) { 
            skip++; 
            continue; 
        }
        return_message << "Copying directory: " << backup_paths[i] << "\n";
        
        fs::path destination = form_backup_path(backup_paths[i], time_of_backup);
        std::error_code error = FileInOut::copy(backup_paths[i], destination);
        // Shouldn't happen unless someone deletes the folder in middle of a
        // copy operation.
        if (error) {
            return_message << "Unexpected error occurred: \n" 
                << error.message() << "\n";
        }
        count++;
    }
    
    if (count > 0) {
        return_message << "Done. Total " << count << " folders backed up.\n";
        last_backup = current_time;
    }
    if (skip > 0) {
        return_message << "Skipped " << skip 
            << " folders as no modifications had been made\n";
    }
    return return_message.str();
}


std::string Core::add_backup(const std::string &input) {
    fs::path filepath = Validator::validate_path(input);
    if (filepath == "") { return "Invalid filepath: Path doesn't exist.\n"; }

    auto iterator = exists(filepath);
    if (iterator != backup_paths.end()) {
        return "Filepath already exists on the list. No changes were made.\n";
    }

    std::string e = FileInOut::write_to_file(backup_addresses, filepath);
    if (e != "") {return e; }

    backup_paths.push_back(filepath);
    return "Added filepath " + filepath.string() + "\n";
}


std::string Core::remove_backup(const std::string &input) {
    fs::path filepath = Validator::validate_path(input);
    if (filepath == "") { return "Invalid filepath: Path doesn't exist.\n"; }

    auto iterator = exists(filepath);
    if (iterator == backup_paths.end()) {
        return "Filepath is not on the list. No changes were made.\n";
    }

    std::string e = FileInOut::remove_line(backup_addresses, filepath);
    if (e != "") { return e; }

    backup_paths.erase(iterator);
    return "Removed filepath " + filepath.string() + "\n";
}


std::string Core::get_backups() {
    std::stringstream return_message;
    return_message << "Following files will be copied on backup:\n";
    for (unsigned i = 0; i < backup_paths.size(); i++) {
        return_message << "  " << backup_paths[i].string() << "\n";
    }
    return return_message.str();
}


std::string Core::get_destination() {
    return "Files will be copied to following directory:\n  " 
        + backup_destination.string() + "\n";
}


std::string Core::set_destination(const fs::path& path) {
    fs::path file_path = Validator::validate_path(path);
    if (Validator::validate_directory(file_path)) {
        backup_destination = path;
        return "New destination for backups: " + file_path.string();
    }
    return "Error: Filepath is not a directory.";
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
            set_destination(p);
        }
        if (setting == "saveInterval") {

        }
        // clear stringstream
        std::stringstream().swap(ss);
    }
}


void Core::read_backup() {
    fs::path path;
    std::vector<std::string> lines = FileInOut::read_file(backup_addresses);
    std::vector<fs::path> paths;
    for (unsigned i = 0; i < lines.size(); i++) {
        if (lines[i] == "") { continue; }
        path = Validator::validate_path(lines[i]);
        if (path == "") {
            continue;
        }
        backup_paths.push_back(path);
    }
}


fs::path Core::form_backup_path(const fs::path &filepath, const fs::path &time) {
    fs::path folder_name = FileInOut::fetch_filename_stem(filepath);
    if (!Validator::validate_directory(backup_destination / folder_name)) {
        fs::create_directory(backup_destination / folder_name);
    } 
        
    fs::path full_path = backup_destination / folder_name / time;
    return full_path;
}


std::vector<fs::path>::iterator Core::exists(const fs::path& path) {
    std::vector<fs::path>::iterator it = std::find(backup_paths.begin(), backup_paths.end(), path);
    return it;
}