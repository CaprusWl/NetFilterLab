//
// Created by bytedance on 2020/12/2.
//

#include "FilterConvertor.h"

#include <stdlib.h>

FilterPtr convertStrToFilter(char* str) {
    FilterPtr filterPtr = (FilterPtr) malloc(sizeof(struct Filter));
    // todo: convert String to Filter
    return filterPtr;
}

char* convertFilterToString(FilterPtr filterPtr) {
    char *filterStr = (char *) malloc(sizeof(char) * 100);
    // todo: convert String to Filter
    return filterStr;
}
