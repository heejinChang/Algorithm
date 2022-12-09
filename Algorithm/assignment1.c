#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int open_file(char* file, int h1[], int m1[], int h2[], int m2[], char* s) {
    int i = 0;
    int n;
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        printf("file cannot open\n");
        exit(0);
    }
    else
    {
        fscanf(fp, "%d", &n);
        if (0 <= n && n < 100) {
            for (i = 1; i <= n; i++) {
                fscanf(fp, "%d:%d %d:%d %[^\n]", &h1[i], &m1[i], &h2[i], &m2[i], s);
            }
            h2[0] = 10, m2[0] = 0, h1[i] = 18, m1[i] = 0;
        }
        fclose(fp);
        return n;
    }
   
}

int calc_time(int n, int h1[], int m1[], int h2[], int m2[], int tot_hour[], int calc_hour[], int calc_min[]) {
    int high = -1000; // variable to save the longest nap time 
    int index = 0; 
    int j;
    if (n == 0) { // schedule 0
        index = -1;
    }
    else { // schedule more than 0
        if (h1[n] - h2[n - 1] == 0 && h1[n + 1] - h2[n] == 0) {
            index = -2;
        }
        for (j = 0; j <= n; j++) {
            tot_hour[j] = (h1[j + 1] * 60 + m1[j + 1]) - (h2[j] * 60 + m2[j]);
            if (high < tot_hour[j]) { // determine which tot_hour is the longest time to sleep
                high = tot_hour[j];
                index = j;
            }
            // calculate time (hour and min to represent time as hh:mm)
            calc_hour[j] = tot_hour[j] / 60;
            calc_min[j] = tot_hour[j] % 60;
        }
    }
    return index;
}

void print_time(int i, int n, int index, int h2[], int m2[], int calc_hour[], int calc_min[]) {
    char file[20];

    sprintf(file, "Output_%d.txt", i);
    FILE* fp = fopen(file, "w");
    if (fp == NULL) {
        exit(1);
    }
    else {
        if (index == -1) {
            printf("%02d:%02d\n08:00\n", h2[n], m2[n]);
            fprintf(fp, "%02d:%02d\n08:00\n", h2[n], m2[n]);

        }
        else if (index == -2) { // when schedule is 1 , that schedule starting time is 10:00 and end time is 18:00
            printf("%02d:%02d\n00:00\n", h2[n - 1], m2[n - 1]);
            fprintf(fp, "%02d:%02d\n00:00\n", h2[n - 1], m2[n - 1]);
        }
        else {
            printf("%02d:%02d\n%02d:%02d\n", h2[index], m2[index], calc_hour[index], calc_min[index]);
            fprintf(fp, "%02d:%02d\n%02d:%02d\n", h2[index], m2[index], calc_hour[index], calc_min[index]);
        }
        fclose(fp);
    }
}

int main() {
    for (int i = 1; i < 9; i++) {
        int hour1[100] = { 0, }, min1[100] = { 0, }, hour2[100] = { 0, }, min2[100] = { 0, }, calc_hour[100] = { 0, }, calc_min[100] = { 0, }, tot_hour[15] = { 0, };
        char s[256], file[20];
        int index, n;

        sprintf(file, "Input_%d.txt", i);
        printf("%s\n", file);
        n = open_file(file, hour1, min1, hour2, min2, s);
        index = calc_time(n, hour1, min1, hour2, min2, tot_hour, calc_hour, calc_min);
        print_time(i, n, index, hour2, min2, calc_hour, calc_min);
    }
    return 0;
}
