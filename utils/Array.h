//
//  Array.h
//  MeowMeow
//
//  Created by Alex Serdukov on 11.04.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Array_h
#define Array_h

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

class Array {
  public:
    template<typename T>
    static bool includes(std::vector<T>& list, T item) {
      auto lastIndexId = list.end();

      return std::find(list.begin(), lastIndexId, item) != lastIndexId;
    }

    template<typename T>
    static bool includes(std::vector<std::reference_wrapper<T>>& list, T& item) {
      auto lastIndexId = list.end();

      return find_if(list.begin(), lastIndexId, predicateFor(item)) != lastIndexId;
    }

    template <typename T>
    static void remove(std::vector<T>& list, T item)
    {
      auto itemMatches = std::remove(list.begin(), list.end(), item);

      list.erase(itemMatches);
    }

    template <typename T>
    static void remove(std::vector<std::reference_wrapper<T>>& list, T& item)
    {
      auto itemMatches = std::remove_if(list.begin(), list.end(), predicateFor(item));

      list.erase(itemMatches);
    }

  private:
    template <typename T>
    static auto predicateFor(T& item) {
      using namespace std;

      return [&](const reference_wrapper<T> &listItem) {
        T& wrappedItem = listItem.get();

        return addressof(wrappedItem) == addressof(item);
      };
    }
};

#endif /* Array_h */
