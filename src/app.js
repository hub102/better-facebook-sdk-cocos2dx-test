var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    _login: false,
    _btnLogin: null,
    _btnInvite: null,
    _friends: null,

    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        var data = jsb.fileUtils.getDataFromFile(res.hoodsters);
        var desPath = jsb.fileUtils.getWritablePath() + "hoodsters.png";

        jsb.fileUtils.writeDataToFile(data, desPath);

        var self = this;
        var btnLogin = new ccui.Button();
        btnLogin.x = size.width/2;
        btnLogin.y = size.height - 50;
        btnLogin.setTitleFontSize(20);
        this._btnLogin = btnLogin;
        this._login = h102.facebookX.isLoggedIn();
        cc.log("first test login = " + this._login);
        btnLogin.setTitleText(this._login ? "LOGOUT" : "LOGIN");

        btnLogin.addClickEventListener(
            function() {
                cc.log("JS login: Pre-check accessToken = " + h102.facebookX.getAccessToken());
                if (!self._login) {
                    cc.log("js test: login");
                    h102.facebookX.login();
                } else {
                    cc.log("js test: logout");
                    h102.facebookX.logout();
                    self._login = false;
                    self._btnLogin.setTitleText("LOGIN");
                }
            }
        );
        this.addChild(btnLogin, 2);

        var btnShareLink = new ccui.Button();
        btnShareLink.x = size.width/2;
        btnShareLink.y = size.height - 100;
        btnShareLink.setTitleText("SHARE LINK");
        btnShareLink.setTitleFontSize(20);
        btnShareLink.addClickEventListener(function() {
            cc.log("js: share link");
            var info = {
                'type': "link",
                'text': "Test description tiếng Việt có dấu",
                'title': "Test title tiếng Việt có dấu",
                'link': "https://hub102.com"
            };
            h102.facebookX.share(info);
        });
        this.addChild(btnShareLink);

        var btnSharePhoto = new ccui.Button();
        btnSharePhoto.x = size.width/2;
        btnSharePhoto.y = size.height - 150;
        btnSharePhoto.setTitleText("SHARE PHOTO");
        btnSharePhoto.setTitleFontSize(20);
        btnSharePhoto.addClickEventListener(function() {
            cc.log("js: share photo");
            var info = {
                'type': "photo",
                'text': "Test description tiếng Việt có dấu",
                'title': "Test title tiếng Việt có dấu",
                'media': jsb.fileUtils.getWritablePath() + "hoodsters.png"
            };
            h102.facebookX.share(info);
        });
        this.addChild(btnSharePhoto);

        var btnShareStory = new ccui.Button();
        btnShareStory.x = size.width/2;
        btnShareStory.y = size.height - 200;
        btnShareStory.setTitleText("SHARE OPEN GRAPH STORY");
        btnShareStory.setTitleFontSize(20);
        btnShareStory.addClickEventListener(function() {
            var info = {
                'type': "better_fbx:person",
                'title': "Tôi đã vượt qua một người bạn",
                'description': "Điểm số: 10000",
                'image': "https://fbcdn-photos-h-a.akamaihd.net/hphotos-ak-xfp1/t39.2081-0/p128x128/10333106_1693250547571713_1233636624_n.png",
                'url': "https://apps.facebook.com/joselitopuzzle_test/"
            }

            h102.facebookX.shareOpenGraphStory(info, "better_fbx:beat", "person");
        });
        this.addChild(btnShareStory);

        var btnReqInviteFriend = new ccui.Button();
        btnReqInviteFriend.x = size.width/2;
        btnReqInviteFriend.y = size.height - 250;
        btnReqInviteFriend.setTitleText("REQUEST INVITE FRIENDS");
        btnReqInviteFriend.setTitleFontSize(20);
        btnReqInviteFriend.addClickEventListener(function() {
            cc.log("js: request friend to invite");
            var params = {
                'ResponseFields': "id,name,picture,email,first_name,last_name,installed"
            };
            h102.facebookX.requestInvitableFriends(params);
        });
        this.addChild(btnReqInviteFriend);

        var btnInviteFriend = new ccui.Button();
        btnInviteFriend.x = size.width/2;
        btnInviteFriend.y = size.height - 300;
        btnInviteFriend.setTitleText("INVITE FRIENDS");
        btnInviteFriend.setTitleFontSize(20);
        var self = this;
        btnInviteFriend.addClickEventListener(function() {
            cc.log("js: invite friends");
            h102.facebookX.inviteFriendsWithInviteIds(self._friends, "BetterX", "This is a test invitation");
        });
        this.addChild(btnInviteFriend);
        btnInviteFriend.setEnabled(false);
        this._btnInvite = btnInviteFriend;
        this._btnInvite.setOpacity(127);

        h102.facebookX.setListener({
            'onLogin': this.onLogin.bind(this),
            'onSharedSuccess': this.onSharedSuccess.bind(this),
            'onSharedFailed': this.onSharedFailed.bind(this),
            'onSharedCancel': this.onSharedCancel.bind(this),
            'onAPI': this.onAPI.bind(this),
            'onRequestInvitableFriends': this.onRequestInvitableFriends.bind(this),
            'onInviteFriendsWithInviteIdsResult': this.onInviteFriendsWithInviteIdsResult.bind(this),
            'onGetUserInfo': this.onGetUserInfo.bind(this)
        });

        return true;
    },

    onLogin: function(isLogin, msg) {
        if (isLogin) {
            cc.log("access token = " + h102.facebookX.getAccessToken());
            this._login = true;
            this._btnLogin.setTitleText("LOGOUT");
            
            // cc.log("user ID = " + h102.facebookX.getUserID());
            // cc.log("user Name = " + h102.facebookX.getName());
            h102.facebookX.api("/me/friends", "test_friends");
        } else {
            cc.log("Login failed: " + msg);
        }
    },

    onSharedSuccess: function(msg) {
        cc.log("onSharedSuccess: " + msg);
    },

    onSharedFailed: function(msg) {
        cc.log("onSharedFailed: " + msg);
    },

    onSharedCancel: function() {
        cc.log("onSharedCancel");
    },

    onAPI: function(key, data) {
        cc.log("onAPI");
        cc.log("key = " + key);
        if (key == "test_friends") {
            cc.log("data = " + data);
        }
    },

    onRequestInvitableFriends: function(friends) {
        cc.log("onRequestInvitableFriends:");
        cc.log(JSON.stringify(friends));
        if (!friends) {
            cc.log("no invitable friend");
            return;
        }
        this._friends = [];
        for (var i = 0; i < friends["data"].length; i++) {
            this._friends.push(friends["data"][i]["id"]);
        }
        cc.log("Invitable number = " + this._friends.length);

        if (this._friends.length > 0) {
            this._btnInvite.setEnabled(true);
            this._btnInvite.setOpacity(255);
        }
    },

    onInviteFriendsWithInviteIdsResult: function(result, msg) {
        cc.log("onInviteFriendsWithInviteIdsResult");
        cc.log("result = " + result);
        cc.log("msg = " + msg);
    },

    onGetUserInfo: function(info) {
        cc.log("onGetUserInfo: " + JSON.stringify(info));
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});