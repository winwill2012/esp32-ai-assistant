#include "utils.h"

String generateUUID() {
    String uuid = "";
    randomSeed(millis()); // 使用模拟引脚 A0 的值作为随机数种子，也可以使用 millis() 等
    for (int i = 0; i < 32; i++) {
        int randomValue = random(0, 16); // 生成 0 到 15 之间的随机数
        if (randomValue < 10) {
            uuid += String(randomValue); // 数字 0-9
        } else {
            uuid += (char) ('a' + (randomValue - 10)); // 字母 a-f
        }
    }
    return uuid;
}