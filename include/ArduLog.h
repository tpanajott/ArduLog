#ifndef ARDULOG_H
#define ARDULOG_H

#define LOG_SHORT_FILENAME                                 \
  (strrchr(__FILE__, '/')    ? strrchr(__FILE__, '/') + 1  \
   : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 \
                             : __FILE__)

#include <Arduino.h>
#include <Snippets.h>
#include <string>

enum class ArduLogLevel
{
  None,
  Error,
  Warning,
  Info,
  Debug,
  Trace
};

class ArduLog
{
public:
  HardwareSerial *_hwSerial;
  ArduLogLevel _configuredLogLevel{ArduLogLevel::Debug};
  bool _useDecorations = false;
  void init();
  // Configure the serial output to be used for logging
  void SetSerial(HardwareSerial *serial);
  void SetLogLevel(const ArduLogLevel logLevel);
  void SetUseDecorations(bool useDecorations);
  static ArduLog *_instance;
  static ArduLog *getInstance();

  // This has to be in the header file to work unfortunetly.
  // Print all parts of the log message
  template <typename LogMessageT, typename... Args>
  void printlnLog(LogMessageT logMessage, Args... args)
  {
    if (!this->_isDecorationString(logMessage))
    {
      this->_hwSerial->print(logMessage);
    }

    if (sizeof...(args) > 0)
    {
      this->printlnLog(args...);
    }
  }

  // This function will print the last part of the log and end it with a \n.
  template <typename LogMessageT>
  void printlnLog(LogMessageT logMessage)
  {
    if (!this->_isDecorationString(logMessage))
    {
      this->_hwSerial->print(logMessage);
    }
    this->_hwSerial->println(); // Break line.
  }

  // This has to be in the header file to work unfortunetly.
  template <typename... Args>
  void Log(const ArduLogLevel logLevel, const char *filename, int lineNumber, const char *functionName, Args &&...args)
  {
    // Check if logLevel is a low enough level to be printed
    // Else, cancel operation.
    if (logLevel > this->_configuredLogLevel || this->_configuredLogLevel == ArduLogLevel::None)
    {
      return;
    }

#ifdef ESP32
    // Lock serial mutex
    xSemaphoreTake(this->_serialMutex, portMAX_DELAY);
#endif

    // Set logLevelStr according to logLevel
    std::string logLevelStr;
    switch (logLevel)
    {
    case ArduLogLevel::None:
      logLevelStr = LOG_LIGHT_GRAY;
      logLevelStr += "[NONE]  ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    case ArduLogLevel::Error:
      logLevelStr = LOG_RED;
      logLevelStr += "[ERROR] ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    case ArduLogLevel::Warning:
      logLevelStr = LOG_YELLOW;
      logLevelStr += "[WARN]  ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    case ArduLogLevel::Info:
      logLevelStr = LOG_BLUE;
      logLevelStr += "[INFO]  ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    case ArduLogLevel::Debug:
      logLevelStr = LOG_MAGENTA;
      logLevelStr += "[DEBUG] ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    case ArduLogLevel::Trace:
      logLevelStr = LOG_WHITE;
      logLevelStr += "[TRACE] ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;

    default:
      logLevelStr = LOG_GRAY;
      logLevelStr += "[UNKNOWN] ";
      logLevelStr += LOG_RESET_DECORATIONS;
      break;
    }
    this->printlnLog(logLevelStr.c_str(), filename, ":", lineNumber, " (f.",
                     LOG_BOLD, functionName, LOG_RESET_DECORATIONS, ") ",
                     args..., LOG_RESET_DECORATIONS);

#ifdef ESP32
    xSemaphoreGive(this->_serialMutex);
#endif
  }

private:
  ArduLog *instance;
  template <typename LogMessageT>
  bool _isDecorationString(LogMessageT logMessage)
  {
    if (!this->_useDecorations)
    {
      if constexpr (std::is_same<const char *, LogMessageT>::value)
      {
        std::string str = (const char *)logMessage;
        return str.compare(0, 4, "\e[1;") == 0;
      }
    }
    return false;
  }
#ifdef ESP32
  SemaphoreHandle_t _serialMutex;
#endif
};

#endif