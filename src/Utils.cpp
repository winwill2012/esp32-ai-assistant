#include "utils.h"

String generateTaskId() {
    String uuid = "";
    const char *charset = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        uuid += charset[random(16)];
    }
    return uuid;
}
