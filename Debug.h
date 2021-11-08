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
#ifdef DEBUG
#include <iostream>
#endif

inline void debugPrint(const std::string& message) {
#ifdef DEBUG
  using namespace std;
  
  cout << message << endl;
#endif
}

#endif /* Debug_h */
