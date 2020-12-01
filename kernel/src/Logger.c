//
// Created by caprus on 2020/11/16.
//

#include "../include/Logger.h"

#include <linux/kernel.h>

void logi(char* context, char* msg) {
    printk("%s: %s", context, msg);
}

void logd(char* context, char* msg) {
    printk("%s: %s", context, msg);
}

void logw(char* context, char* msg) {
    printk("%s: %s", context, msg);
}

void loge(char* context, char* msg) {
    printk("%s: %s", context, msg);
}
