#include "ogxlog.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace library {
  //static const std::string logger_name = log_lib;
  static const std::string logger_name = "oggex";

  // Registers the libary logger for 
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

  //void trace(std::string message) {
      //auto logger = spdlog::get(logger_name);
      //if (logger) {
          //logger->trace("{}::{}", __FUNCTION__, message);
      //}
  //}

  //void info(std::string message) {
      //auto logger = spdlog::get(logger_name);
      //if (logger) {
          //logger->info("{}::{}", __FUNCTION__, message);
      //}
  //}

  //void warn(std::string message) {
      //auto logger = spdlog::get(logger_name);
      //if (logger) {
          //logger->warn("{}::{}", __FUNCTION__, message);
      //}
  //}

  //void debug(std::string message) {
      //auto logger = spdlog::get(logger_name);
      //if (logger) {
          //logger->debug("{}::{}", __FUNCTION__, message);
      //}
  //}

  //void error(std::string message) {
      //auto logger = spdlog::get(logger_name);
      //if (logger) {
          //logger->warn("{}::{}", __FUNCTION__, message);
      //}
  //}
}
