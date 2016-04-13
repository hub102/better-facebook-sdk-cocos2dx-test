
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    _login: false,
    _btn: null,
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
                    h102.testFacebookX.testButtonLogin();
                    self._btnLogin.setTitleText("LOGOUT");
                } else {
                    h102.testFacebookX.testButtonLogout();
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
            h102.testFacebookX.testButtonShareLink();
        });
        this.addChild(btnShareLink);

        var btnSharePhoto = new ccui.Button();
        btnSharePhoto.x = size.width/2;
        btnSharePhoto.y = size.height - 150;
        btnSharePhoto.setTitleText("SHARE PHOTO");
        btnSharePhoto.setTitleFontSize(20);
        btnSharePhoto.addClickEventListener(function() {
            h102.testFacebookX.testButtonSharePhoto();
        });
        this.addChild(btnSharePhoto);

        var btnShareVideo = new ccui.Button();
        btnShareVideo.x = size.width/2;
        btnShareVideo.y = size.height - 200;
        btnShareVideo.setTitleText("SHARE VIDEO");
        btnShareVideo.setTitleFontSize(20);
        btnShareVideo.addClickEventListener(function() {
            h102.testFacebookX.testButtonShareVideo();
        });
        this.addChild(btnShareVideo);

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

