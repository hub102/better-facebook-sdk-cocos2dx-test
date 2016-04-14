//
//  jsb_h102_testFacebookX.cpp
//  FacebookXTest
//
//  Created by Thuy Dong Xuan on 4/12/16.
//
//

#include "jsb_h102_testFacebookX.hpp"
#include "cocos2d_specifics.hpp"

#include "TestFacebookX.hpp"


static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  args.rval().setBoolean(true);
  return true;
}

JSClass  *jsb_h102_testFacebookX_class;
JSObject *jsb_h102_testFacebookX_prototype;

bool js_h102_testFacebookX_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  bool ok = true;
  TestFacebookX* cobj = new (std::nothrow) TestFacebookX();
  
  TypeTest<TestFacebookX> t;
  js_type_class_t *typeClass = nullptr;
  std::string typeName = t.s_name();
  auto typeMapIter = _js_global_type_map.find(typeName);
  CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
  typeClass = typeMapIter->second;
  CCASSERT(typeClass, "The value is null.");
  // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
  JS::RootedObject proto(cx, typeClass->proto.get());
  JS::RootedObject parent(cx, typeClass->parentProto.get());
  JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
  args.rval().set(OBJECT_TO_JSVAL(obj));
  // link the native object with the javascript object
  js_proxy_t* p = jsb_new_proxy(cobj, obj);
  AddNamedObjectRoot(cx, &p->obj, "TestFacebookX");
  if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
    ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
  return true;
}

bool js_h102_testFacebookX_testButtonLogin(JSContext *cx, uint32_t argc, jsval *vp)
{
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testButtonLogin();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testButtonLogin : wrong number of arguments");
  return false;
}

bool js_h102_testFacebookX_testButtonLogout(JSContext *cx, uint32_t argc, jsval *vp)
{
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testButtonLogout();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testButtonLogout : wrong number of arguments");
  return false;
}

bool js_h102_testFacebookX_testButtonShareLink(JSContext *cx, uint32_t argc, jsval *vp)
{
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testButtonShareLink();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testButtonShareLink : wrong number of arguments");
  return false;
}

bool js_h102_testFacebookX_testButtonSharePhoto(JSContext *cx, uint32_t argc, jsval *vp)
{
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testButtonSharePhoto();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testButtonSharePhoto : wrong number of arguments");
  return false;
}

bool js_h102_testFacebookX_testButtonShareVideo(JSContext *cx, uint32_t argc, jsval *vp)
{
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testButtonShareVideo();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testButtonShareVideo : wrong number of arguments");
  return false;
}

bool js_h102_testFacebookX_testReqInviteFriend(JSContext *cx, uint32_t argc, jsval *vp) {
  do {
    if (argc == 0) {
      TestFacebookX::getInstance()->testReqInviteFriend();
      return true;
    }
  } while(0);
  
  JS_ReportError(cx, "js_h102_testFacebookX_testReqInviteFriend : wrong number of arguments");
  return false;
}

void js_h102_Utils_finalize(JSFreeOp *fop, JSObject *obj) {
  CCLOGINFO("jsbindings: finalizing JS object %p (H102::Utils)", obj);
}

void js_register_h102_testFacebookX(JSContext *cx, JS::HandleObject global) {
  jsb_h102_testFacebookX_class = (JSClass *)calloc(1, sizeof(JSClass));
  jsb_h102_testFacebookX_class->name = "testFacebookX";
  jsb_h102_testFacebookX_class->addProperty = JS_PropertyStub;
  jsb_h102_testFacebookX_class->delProperty = JS_DeletePropertyStub;
  jsb_h102_testFacebookX_class->getProperty = JS_PropertyStub;
  jsb_h102_testFacebookX_class->setProperty = JS_StrictPropertyStub;
  jsb_h102_testFacebookX_class->enumerate = JS_EnumerateStub;
  jsb_h102_testFacebookX_class->resolve = JS_ResolveStub;
  jsb_h102_testFacebookX_class->convert = JS_ConvertStub;
  jsb_h102_testFacebookX_class->finalize = js_h102_Utils_finalize;
  jsb_h102_testFacebookX_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
  
  static JSPropertySpec properties[] = {
    JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_PS_END
  };
  
  static JSFunctionSpec funcs[] = {
    JS_FS_END
  };
  
  static JSFunctionSpec st_funcs[] = {
    JS_FN("testButtonLogin", js_h102_testFacebookX_testButtonLogin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FN("testButtonLogout", js_h102_testFacebookX_testButtonLogout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FN("testButtonShareLink", js_h102_testFacebookX_testButtonShareLink, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FN("testButtonSharePhoto", js_h102_testFacebookX_testButtonSharePhoto, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FN("testButtonShareVideo", js_h102_testFacebookX_testButtonShareVideo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FN("testReqInviteFriend", js_h102_testFacebookX_testReqInviteFriend, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
    JS_FS_END
  };
  
  jsb_h102_testFacebookX_prototype = JS_InitClass(
                                          cx, global,
                                          JS::NullPtr(),
                                          jsb_h102_testFacebookX_class,
                                          js_h102_testFacebookX_constructor, 0, // constructor
                                          properties,
                                          funcs,
                                          NULL, // no static properties
                                          st_funcs);
  
  // make the class enumerable in the registered namespace
  //  bool found;
  //FIXME: Removed in Firefox v27
  //  JS_SetPropertyAttributes(cx, global, "LWFBitmap", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
  
  // add the proto and JSClass to the type->js info hash table
  TypeTest<TestFacebookX> t;
  js_type_class_t *p;
  std::string typeName = t.s_name();
  if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
  {
    p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
    p->jsclass = jsb_h102_testFacebookX_class;
    p->proto = jsb_h102_testFacebookX_prototype;
    p->parentProto = NULL;
    _js_global_type_map.insert(std::make_pair(typeName, p));
  }
}

void register_all_h102(JSContext* cx, JS::HandleObject obj) {
  // Get the ns
  JS::RootedObject ns(cx);
  get_or_create_js_obj(cx, obj, "h102", &ns);
  
  js_register_h102_testFacebookX(cx, ns);
}
