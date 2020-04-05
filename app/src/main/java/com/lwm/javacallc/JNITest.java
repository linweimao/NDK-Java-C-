package com.lwm.javacallc;

/**
 * @Author: 林伟茂
 * @Version: 1.0
 * 作用：Java 调用 C 代码
 */
public class JNITest {

    static {
        System.loadLibrary("javacallc");
    }

    // 让 C代码做加法运算，把结果返回
    public native int add(int x, int y);

    // 从 Java 传入字符串，C 代码进行拼接
    // 例如：传入 I am from Java
    // 返回 I am from Java add I am from C（add I am from C在C加上）
    public native String sayHello(String s);

    // 让 C 代码给每个元素都加上 10
    public native int[] increaseArrayEles(int[] intArray);

    /*

     * 应用: 检查密码是否正确, 如果正确返回200, 否则返回400

     */

    public native int checkPwd(String pwd);

}
