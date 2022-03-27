//
//  Debug.h
//  MeowMeow
//
//  Created by Alex Serdukov on 24.01.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Debug_h
#define Debug_h

#include <string>
#include <functional>

#ifdef DEBUG
#include <iostream>
#endif

typedef std::function<void(const std::string&)> CustomLogger;

class DebugLogger {
  private:
    static CustomLogger customLogger;

  public:
    static void setCustomLogger(CustomLogger logger);
    static void debug(const std::string& message);
};

inline void debugPrint(const std::string& message) {
  DebugLogger::debug(message);
}

#endif /* Debug_h */
