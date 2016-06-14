/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.javascript;

import com.facebook.Profile;
import com.facebook.ProfileTracker;
import com.hub102.facebookx.FacebookX;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Intent;
import android.os.Bundle;
import com.facebook.AccessTokenTracker;
import com.facebook.AccessToken;

public class AppActivity extends Cocos2dxActivity {
    @Override
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        FacebookX.getCallbackManager().onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FacebookX.init(this);
        AccessTokenTracker fxAccessTokenTracker = FacebookX.getAccessTokenTracker();
        fxAccessTokenTracker = new AccessTokenTracker() {
            @Override
            protected void onCurrentAccessTokenChanged(AccessToken oldAccessToken, AccessToken currentAccessToken) {
                updateWithToken(currentAccessToken);
            }
        };
        ProfileTracker fxProfileTracker = FacebookX.getProfileTracker();
        fxProfileTracker = new ProfileTracker() {
            @Override
            protected void onCurrentProfileChanged(Profile oldProfile, Profile currentProfile) {
                if (currentProfile != null) {
                    JSONObject userInfo = new JSONObject();
                    try {
                        userInfo.put("id", currentProfile.getId());
                        userInfo.put("name", currentProfile.getName());
                        userInfo.put("first_name", currentProfile.getFirstName());
                        userInfo.put("last_name", currentProfile.getLastName());
                        userInfo.put("middle_name", currentProfile.getMiddleName());
                        userInfo.put("link_uri", currentProfile.getLinkUri());
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    FacebookX.onGetUserInfoWrapper(userInfo.toString());
                }
            }
        };
        updateWithToken(AccessToken.getCurrentAccessToken());
    }

    @Override
    protected void onDestroy() {
        FacebookX.getAccessTokenTracker().stopTracking();
        super.onDestroy();
    }

    private void updateWithToken(AccessToken currentAccessToken) {
        if (currentAccessToken != null) {
            FacebookX.setLoggedIn(true);
        } else {
            FacebookX.setLoggedIn(false);
        }
    }
}