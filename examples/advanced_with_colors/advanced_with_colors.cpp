// Uncomment the following to enable decorations in log output
// Use a compatible serial monitor, in platformio set
// monitor_raw = 1

#include <ArduLog.h>
#include <Arduino.h>

ArduLog logger;

void setup() {
  Serial.begin(115200);
  delay(500);
  logger.init();
  logger.SetSerial(&Serial);
  logger.SetLogLevel(ArduLogLevel::Trace);
  logger.SetUseDecorations(true);
}

void loop() {
  LOG_DEBUG(LOG_BLUE, "Seconds since boot: ", LOG_GREEN, millis() / 1000);
  delay(1000);
}