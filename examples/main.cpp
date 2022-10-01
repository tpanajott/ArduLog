#include <Arduino.h>
#include <ArduLog.h>

ArduLog logger;

void setup() {
  Serial.begin(115200);
  delay(500);
  logger.init();
  logger.SetSerial(&Serial);
  logger.SetLogLevel(ArduLogLevel::Debug);
  
  LOG_ERROR("Error message");
  LOG_WARNING("Warning message");
  LOG_INFO("Info message");
  LOG_DEBUG("Debug message");
  LOG_TRACE("Trace message");
}

void loop() {
  delay(500);
}