#include "nogui.h"
#include <iostream>


NoGui::NoGui() {
    fio.read_backup();    
}


void NoGui::backup() {
    fio.backup();
}


void NoGui::add_backup(const std::vector<std::string>& input) {
    if (input.size() < 2) { 
        std::cerr << "Invalid input for command 'add'" << std::endl; 
        return;
    }
    fio.add_backup(input[1]);
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
    std::cout << "  help: prints this help text" << std::endl;
}


int main() {
    NoGui g;
    std::cout << "Type 'help' to see all available commands.\nType 'exit' to exit the program." << std::endl;
    std::vector<std::string> answer;
    while (true) {
        answer = g.get_input();
        if (answer[0] == "exit") { break; }
        else if (answer[0] == "backup") { g.backup(); }
        else if (answer[0] == "add") { g.add_backup(answer); }
        else if (answer[0] == "help") { g.help(); }
        else { std::cout << "Unknown input" << std::endl; }
    }
    return 0;
}