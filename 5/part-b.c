#include <stdio.h>
#include <stdlib.h>
#include "../lib/utils.h"

#define DEBUG 1

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

// Sort the fresh_ids array
int compare_ranges(const void *a, const void *b) {
    // 1. Cast the generic void pointers to your struct type
    const struct FreshRange *range_a = (const struct FreshRange *)a;
    const struct FreshRange *range_b = (const struct FreshRange *)b;

    // 2. Compare the 'start' values
    if (range_a->start < range_b->start) return -1;
    if (range_a->start > range_b->start) return 1;
    
    // If starts are equal, optionally sort by end
    if (range_a->end < range_b->end) return -1;
    if (range_a->end > range_b->end) return 1;

    return 0;
}

int main(void)
{
    FILE *file_ptr = fopen("test.input","r");
    //FILE *file_ptr = fopen("part-a.input","r");
    char line_buffer[128];
    enum Stage stage = RANGES; 
    //long long fresh_ids[1000000]; // fresh products
    struct FreshRange fresh_ids[10000]; // array of structs
    int fresh_ids_count = 0;
    long long available_ids[1000000]; // available products
    int available_ids_count = 0;
    long long int_a;
    long long int_b;
    long long available = 0;

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
            }
        }
    }
    printf("finished processing ids\n");

    // Sort array of fresh ids
    qsort(fresh_ids, fresh_ids_count, sizeof(struct FreshRange), compare_ranges);

    // Loop over fresh ids and then loop over all fresh ids going forward only
    // find any overlaps and remove from self
    // i.e. adjust start or end to remove overlap
    // 2-6 / 4-12 / 16-18
    // 2-4 / 1-2 / 16-18

    for (int i = 0; i < fresh_ids_count; i++) {

        printf("==== checking range: %lld - %lld\n", fresh_ids[i].start, fresh_ids[i].end);
        
        for (int i2 = i+1; i2 < fresh_ids_count; i2++) {
            if (
                fresh_ids[i].end >= fresh_ids[i2].start 
                && fresh_ids[i].start <= fresh_ids[i2].start
            ) {
                if (DEBUG) printf("adjust end of id: %lld to %lld\n", fresh_ids[i].end, fresh_ids[i2].start - 1);
                fresh_ids[i].end = fresh_ids[i2].start - 1;
            }

            if (
                fresh_ids[i].start <= fresh_ids[i2].end 
                && fresh_ids[i].end >= fresh_ids[i2].end 
            ) {
                if (DEBUG) printf("adjust start of id: %lld to %lld\n", fresh_ids[i].start, fresh_ids[i2].end + 1);
                fresh_ids[i].start = fresh_ids[i2].end + 1;
            }

        }
    }
    // TODO: do we need to remove duplicate ranges

    // Now add up all fresh ranges
    for (int i = 0; i < fresh_ids_count; i++) {
        printf("==== checking range: %lld - %lld\n", fresh_ids[i].start, fresh_ids[i].end);
        printf("adding: %lld\n", (fresh_ids[i].end - fresh_ids[i].start + 1));
        available += (fresh_ids[i].end - fresh_ids[i].start) + 1; // inclusive
    }


    printf("Number of ingredients available: %lld\n", available);
}
