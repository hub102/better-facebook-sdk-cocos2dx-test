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

#include "../../FacebookX/Classes/FacebookX.hpp"

#include <vector>

class TestFacebookX : public h102::FacebookListener {
  
  static TestFacebookX* mSharedInstance;
  
  std::vector<std::string> mFriendIds;
  
public:
  static TestFacebookX* getInstance();
  
  TestFacebookX();
  
  void testButtonLogin();
  void testButtonLogout();
  void testButtonShareLink();
  void testButtonSharePhoto();
  void testButtonShareVideo();
  void testReqInviteFriend();
  void testInviteFriends();
  
  virtual void onLogin(bool isLogin, const std::string& msg);
  virtual void onSharedSuccess(const std::string& message);
  virtual void onSharedFailed(const std::string& message);
  virtual void onSharedCancel();
  virtual void onAPI(const std::string& key, const std::string& jsonData);
  virtual void onAPIFailed(const std::string& key, const std::string& msg);
  virtual void onPermission(bool isLogin, const std::string& msg);
  virtual void onFetchFriends(bool ok, const std::string& msg);
  virtual void onRequestInvitableFriends( const h102::FBInvitableFriendsInfo& friends );
  virtual void onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg );
  virtual void onInviteFriendsResult( bool result, const std::string& msg );
  
  virtual void onGetUserInfo( const h102::FBGraphUser& userInfo );
};

#endif /* TestFacebookX_hpp */
