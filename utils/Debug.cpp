#include "Debug.h"

#ifdef DEBUG
#include <iostream>
#endif

Debug::DefaultLogger Debug::defaultLogger{};
std::reference_wrapper<CustomLogger> Debug::logger = std::ref(Debug::defaultLogger);

void Debug::DefaultLogger::print(const std::string& message) {
#ifdef DEBUG
  using namespace std;
  
  cout << message << endl;
#endif
}

void Debug::setCustomLogger(CustomLogger& customLogger) {
  logger = std::ref(customLogger);
}

void Debug::reset() {
  logger = std::ref(defaultLogger);
}
