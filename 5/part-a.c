#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"

#define DEBUG 0

enum Stage {
    RANGES,
    IDS
};

struct FreshRange {
    long long start;
    long long end;
};

// Return 2 ints
void parse_range(const char *buffer, long *a, long *b) {
    sscanf(buffer, "%i-%i", &a, &b);
}

int main(void)
{
    //FILE *file_ptr = fopen("test.input","r");
    FILE *file_ptr = fopen("part-a.input","r");
    char line_buffer[128];
    enum Stage stage = RANGES; 
    //long long fresh_ids[1000000]; // fresh products
    struct FreshRange fresh_ids[10000]; // array of structs
    int fresh_ids_count = 0;
    long long available_ids[1000000]; // available products
    int available_ids_count = 0;
    long long int_a;
    long long int_b;
    int available = 0;

    while(fgets(line_buffer, 128, file_ptr)) {
        // Loop until we hit a blank line
        if (line_buffer[0] == '\n') {
            stage = IDS;
        } else {
            if (stage == RANGES) {
                if (DEBUG) printf("fresh range: %s\n", line_buffer);
                sscanf(line_buffer, "%lld-%lld", &int_a, &int_b);
                if (DEBUG) printf("a: %lld / b: %lld\n", int_a, int_b);
                fresh_ids[fresh_ids_count].start = int_a;
                fresh_ids[fresh_ids_count].end   = int_b;
                fresh_ids_count++;
            } else {
                //if (DEBUG) printf("available id: %s", line_buffer);
                sscanf(line_buffer, "%lld", &int_a);
                if (!int_array_contains(available_ids, available_ids_count, int_a)) {
                    available_ids[available_ids_count++] = int_a;
                }
            }
        }
    }
    printf("finished processing ids");

    // Now check how many of the ingredient ids are fresh
    for (int i = 0; i < available_ids_count; i++) {
        if (DEBUG) printf("checking if ingredient is fresh: %lld\n", available_ids[i]);
        
        for (int i2 = 0; i2 < fresh_ids_count; i2++) {
            if (DEBUG) printf("is %lld between %lld and %lld", available_ids[i], fresh_ids[i2].start, fresh_ids[i2].end);
            if (
                available_ids[i] >= fresh_ids[i2].start 
                && available_ids[i] <= fresh_ids[i2].end
            ) {
                if (DEBUG) printf("found fresh ingredient\n");
                available++;
                break;
            }
        }
    }

    printf("Number of ingredients available: %i\n", available);
}
