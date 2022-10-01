#ifndef ARDULOG_H
#define ARDULOG_H

#define LOG_SHORT_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#include <Arduino.h>
#include <string>
#include <Snippets.h>

enum class ArduLogLevel {
    None,
    Error,
    Warning,
    Info,
    Debug,
    Trace
};

class ArduLog {
    public:
        HardwareSerial *_hwSerial;
        ArduLogLevel _configuredLogLevel {ArduLogLevel::Debug};
        void init();
        // Configure the serial output to be used for logging
        void SetSerial(HardwareSerial *serial);
        void SetLogLevel(const ArduLogLevel logLevel);
        static ArduLog *_instance;
        static ArduLog *getInstance();

        // This has to be in the header file to work unfortunetly.
        // Print all parts of the log message
        template <typename LogMessageT, typename... Args>
        void printlnLog(LogMessageT logMessage, Args... args) {
            this->_hwSerial->print(logMessage);
            
            if(sizeof...(args) > 0) {
                this->printlnLog(args...);
            }
        }

        // This function will print the last part of the log and end it with a \n.
        template <typename LogMessageT>
        void printlnLog(LogMessageT logMessage) {
            this->_hwSerial->println(logMessage);
        }

        // This has to be in the header file to work unfortunetly.
        template <typename... Args>
        void Log(const ArduLogLevel logLevel, const char* filename, int lineNumber, const char* functionName, Args&&... args) {
            // Check if logLevel is a low enough level to be printed
            // Else, cancel operation.
            if(logLevel > this->_configuredLogLevel && this->_configuredLogLevel != ArduLogLevel::None) {
                return;
            }

            // Set logLevelStr according to logLevel
            std::string logLevelStr;
            switch (logLevel)
            {
                case ArduLogLevel::None:
                    logLevelStr = "[NONE]  ";
                    break;

                case ArduLogLevel::Error:
                    logLevelStr = "[ERROR] ";
                    break;
                
                case ArduLogLevel::Warning:
                    logLevelStr = "[WARN]  ";
                    break;

                case ArduLogLevel::Info:
                    logLevelStr = "[INFO]  ";
                    break;
                
                case ArduLogLevel::Debug:
                    logLevelStr = "[DEBUG] ";
                    break;

                case ArduLogLevel::Trace:
                    logLevelStr = "[TRACE] ";
                    break;

                default:
                    logLevelStr = "[UNKNOWN] ";
                    break;
            }

            this->printlnLog(logLevelStr.c_str(), filename, ":", lineNumber, " (f.", lineNumber, ") ",  args...);

        }

    private:
        ArduLog *instance;

};

#endif