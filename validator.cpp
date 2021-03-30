#include "validator.h"
#include <filesystem>


std::filesystem::path Validator::validate(const std::vector<std::string>& inputs) {
    /*if (validate_command(inputs[0])) { return 0; }
    if (validate_path(inputs[1])) { return 0; }
    return 1;*/
}

int Validator::validate_command(const std::string& input) {
    return 0;
}

std::filesystem::path Validator::validate_path(const std::string& input) {
    std::filesystem::path p = input;
    std::error_code error;
    std::filesystem::canonical(p, error);
    if (error) { p = ""; return p; }
    return p;
}