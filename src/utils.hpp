#pragma once

#include <filesystem>
#include "config.hpp"

namespace fs = std::filesystem;


std::string getLastAlbumItem();
size_t filesize(std::string &path);
std::string url_encode(const std::string &value);
