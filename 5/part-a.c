#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"

#define DEBUG 1

enum Stage {
    RANGES,
    IDS
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
    long long fresh_ids[1000000]; // fresh products
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
                printf("a: %lld / b: %lld\n", int_a, int_b);
                while (int_a <= int_b) {
                    if (!int_array_contains(fresh_ids, fresh_ids_count, int_a)) {
                        //printf("%lld\n", int_a);
                        fresh_ids[fresh_ids_count++] = int_a;
                    }
                    int_a++;
                }
                printf("done on range\n");
            } else {
                if (DEBUG) printf("available id: %s", line_buffer);
                if (!int_array_contains(available_ids, available_ids_count, int_a)) {
                    available_ids[available_ids_count++] = int_a;
                }
            }
        }
    }
    printf("finished processing ids");

    // Now check how many of the ingredient ids are fresh
    for (int i = 0; i < available_ids_count; i++) {
        if (int_array_contains(fresh_ids, fresh_ids_count, available_ids[i])) {
            available++;
        }
    }

    printf("Number of ingredients available: %i\n", available);
}
