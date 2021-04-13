#include "validator.h"
#include <filesystem>


std::filesystem::path Validator::validate_path(const std::string& input) {
    std::filesystem::path p = Validator::canonical(input);
    if (p == "") { return p; }
    return p;
}


int Validator::validate_file(const std::filesystem::path& path) {
    std::filesystem::path p = Validator::canonical(path);
    return std::filesystem::is_regular_file(p);
}


std::filesystem::path Validator::canonical(const std::filesystem::path& path) {
    std::filesystem::path p = path;
    std::error_code error;
    p = std::filesystem::absolute(p);
    p = std::filesystem::canonical(p.lexically_normal(), error);
    if (error) { p = ""; return p; }
    return p;
}
