//
// Created by 林伟茂 on 2020/4/3.
//

#include "com_lwm_javacallc_JNITest.h"
#include <string.h>

//2. 包含日志头文件, 定义日志输出函数
#include <android/log.h>

#define LOG_TAG "System.out"

//第一个参数为日志的等级，第二个参数为 TAG：标志，第三个参数为__VA_ARGS__：可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

/*
 *  JNIEnv *env中的 env相当于 结构体的二级结构体指针
 *  把一个 jstring 转换成一个c语言的char* 类型
 */
char *_JString2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode);// String.getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}

/*
  jint：返回值
  Java_全类名_方法名
  JNIEnv * env
*/
jint Java_com_lwm_javacallc_JNITest_add
        (JNIEnv *env, jobject jobj, jint ji, jint jj) {
    int result = ji + jj;
    // 打印日志
    LOGD("result=%d\n", result);
    return result;
};


// 从 Java 传入字符串，C 代码进行拼接
// java ： I am from Java
// C    :  add I am from C
// return : I am from Java add I am from C
// JNIEnv *env中的 env相当于 结构体的二级结构体指针

JNIEXPORT jstring JNICALL Java_com_lwm_javacallc_JNITest_sayHello
        (JNIEnv *env, jobject jobj, jstring jstr) {

    // Java传递的为 jstring 要转化为 char 类型
    char *fromJava = _JString2CStr(env, jstr);   // I am from Java add I am from C
    // C：
    char *fromc = "add I am from C";
    // 拼接函数 strcat
    strcat(fromJava, fromc);// 这个方法会把拼接的结果放在第一个参数里面(此时为char类型)

    // 拼接完成的结果为char类型，因此还要转换成 jstring类型
    //     jstring     (*NewStringUTF)(JNIEnv*, const char*);
    LOGD("fromJava=%s\n", fromJava);
    return (*env)->NewStringUTF(env, fromJava);
};

/*
 * JNIEnv *env中的 env相当于 结构体的二级结构体指针
 * 给每个元素加上 10
 */
JNIEXPORT jintArray JNICALL Java_com_lwm_javacallc_JNITest_increaseArrayEles
        (JNIEnv *env, jobject jobj, jintArray jarray) {

    //1.得到数组的长度(调用 GetArrayLength 这个方法就可以得到)
    //  jsize       (*GetArrayLength)(JNIEnv*, jarray);
    int size = (*env)->GetArrayLength(env, jarray);

    //2.得到数组元素
    //   jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
    // JNI_FALSE：就在 jarray 传递过来的这个空间里面操作
    jint *intArray = (*env)->GetIntArrayElements(env, jarray, JNI_FALSE);

    //3.遍历数组，给每个元素加上10
    int i;
    for (i = 0; i < size; ++i) {
        //*(intArray+i) = *(intArray+i) + 10;
        *(intArray + i) += 10;
    }

    //4.返回结果
    return jarray;
};

// JNIEnv *env中的 env相当于 结构体的二级结构体指针
JNIEXPORT jint JNICALL Java_com_lwm_javacallc_JNITest_checkPwd
        (JNIEnv *env, jobject jobj, jstring jstr) {

    // 假设服务器的密码是123456
    char *origin = "123456";

    //_JString2CStr把 jstring 转化成 char指针类型
    char *fromUser = _JString2CStr(env, jstr);

    // 函数比较字符串是否相同
    // extern int    strcmp(const char *, const char *);
    int code = strcmp(origin, fromUser);
    LOGD("code=%d\n", code);
    // code 等于 0 密码就相同返回 200
    if (code == 0) {
        return 200;
    } else {
        return 400;
    }
};