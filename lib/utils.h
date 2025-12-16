#include <stdio.h>

/*
 * Returns 1 if found otherwise return 0
 */
int int_array_contains(long long *arr, long long size, long long needle) {
    int i = 0;
    while (i < size) {
        if (arr[i] == needle) {
            return 1;
        }
        i++;
    }
    return 0;
}
