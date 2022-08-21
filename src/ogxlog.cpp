#include "ogxlog.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace library {
  static const std::string logger_name = "oggex";

  // Registers the libary logger
  std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks) {
      auto logger = spdlog::get(logger_name);
      if (!logger) {
          if (sinks.size() > 0) {
              logger = std::make_shared<spdlog::logger>(logger_name, std::begin(sinks), std::end(sinks));
              spdlog::register_logger(logger);
          } else {
              logger = spdlog::stdout_color_mt(logger_name);
          }
      }
      return logger;
  }
}
