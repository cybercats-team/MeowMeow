#include "Debug.h"

#ifdef DEBUG
#include <iostream>
#endif

void Debug::DefaultLogger::print(const std::string& message) {
#ifdef DEBUG
  using namespace std;
  
  cout << message << endl;
#endif
}

Debug Debug::instance{};
Debug& Debug::customize(Debug::instance);

Debug::Debug()
  : defaultLogger(),
    logger(std::ref(defaultLogger)) {}

void Debug::setLogger(CustomLogger& customLogger) {
  logger = std::ref(customLogger);
}

void Debug::reset() {
  logger = std::ref(defaultLogger);
}
