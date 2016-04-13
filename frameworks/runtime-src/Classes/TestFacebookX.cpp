//
//  TestFacebookX.cpp
//  FacebookXTest
//
//  Created by Thuy Dong Xuan on 4/12/16.
//
//

#include "TestFacebookX.hpp"

using namespace h102;
using namespace std;

TestFacebookX* TestFacebookX::mSharedInstance = nullptr;

TestFacebookX* TestFacebookX::getInstance() {
  if (!mSharedInstance)
    mSharedInstance = new TestFacebookX();
  
  return mSharedInstance;
}

TestFacebookX::TestFacebookX() {
  FacebookX::setListener(this);
}

void TestFacebookX::testButtonLogin() {
//  CCLOG("TestFacebookX ------> abc");
  FacebookX::login();
}

void TestFacebookX::testButtonLogout() {
//  CCLOG("TestFacebookX ------> abc");
  FacebookX::logout();
  // CCLOG("Is logged in = %d", FacebookX::isLoggedIn());
  // CCLOG("Access token = %s", FacebookX::getAccessToken().c_str());
  // CCLOG("User ID = %s", FacebookX::getUserID().c_str());
}

void TestFacebookX::onLogin(bool isLogin, const std::string& msg) {
  CCLOG("%d %s", isLogin, msg.c_str());
  CCLOG("Access token = %s", FacebookX::getAccessToken().c_str());
  // CCLOG("User ID = %s", FacebookX::getUserID().c_str());
  
  vector<string> permissions = FacebookX::getPermissionList();
  
  for(string p : permissions)
    CCLOG("Permission - %s", p.c_str());
}

void TestFacebookX::onSharedSuccess(const std::string& message) {
  
}

void TestFacebookX::onSharedFailed(const std::string& message) {
  
}

void TestFacebookX::onSharedCancel() {
  
}

void TestFacebookX::onAPI(const std::string& key, const std::string& jsonData) {
  
}

void TestFacebookX::onPermission(bool isLogin, const std::string& msg) {
  
}

void TestFacebookX::onFetchFriends(bool ok, const std::string& msg) {
  
}

//    void onRequestInvitableFriends( const FBInvitableFriendsInfo& friends );
void TestFacebookX::onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg ) {
  
}

void TestFacebookX::onInviteFriendsResult( bool result, const std::string& msg ) {
  
}

//    void onGetUserInfo( const FBGraphUser& userInfo );