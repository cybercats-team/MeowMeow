#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <memory>
#include <string>
#include <stdexcept>

class String {
  private:
    template<typename T>
    static auto convert(T&& t) {
      using namespace std;

      if constexpr (is_same<remove_cv_t<remove_reference_t<T>>, string>::value) {
        return forward<T>(t).c_str();
      } else {
        return forward<T>(t);
      }      
    }

    template<typename ... Args>
    static std::string sprintf(const std::string& format, Args&& ... args) {
      using namespace std;

      const char* formatString = format.c_str();
      int formattedLength = snprintf(nullptr, 0, formatString, args ...);

      if (formattedLength < 0) {
        throw runtime_error("Error during formatting.");
      }

      size_t formattedSize = static_cast<size_t>(formattedLength + 1);
      unique_ptr<char[]> formattedStringPtr(new char[formattedSize]);
      char* formattedString = formattedStringPtr.get();

      snprintf(formattedString, formattedSize, formatString, args ...);
      return string(formattedString, formattedString + formattedLength);
    }
  public:
    template<typename ... Args>
    static std::string format(const std::string format, Args&& ... args) {
      return sprintf(format, convert(std::forward<Args>(args))...);
    }
};

#endif