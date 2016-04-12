//
//  TestFacebookX.cpp
//  FacebookXTest
//
//  Created by Thuy Dong Xuan on 4/12/16.
//
//

#include "TestFacebookX.hpp"

TestFacebookX* TestFacebookX::mSharedInstance = nullptr;

TestFacebookX* TestFacebookX::getInstance() {
  if (!mSharedInstance)
    mSharedInstance = new TestFacebookX();
  
  return mSharedInstance;
}

void TestFacebookX::testButton() {
  CCLOG("TestFacebookX ------> abc");
}