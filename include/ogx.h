#pragma once
#ifndef OGX_H
#define OGX_H

#include "oggex.h"
#include "cli.h"

std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks);
void setup_logging(arguments arguments);
int oggex(const char* command, Media media);
arguments init_args(int argc, char** argv);

// For gui executables
arguments init_args_gui(int argc, char** argv);
bool cmd_specified(struct arguments& args);

#endif // OGX_H
