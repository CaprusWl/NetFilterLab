//
// Created by bytedance on 2020/12/2.
//

#include "../include/FilterConvertor.h"

FilterPtr convertStrToFilter(char* str) {
    FilterPtr filterPtr = (FilterPtr) kmalloc(sizeof(struct Filter), GFP_USER);
    // todo: convert String to Filter
    return filterPtr;
}

char* convertFilterToString(FilterPtr filterPtr) {
    char *filterStr = (char *) kmalloc(sizeof(char) * 100, GFP_USER);
    // todo: convert String to Filter
    return filterStr;
}
