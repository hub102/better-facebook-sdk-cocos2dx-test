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
using namespace cocos2d;

#include <iostream>

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

void TestFacebookX::testButtonShareLink() {
  FBShareInfo info;
  info.type = FB_LINK;
  info.text = "ABC";
  info.title = "XYZ";
  info.link = "https://hub102.com";
  FacebookX::share(info);
}

void TestFacebookX::testButtonSharePhoto() {
  FBShareInfo info;
  info.type = FB_PHOTO;
  info.text = "ABC";
  info.title = "XYZ";
  info.media = FileUtils::getInstance()->getWritablePath() + "hoodsters.png";
  FacebookX::share(info);
}

void TestFacebookX::testButtonShareVideo() {
  FBGraphStoryProperties properties;
  properties.type = "better_fbx:person";
  properties.title = "I beat a friend";
  properties.description = "Score: 10000";
  properties.image = "https://fbcdn-photos-h-a.akamaihd.net/hphotos-ak-xfp1/t39.2081-0/p128x128/10333106_1693250547571713_1233636624_n.png";
  properties.url = "https://apps.facebook.com/joselitopuzzle_test/";

    std::string actionType = std::string("better_fbx:beat");
    std::string ppn = std::string("person");
    FacebookX::shareOpenGraphStory(properties, actionType, ppn);
}

void TestFacebookX::testReqInviteFriend() {
  FBAPIParam params;
  params[kRI_ResponseFields] = "id,name,picture,email,first_name,last_name,installed"; 
  FacebookX::requestInvitableFriends(params);
}

void TestFacebookX::testInviteFriends() {
  FacebookX::inviteFriendsWithInviteIds(mFriendIds, "BetterX", "This is a test invitation");
}

void TestFacebookX::onLogin(bool isLogin, const std::string& msg) {
  CCLOG("%d %s", isLogin, msg.c_str());
  CCLOG("Access token = %s", FacebookX::getAccessToken().c_str());
  CCLOG("User ID = %s", FacebookX::getUserID().c_str());
  map<string, string> params;
  FacebookX::api("me", "test_me");

  vector<string> permissions = FacebookX::getPermissionList();
    
  for(string p : permissions)
    CCLOG("Permission - %s", p.c_str());
}

void TestFacebookX::onSharedSuccess(const std::string& message) {
  CCLOG("onSharedSuccess: %s", message.c_str());
}

void TestFacebookX::onSharedFailed(const std::string& message) {
  CCLOG("onSharedFailed: %s", message.c_str());
}

void TestFacebookX::onSharedCancel() {
  CCLOG("onSharedCancel");
}

void TestFacebookX::onAPI(const std::string& key, const std::string& jsonData) {
    cout << "onAPI, tag = " << key << "\n";

    if (key == "test_me") {
        cout << "Data = " << jsonData << "\n";
    }
}

void TestFacebookX::onPermission(bool isLogin, const std::string& msg) {
  
}

void TestFacebookX::onFetchFriends(bool ok, const std::string& msg) {
  
}

void TestFacebookX::onRequestInvitableFriends( const FBInvitableFriendsInfo& friends ) {
  CCLOG("%s", friends.getOriginalString().c_str());
  
  mFriendIds.clear();
  
  for (auto it = friends.begin(); it != friends.end(); ++it) {
    mFriendIds.push_back((*it).getUserId());
  }
}

void TestFacebookX::onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg ) {
  CCLOG("%d %s", result, msg.c_str());
}

void TestFacebookX::onInviteFriendsResult( bool result, const std::string& msg ) {
  
}

void TestFacebookX::onGetUserInfo(const FBGraphUser &userInfo) {
    
}

//    void onGetUserInfo( const FBGraphUser& userInfo );