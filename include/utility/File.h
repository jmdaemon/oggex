#pragma once
#ifndef FILE_CPP_H
#define FILE_CPP_H

#include <string>
#include <initializer_list>
#include <filesystem>

// Third Party Libraries
#include <fmt/core.h>
#include <file.h>

const off_t MAX_FILE_POST_SIZE = 1024 * 1024 * 4; // 4MiB

void clean(std::initializer_list<std::filesystem::path> filepaths);

#endif
