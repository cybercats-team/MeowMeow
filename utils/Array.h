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
#include <algorithm>
#include <functional>

class Array {
  public:
    template<typename T>
    static bool includes(std::vector<T> list, T item) {
      return std::count(list.begin(), list.end(), item) > 0;
    }
  
    template<typename T>
    static bool includes(std::vector<std::reference_wrapper<T>> list, T& item) {
      using namespace std;
      
      return count_if(list.begin(), list.end(), [&](const reference_wrapper<T> &listItem) {
        T& wrappedItem = listItem.get();
        
        return &wrappedItem == &item;
      }) > 0;
    }
  
    template<typename T>
    static long indexOf(std::vector<T> list, T item) {
      auto indexId = std::find(list.begin(), list.end(), item);
      
      return getIndex(indexId);
    }
  
    template<typename T>
    static long indexOf(std::vector<std::reference_wrapper<T>> list, T& item) {
      using namespace std;
      
      auto indexId = find_if(list.begin(), list.end(), [&](const reference_wrapper<T> &listItem) {
        T& wrappedItem = listItem.get();
        
        return &wrappedItem == &item;
      });
      
      return getIndex<reference_wrapper<T>>(list, indexId);
    }
  
    template <typename T>
    static void remove(std::vector<T>& list, size_t index)
    {
        auto indexId = list.begin();
        
        std::advance(indexId, index);
        list.erase(indexId);
    }
  
  private:
    template<typename T>
    static long getIndex(std::vector<T> list, typename std::vector<T>::iterator indexId) {
      if (indexId == list.end()) {
        return -1;
      }
      
      return indexId - list.begin();
    }
};

#endif /* Array_h */
