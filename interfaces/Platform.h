#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <sstream>

class Platform {
  private:
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
      nlString(std::move(getNLString())) {}

    const std::string& nl() {
      return nlString;
    }

    const std::string& resourcePath() {
      if (resourcePathString.length() == 0) {
        resourcePathString = std::move(getResourcePath());
      }

      return resourcePathString;
    }
};

#endif
