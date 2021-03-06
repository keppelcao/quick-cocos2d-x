
#include "native/CCNative.h"
#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include <stdlib.h>
#include <android/log.h>

using namespace cocos2d;

NS_CC_EXTRA_BEGIN

//  activity indicator

void CCNative::showActivityIndicator(void)
{
    CCLOG("CCNative::showActivityIndicator() - not support this platform.");
}

void CCNative::hideActivityIndicator(void)
{
    CCLOG("CCNative::hideActivityIndicator() - not support this platform.");
}


//  alert view

void CCNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "createAlert", 
        "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
		jstring jtitle = methodInfo.env->NewStringUTF(title);
		jstring jmessage = methodInfo.env->NewStringUTF(message);
		jstring jcancelButtonTitle = methodInfo.env->NewStringUTF(cancelButtonTitle);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jtitle, jmessage, jcancelButtonTitle);
		methodInfo.env->DeleteLocalRef(jtitle);
		methodInfo.env->DeleteLocalRef(jmessage);
		methodInfo.env->DeleteLocalRef(jcancelButtonTitle);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

int CCNative::addAlertButton(const char* buttonTitle)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "addAlertButton", 
        "(Ljava/lang/String;)I"))
    {
		jstring jbuttonTitle = methodInfo.env->NewStringUTF(buttonTitle);
        jint ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, jbuttonTitle);
		methodInfo.env->DeleteLocalRef(jbuttonTitle);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		
		return ret;
    }
	return 0;
}

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
	return addAlertButton(buttonTitle);
}
#endif

void CCNative::showAlert(CCAlertViewDelegate* delegate)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "showAlert", 
        "()V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCNative::showAlertLua(LUA_FUNCTION listener)
{
    CCLOG("CCNative::showAlertLua(LUA_FUNCTION listener)) - not support this platform.");
}
#endif

void CCNative::cancelAlert(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "cancelAlert", 
        "()V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}


//  misc

void CCNative::openURL(const char* url)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "openURL", 
        "(Ljava/lang/String;)V"))
    {
		jstring jurl = methodInfo.env->NewStringUTF(url);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jurl);
		methodInfo.env->DeleteLocalRef(jurl);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

const string CCNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    CCLOG("CCNative::getInputText() - not support this platform.");
    return string("");
}


//  OpenUDID

const string CCNative::getOpenUDID(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "getOpenUDID", 
        "()Ljava/lang/String;"))
    {
        jstring judid = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
		char* udid = (char*)methodInfo.env->GetStringUTFChars(judid, 0);
		string ret = udid;
		methodInfo.env->ReleaseStringUTFChars(judid, udid);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return string("");
}

const string CCNative::getDeviceName(void)
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "getDeviceName", 
        "()Ljava/lang/String;"))
    {
        jstring jdevice = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
		char* device = (char*)methodInfo.env->GetStringUTFChars(jdevice, 0);
		string ret = device;
		methodInfo.env->ReleaseStringUTFChars(jdevice, device);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return ret;
    }
    return string("");
}

void CCNative::vibrate()
{
	JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/utils/PSNative", "vibrate", 
        "(L)V"))
    {
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (jlong)200);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

NS_CC_EXTRA_END
