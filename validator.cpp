#include "validator.h"
#include <filesystem>


std::filesystem::path Validator::validate_path(const std::string& input) {
    return Validator::canonical(input);
}


int Validator::validate_file(const std::filesystem::path& path) {
    std::filesystem::path p = Validator::canonical(path);
    return std::filesystem::is_regular_file(p);
}


std::filesystem::path Validator::canonical(const std::filesystem::path& path) {
    std::filesystem::path p = path;
    std::error_code error;
    std::filesystem::canonical(p, error);
    if (error) { p = ""; return p; }
    std::filesystem::absolute(p);
    return p;
}
