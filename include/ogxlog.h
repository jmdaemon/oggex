#pragma once
#ifndef OGXLOG_H
#define OGXLOG_H

#include <spdlog/logger.h>

namespace library {
  std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks);
}
#endif // OGXLOG_H
