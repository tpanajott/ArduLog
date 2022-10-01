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