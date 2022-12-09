#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int output[30] = { 0, };
int idx = 0; // output array's index 
int num = 0; // num of pancakes

// check_overlap function that avoids swapping digits when there are multiple occurrences of the same number
int check_overlap(int pancakes[], int size) {
    int temp;
    int i = 0;
    int same = 0;

    if (pancakes[i] == pancakes[i + 1]) {
        same = 1;
    }

    return same;
}

//void flip function that turns the pancake over based on the received n
void flip(int pancakes[], int n) {
    int result[100] = { 0, };
    int same = 0;
    int sub[100];

    for (int i = 0; i < num - n + 1; i++) {
        sub[i] = pancakes[i];
    }

    if (num - n + 1 == 2) {
        same = check_overlap(sub, num - n + 1);
    }

    for (int i = 0; i < num - n + 1; i++) {
        //Inserting the pancakes array from the opposite side
        result[i] = pancakes[num - i - n];
    }
    for (int i = 0; i < num - n + 1; i++) {
        pancakes[i] = result[i];
    }

    // to save which index was fliped
    if (same == 1 && (num - n + 1) == 2) {
        ;
    }
    else {
        output[idx] = n; idx++;
    }
}

// pancakes sorting to use flip function 
void pancake_stacking(int pancakes[], int n) {

    for (int i = n; i > 0; i--) {
        int max = 0, max_idx = 0;

        if (i == 1) {
            output[idx] = 0;
        }
        else {
            for (int j = 0; j < i; j++) {
                // find max number's index 
                if (pancakes[j] >= max) {
                    max = pancakes[j];
                    max_idx = j;
                }
            }
            if (max_idx == 0) { // When the first value in the array is the largest
                flip(pancakes, n - i + 1);
            }
            else if (max_idx != i - 1) {
                flip(pancakes, n - max_idx);
                flip(pancakes, n - i + 1);
            }
        }
    }
}

//print sorting pancakes result and flip output index
void printPancakes(int pancakes[], int pancakes1[], int n, int i) { // print result into output_txt
    char file[15];
    sprintf(file, "Output_%d.txt", i);
    FILE* fp = fopen(file, "a");

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", pancakes1[i]);
        printf("%d ", pancakes1[i]);
    }

    fprintf(fp, "( ");
    printf("( ");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", pancakes[i]);
        printf("%d ", pancakes[i]);
    }
    fprintf(fp, ")");
    printf(")");

    // print flip index result (end : 0)
    for (int k = 0; k <= idx; k++) {
        fprintf(fp, "%d ", output[k]);
        printf("%d ", output[k]);
    }
    fprintf(fp, "\n");
    printf("\n");

    fclose(fp);
}

void file_open(int i) {
    char file[15];
    sprintf(file, "Input_%d.txt", i);

    FILE* fp = fopen(file, "r");
    char input[100];
    char* str = NULL;

    while (!feof(fp)) {

        if (fgets(input, 100, fp) == NULL) break;

        char* str = NULL;
        char* temp = strtok_s(input, " ", &str); //Trim string based on whitespace
        int pancakes[30] = { 0, }; // to save integer 
        int pancakes1[30] = { 0, };


        while (temp != NULL) { //repeat until not null
            pancakes[num] = atoi(temp);
            pancakes1[num] = atoi(temp);
            temp = strtok_s(NULL, " ", &str);	//Retruncate based on null character
            num++;
        }
        pancake_stacking(pancakes, num);
        printPancakes(pancakes, pancakes1, num, i);

        num = 0;
        idx = 0;
    }
    printf("\n");
    fclose(fp);
}

int main() {

    for (int i = 1; i <= 5; i++) {
        file_open(i);
    }
    return 0;
}
