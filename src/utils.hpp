#pragma once

#include <filesystem>
#include <vector>
#include "config.hpp"

std::vector<std::filesystem::directory_entry> getAlbumItemsPastDate(int year, int month, int day);
std::string getLastAlbumItem();
size_t filesize(std::string &path);
std::string url_encode(const std::string &value);
