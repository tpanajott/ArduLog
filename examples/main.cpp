// Uncomment the following to enable decorations in log output
// Use a compatible serial monitor, in platformio set
// monitor_raw = 1
// #define ARDULOG_USE_DECORATIONS 1

#include <ArduLog.h>
#include <Arduino.h>

ArduLog logger;

void setup() {
  Serial.begin(115200);
  delay(500);
  logger.init();
  logger.SetSerial(&Serial);
  logger.SetLogLevel(ArduLogLevel::Trace);

  LOG_ERROR("Error message");
  LOG_WARNING("Warning message");
  LOG_INFO("Info message");
  LOG_DEBUG("Debug message");
  LOG_TRACE("Trace message");
}

void loop() { delay(500); }