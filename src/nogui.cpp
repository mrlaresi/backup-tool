#include "nogui.h"
#include "core.h"
#include <iostream>
#include <filesystem>


NoGui::NoGui() {
    if (!core.is_first()) {
        this->first_time();
    }
    core.load_settings();
}


void NoGui::backup() {
    core.backup();
}


void NoGui::add_backup(const std::vector<std::string>& input) {
    if (!core.add_backup(input)) {
        //std::cout << "Filepath doesn't exist. No changes were made.\n";
    }
}


void NoGui::remove_backup(const std::vector<std::string>& input) {
    if (!core.remove_backup(input)) {
        std::cout << "Filepath isn't on the list. No changes were made\n";
    }
}


void NoGui::get_backups() {
    std::vector<std::string> paths = core.get_backups();
    std::cout << "Following paths will be copied on backup:\n";
    for (unsigned i = 0; i < paths.size(); i++) {
        std::cout << "  " << paths[i] << "\n";
    }
}


void NoGui::get_destination() {
    std::string path = core.get_destination();
    std::cout << "Files will be copied to following directory:\n";
    std::cout << "  " << path << "\n";
}


std::vector<std::string> NoGui::get_input() {
    std::string stri;
    std::cout << "Enter command > ";
    std::getline(std::cin, stri);
    std::stringstream ss;
    ss << stri;
    std::vector<std::string> ret;
    while (!ss.eof()) {
        ss >> stri;
        ret.push_back(stri);
    }
    return ret;
}


void NoGui::help() {
    std::cout << "Following commands are available as of now:\n";
    std::cout << "  exit: terminates the program\n";
    std::cout << "  backup: backups files\n";
    std::cout << "  add <path>: adds given filepath to list of files which will be backed up\n";
    std::cout << "  remove <path>: removes given filepath from the list of files\n";
    std::cout << "  filepaths: prints list of filepaths which will be backed up\n";
    std::cout << "  destination: prints the backup destination\n";
    std::cout << "  help: prints this help text\n";
}

int NoGui::nogui_loop() {
    std::cout << "Type 'help' to see all available commands.\nType 'exit' to exit the program." << std::endl;
    std::vector<std::string> answer;
    while (true) {
        answer = this->get_input();
        if (answer[0] == "exit") { break; }
        else if (answer[0] == "backup") { this->backup(); }
        else if (answer[0] == "add") { this->add_backup(answer); }
        else if (answer[0] == "remove") { this->remove_backup(answer); }
        else if (answer[0] == "filepaths") {this->get_backups(); }
        else if (answer[0] == "destination") {this->get_destination(); }
        else if (answer[0] == "help") { this->help(); }
        else { std::cout << "Unknown input" << std::endl; }
    }
    return 1;
}


void NoGui::first_time() {
    std::cout << "Looks like you started the program for the first time.\n";
    std::cout << "Insert the filepath where you would like to store your backups.\n";
    while (true) {
        std::cout << "> ";
        std::string input;
        std::cin >> input;
        int b = core.parse_input("destination=", input);
        if (b) {
            break;
        }
        std::cout << "Invalid filepath.\n";
    }
    //core.set_backup(p);
}


int main() {
    NoGui g;
    g.nogui_loop();   
}