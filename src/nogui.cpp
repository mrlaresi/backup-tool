#include "nogui.h"
#include "core.h"

#include <iostream>
#include <filesystem>
#include <thread>


NoGui::NoGui(Invoker *invoker) {
    this->invoker = invoker;
    /*if (!core.is_first()) {
        this->first_time();
    }
    core.load_settings();*/
}


NoGui::~NoGui() {}


void NoGui::backup() {
    print(invoker->do_backup());
}


void NoGui::add_backup(const std::string &input) {
    print(invoker->do_add_backup(input));
}


void NoGui::remove_backup(const std::string &input) {
    print(invoker->do_remove_backup(input));
}


void NoGui::get_backups() {
    print(invoker->do_get_backups());
}


void NoGui::get_destination() {
    print(invoker->do_get_destination());
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
    print("Following commands are available as of now:\
        \n  exit: terminates the program\
        \n  backup: backups files\
        \n  add <path>: adds given filepath to list of files which will be backed up\
        \n  remove <path>: removes given filepath from the list of files\
        \n  filepaths: prints list of filepaths which will be backed up\
        \n  destination: prints the backup destination\
        \n  help: prints this help text\
        \n");
}


void NoGui::print(const std::string &input) {
    std::cout << input;
}


int NoGui::nogui_loop() {
    std::cout << "Type 'help' to see all available commands.\nType 'exit' to exit the program." << std::endl;
    std::vector<std::string> answer;
    while (true) {
        answer = get_input();
        if (answer[0] == "exit") { break; }
        else if (answer[0] == "backup") { backup(); }
        else if (answer[0] == "add") { add_backup(answer[1]); }
        else if (answer[0] == "remove") { remove_backup(answer[1]); }
        else if (answer[0] == "filepaths") { get_backups(); }
        else if (answer[0] == "destination") { get_destination(); }
        else if (answer[0] == "help") { help(); }
        else { std::cout << "Unknown input" << std::endl; }
    }
    return 1;
}


/*int NoGui::backup_loop() {
    std::cout << "lööps\n";
    return core.backup_loop();
}*/


void NoGui::first_time() {
    /*std::cout << "Looks like you started the program for the first time.\n";
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
    }*/
    //core.set_backup(p);
}


/*int main() {
    NoGui g;
    g.nogui_loop();
    std::thread first(&NoGui::nogui_loop, &g);   
    std::thread second(&NoGui::backup_loop, &g);
    first.join();
    second.join();
    std::cout << "exit\n";
    return 0;
}*/