//
//  TestFacebookX.hpp
//  FacebookXTest
//
//  Created by Thuy Dong Xuan on 4/12/16.
//
//

#ifndef TestFacebookX_hpp
#define TestFacebookX_hpp

#include "cocos2d.h"

class TestFacebookX {
  
  static TestFacebookX* mSharedInstance;
  
public:
  static TestFacebookX* getInstance();
  
  void testButton();
};

#endif /* TestFacebookX_hpp */
