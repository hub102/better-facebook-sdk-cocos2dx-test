//
//  jsb_h102_testFacebookX.hpp
//  FacebookXTest
//
//  Created by Thuy Dong Xuan on 4/12/16.
//
//

#include "base/ccConfig.h"
#ifndef jsb_h102_testFacebookX_hpp
#define jsb_h102_testFacebookX_hpp

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_h102_testFacebookX_class;
extern JSObject *jsb_h102_testFacebookX_prototype;

bool js_h102_testFacebookX_constructor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_h102_testFacebookX_testButton(JSContext *cx, uint32_t argc, jsval *vp);

void register_all_h102(JSContext* cx, JS::HandleObject obj);

#endif /* jsb_h102_testFacebookX_hpp */