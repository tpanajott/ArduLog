#include <ArduLog.h>

ArduLog *ArduLog::_instance;

void ArduLog::init() {
    ArduLog::_instance = this;
}

ArduLog *ArduLog::getInstance() {
    return ArduLog::_instance;
}

void ArduLog::SetSerial(HardwareSerial *serial) {
    this->_hwSerial = serial;
}

void ArduLog::SetLogLevel(const ArduLogLevel logLevel) {
    ArduLog::_configuredLogLevel = logLevel;
}

// template<typename LogMessageT>
// void ArduLog::Log(LogMessageT logMessage) {
//     //ArduLog::_hwSerial->println(logMessage);
//     // this->_hwSerial->println(logLevel);
//     this->_hwSerial->println(logMessage);
// }