#include <stdio.h>
#pragma warning(disable 4996)

int list[100] = { 0, };
int count = 0;

void output(int i) {
	char file[15];
	sprintf(file, "Output_%d.txt", i);
	FILE* fp = fopen(file, "w");
	if (fp == NULL) {
		printf("file cannot open.\n");
		exit();
	}
	else {
		// Print as many as the number stored in the list
		for (int i = 0; i < count; i++) {
			fprintf(fp, "%d\n", list[i]);
			printf("%d\n", list[i]);
		}
		printf("\n");
		fclose(fp);
	}
}

int calc_money(int i, int num, int money[]) {
	int each_money = 0, tot = 0, remainder = 0, extra = 0;
	// each_money -> Amount to be paid by each person when all amounts are divided by the number of people
	// tot -> variable to store the total amount
	// remainder -> each person's money minus each_money, if remainder is negative, the person who paid the least has to pay extra (extra)
	for (int i = 0; i < num; i++) {
		tot += money[i];
	}

	if (num != 0)
		each_money = tot / num;

	for (int i = 0; i < num; i++) {
		remainder = money[i] - each_money;
		if (remainder < 0) {
			remainder = -(remainder);
			extra += remainder;
		}
	}
	list[count] = extra;
	count++;

}

void file_read(int i, char file[]) {
	FILE* fp = fopen(file, "r");
	int num = 0;
	int money = 0;
	int extra_money = 0;

	if (fp == NULL) {
		printf("file cannot open.\n");
		exit();
	}
	else {
		int each_money[100] = { 0, }; // no more than 100 students
		while (!feof(fp)) {
			fscanf(fp, "%d", &num);
			if (num != 0) {
				for (int i = 0; i < num; i++) {
					fscanf(fp, "%d", &each_money[i]);

					if (each_money[i] > 100000) {
						printf("no student spent more than 100,000");
						exit();
					}
				}
				calc_money(i, num, each_money);
			}
		}
		fclose(fp);
	}
}


int main() {
	for (int i = 1; i <= 5; i++) {
		char file[15];
		sprintf(file, "Input_%d.txt", i);
		file_read(i, file);
		output(i);
		count = 0;
	}
}