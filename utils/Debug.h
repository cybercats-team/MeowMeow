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
#include "String.h"
#endif

class CustomLogger {
  public:
    virtual void print(const std::string& message) = 0;
};


class Debug {
  private:
    class DefaultLogger : public CustomLogger {
      void print(const std::string& message) override;
    };

    static DefaultLogger defaultLogger;
    static std::reference_wrapper<CustomLogger> logger;

  public:    
    template<typename ... Args>
    static void printf(const std::string& format, Args ... args) {
#ifdef DEBUG
      std::string formatted = String::format(format, args ...);

      logger.get().print(formatted);
#endif
    }

    static void setCustomLogger(CustomLogger& logger);
    static void reset();
};

#endif /* Debug_h */
