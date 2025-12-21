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
    //FILE *file_ptr = fopen("test.input","r");
    FILE *file_ptr = fopen("part-a.input","r");
    char line_buffer[128];
    enum Stage stage = RANGES; 
    struct FreshRange fresh_ids[10000]; // array of structs
    int fresh_ids_count = 0;
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
    // when the next range is deemed to be overlapping then we will set
    // current end to the end of that range
    long long current_start = fresh_ids[0].start;
    long long current_end = fresh_ids[0].end;

    for (int i = 1; i < fresh_ids_count; i++) {
        printf("==== current range: %lld - %lld\n", fresh_ids[i].start, fresh_ids[i].end);
        printf("  -- current start/end: %lld - %lld\n", current_start, current_end);
        printf("  -- next range: %lld - %lld\n", fresh_ids[i].start, fresh_ids[i].end);

        if (current_end >= fresh_ids[i].start && fresh_ids[i].end > current_end) {
            printf("    -- overlap detected\n");
            current_end = fresh_ids[i].end;
        } else {
            // Catch any where the range sites inside current start and end
            if (fresh_ids[i].start >= current_start && fresh_ids[i].end <= current_end) {
                printf("ignored range\n");
            } else {
                printf("    --  ranges do not overlap, adding to total: %lld\n", (current_end - current_start) + 1); 
                available += (current_end - current_start) + 1; // inclusive
                current_start = fresh_ids[i].start;
                current_end = fresh_ids[i].end;
            }
        }
    }

    // Gotcha, remember to add the last range
    available += (current_end - current_start) + 1; // inclusive

    printf("Number of ingredients available: %lld\n", available);
}
