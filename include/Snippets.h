#ifndef ARDULOG_SHORTCUTS
#define ARDULOG_SHORTCUTS

// Colors codes available as "shortcut" for printing log messages.
#define LOG_BLACK "\e[1;30m"
#define LOG_RED "\e[1;31m"
#define LOG_GREEN "\e[1;32m"
#define LOG_YELLOW "\e[1;33m"
#define LOG_BLUE "\e[1;34m"
#define LOG_MAGENTA "\e[1;35m"
#define LOG_CYAN "\e[1;36m"
#define LOG_LIGHT_GRAY "\e[1;37m"
#define LOG_GRAY "\e[1;37m"
#define LOG_WHITE "\e[1;97m"
#define LOG_RESET_DECORATIONS "\e[1;0m"

#define LOG_BOLD "\e[1;1m"

#define LOG_ERROR(...)                                                 \
  ArduLog::getInstance()->Log(ArduLogLevel::Error, LOG_SHORT_FILENAME, \
                              __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...)                                                 \
  ArduLog::getInstance()->Log(ArduLogLevel::Warning, LOG_SHORT_FILENAME, \
                              __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...)                                                 \
  ArduLog::getInstance()->Log(ArduLogLevel::Info, LOG_SHORT_FILENAME, \
                              __LINE__, __func__, __VA_ARGS__)
#define LOG_DEBUG(...)                                                 \
  ArduLog::getInstance()->Log(ArduLogLevel::Debug, LOG_SHORT_FILENAME, \
                              __LINE__, __func__, __VA_ARGS__)
#define LOG_TRACE(...)                                                 \
  ArduLog::getInstance()->Log(ArduLogLevel::Trace, LOG_SHORT_FILENAME, \
                              __LINE__, __func__, __VA_ARGS__)

#endif