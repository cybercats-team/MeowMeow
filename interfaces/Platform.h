#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include <sstream>

class Platform {
  private:
    std::string nlString;
  public:
    Platform(): nlString() {
      using namespace std;

      ostringstream nlStream;
      
      nlStream << endl;
      nlString = nlStream.str();
    }

    const std::string& nl() {
      return nlString;
    }

    virtual const std::string& resourcePath() = 0;
};

#endif