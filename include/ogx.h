#pragma once
#ifndef OGX_H
#define OGX_H

#include "oggex.h"
#include "cli.h"

std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks);
void setup_logging(arguments arguments);
int oggex(const char* command, Media media);
arguments init_args(int argc, char** argv);

#endif // OGX_H
