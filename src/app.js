
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
        btnLogin.setTitleText("LOGIN");
        btnLogin.setTitleFontSize(20);
        this._btnLogin = btnLogin;

        btnLogin.addClickEventListener(
            function() {
                if (!self._login) {
                    h102.facebookX.login();
                    self._btnLogin.setTitleText("LOGOUT");
                } else {
                    h102.facebookX.logout();
                    self._btnLogin.setTitleText("LOGIN");
                }
                self._login = !self._login;
            }
        );
        this.addChild(btnLogin, 2);

        var btnShareLink = new ccui.Button();
        btnShareLink.x = size.width/2;
        btnShareLink.y = size.height - 100;
        btnShareLink.setTitleText("SHARE LINK");
        btnShareLink.setTitleFontSize(20);
        btnShareLink.addClickEventListener(function() {
            var info = {
                'type': "link",
                'text': "Test description",
                'title': "Test title",
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
            var info = {
                'type': "photo",
                'text': "Test description",
                'title': "Test title",
                'media': jsb.fileUtils.getWritablePath() + "hoodsters.png"
            };
            h102.facebookX.share(info);
        });
        this.addChild(btnSharePhoto);

        var btnShareVideo = new ccui.Button();
        btnShareVideo.x = size.width/2;
        btnShareVideo.y = size.height - 200;
        btnShareVideo.setTitleText("SHARE OPEN GRAPH STORY");
        btnShareVideo.setTitleFontSize(20);
        btnShareVideo.addClickEventListener(function() {
            var info = {
                'type': "better_fbx:person",
                'title': "I beat a friend",
                'description': "Score: 10000",
                'image': "https://fbcdn-photos-h-a.akamaihd.net/hphotos-ak-xfp1/t39.2081-0/p128x128/10333106_1693250547571713_1233636624_n.png",
                'url': "https://apps.facebook.com/joselitopuzzle_test/"
            }

            h102.facebookX.shareOpenGraphStory(info, "better_fbx:beat", "person");
        });
        this.addChild(btnShareVideo);

        var btnReqInviteFriend = new ccui.Button();
        btnReqInviteFriend.x = size.width/2;
        btnReqInviteFriend.y = size.height - 250;
        btnReqInviteFriend.setTitleText("REQUEST INVITE FRIENDS");
        btnReqInviteFriend.setTitleFontSize(20);
        btnReqInviteFriend.addClickEventListener(function() {
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
            'onInviteFriendsWWithInviteIdsResult': this.onInviteFriendsWWithInviteIdsResult.bind(this)
        });

        return true;
    },

    onLogin: function(isLogin, msg) {
        cc.log("onLogin");
        cc.log("isLogin = " + isLogin);
        cc.log("msg = " + msg);
        cc.log("access token = " + h102.facebookX.getAccessToken());
        cc.log("user ID = " + h102.facebookX.getUserID());
        h102.facebookX.api("me", "test_me");
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
        if (key == "test_me") {
            cc.log("data = " + data);
        }
    },

    onRequestInvitableFriends: function(friends) {
        cc.log("onRequestInvitableFriends");
        // cc.log("friends = " + JSON.stringify(friends));
        this._friends = [];
        for (var i = 0; i < friends["data"].length; i++) {
            this._friends.push(friends["data"][i]["id"]);
        }

        cc.log("This friends = " + JSON.stringify(this._friends));
        if (this._friends.length > 0) {
            this._btnInvite.setEnabled(true);
            this._btnInvite.setOpacity(255);
        }
    },

    onInviteFriendsWWithInviteIdsResult: function(result, msg) {
        cc.log("onInviteFriendsWWithInviteIdsResult");
        cc.log("result = " + result);
        cc.log("msg = " + msg);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});