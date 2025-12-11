#include <stdio.h>
#include <string.h>

#define DEBUG 1
#define MAX_NEIGHBOURS 3

struct Cell {
    int r;
    int c;
    int value;
};

int is_removable(int arr[512][512], int rows, int cols, int row, int col){
    if (DEBUG) printf(" = calculate cell: %i, %i\n", row, col);
    struct Cell cells[8];
    int cells_size = 0;
    int rolls_nearby = 0;

    for (int r = row-1; r <= row+1; r++) {
        for (int c = col-1; c <= col+1; c++) {
            if (r >= 0 && r < rows) {
                if (c >= 0 && c < cols) {
                    if (r != row || c != col) { // exclude self
                        //printf("  - valid cell: %i, %i\n", r, c); 
                        cells[cells_size].r = r;
                        cells[cells_size].c = c;
                        cells[cells_size].value = arr[r][c];
                        if (arr[r][c] == 1) {
                            printf("  - removable roll: %i, %i\n", r, c); 
                            rolls_nearby++;
                        }
                        cells_size++;
                    }
                }
            }
        }
    }

    if (rolls_nearby <= MAX_NEIGHBOURS) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    FILE *file_ptr = fopen("part-a.input","r");
    char line_buffer[512]; // hold lines read
    char compare_buffer[2]; // holds single chars for comparison
    int row = 0;
    int arr[512][512]; 
    int rows = 0;
    int cols = 0;
    int removable = 0;
    
    // Initialise the array
    while (fgets(line_buffer, 511, file_ptr)) {
        if (DEBUG) printf("current line: %s", line_buffer);
        // Loop over cols
        for (int col = 0; col < strlen(line_buffer) - 1; col++) {
            printf("\n");
            //if (DEBUG) printf("col %c\n", line_buffer[col]);
            compare_buffer[0] = line_buffer[col];
            if (strcmp(compare_buffer, "@") == 0) {
                arr[row][col] = 1; // paper roll
            } else {
                arr[row][col] = 0; // empty
            }
            cols = col+1;
        }
        row += 1;
        rows = row;
    }

    // Calculate rolls that can be removed
    printf("rows: %i / cols: %i\n", rows, cols);

    // Now we loop over array again and decide if the rolls can be removed
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (arr[row][col] == 1) {
                removable += is_removable(arr, rows, cols, row, col);
            }
        }
    }

    printf("removable rolls: %i\n", removable);

    return 0;
}
