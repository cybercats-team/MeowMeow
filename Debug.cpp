#include "Debug.h"

CustomLogger DebugLogger::customLogger = nullptr;

void DebugLogger::setCustomLogger(CustomLogger logger) {
#ifdef DEBUG
  customLogger = std::move(logger);
#endif
}

void DebugLogger::debug(const std::string& message) {
#ifdef DEBUG
  using namespace std;

  if (customLogger == nullptr) {
    cout << message << endl;
  }
  else {
    customLogger(message);
  }
#endif
}
