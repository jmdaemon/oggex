#pragma once
#ifndef OGXLOG_H
#define OGXLOG_H

#include <spdlog/logger.h>
//#include <spdlog/fmt/bundled/core.h>

namespace library {
  std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks);

  void trace(std::string message);
  void info(std::string message);
  void warn(std::string message);
  void debug(std::string message);
  void error(std::string message);
}
#endif // OGXLOG_H
