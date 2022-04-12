#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <sstream>
#include <filesystem>

class Platform {
  private:
    std::string appName;
    std::string nlString;
    std::string resourcePathString;

    const std::string getNLString() {
      using namespace std;

      ostringstream nlStream;
      nlStream << endl;

      return nlStream.str();
    }

  protected:
    virtual const std::string getResourcePath() = 0;

  public:
    Platform() : resourcePathString(),
      nlString(getNLString()) {}
      
    void setAppName(const std::string& appName) {
      this->appName = appName;
    }  

    const std::string& nl() {
      return nlString;
    }

    const char ds() {
      return std::filesystem::path::preferred_separator;
    }

    const std::string& resourcePath() {
      if (resourcePathString.length() == 0) {
        resourcePathString = getResourcePath();
      }

      return resourcePathString;
    }
};

#endif
