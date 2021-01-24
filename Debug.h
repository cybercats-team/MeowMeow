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

using namespace std;

inline void debugPrint(string message) {
#ifdef DEBUG
  cout << message << endl;
#endif
}

#endif /* Debug_h */
