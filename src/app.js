
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

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(this.sprite, 0);

        var self = this;
        var btn = new ccui.Button(res.CloseNormal_png, res.CloseSelected_png, "");
        btn.x = size.width - 40;
        btn.y = 40;
        btn.scale = 2;
        btn.setTitleText("LOGIN");
        this._btn = btn;

        btn.addClickEventListener(
            function() {
                if (!self._login) {
                    h102.testFacebookX.testButtonLogin();
                    self._btn.setTitleText("LOGOUT");
                } else {
                    h102.testFacebookX.testButtonLogout();
                    self._btn.setTitleText("LOGIN");
                }
                self._login = !self._login;
            }
        );
        this.addChild(btn, 2);

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

