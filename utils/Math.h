//
//  Math.h
//  MeowMeow
//
//  Created by Alex Serdukov on 31.10.2021.
//  Copyright © 2021 Alex Serdukov. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include <SFML/System.hpp>

class Math {
  public:
    static sf::Int64 gcd(sf::Int64 a, sf::Int64 b) {
      using namespace sf;
      
      Int64 first = a;
      Int64 second = b;
      
      while (second != 0) {
        Int64 next = first % second;
        
        first = second;
        second = next;
      }
      
      return first;
    }
  
    static sf::Int64 lcm(sf::Int64 a, sf::Int64 b) {
      return a * b / gcd(a, b);
    }
};

#endif /* Math_h */
