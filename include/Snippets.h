#ifndef ARDULOG_SHORTCUTS
#define ARDULOG_SHORTCUTS

#define LOG_ERROR(...) ArduLog::getInstance()->Log(ArduLogLevel::Error, LOG_SHORT_FILENAME, __LINE__, __func__, __VA_ARGS__)
#define LOG_WARNING(...) ArduLog::getInstance()->Log(ArduLogLevel::Warning, LOG_SHORT_FILENAME, __LINE__, __func__, __VA_ARGS__)
#define LOG_INFO(...) ArduLog::getInstance()->Log(ArduLogLevel::Info, LOG_SHORT_FILENAME, __LINE__, __func__, __VA_ARGS__)
#define LOG_DEBUG(...) ArduLog::getInstance()->Log(ArduLogLevel::Debug, LOG_SHORT_FILENAME, __LINE__, __func__, __VA_ARGS__)
#define LOG_TRACE(...) ArduLog::getInstance()->Log(ArduLogLevel::Trace, LOG_SHORT_FILENAME, __LINE__, __func__, __VA_ARGS__)

#endif