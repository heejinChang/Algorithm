#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct ELEPHANT {
	//ELEPHANT struct to save elephant's weight, iq, index 
	int weight;
	int iq;
	int idx;
}elephant;

elephant list[1000];
int seq[1000];
int back[1000];
int num = 0; // Variable to store how many elephants there are in one file

char* input[5] = {
	"Input_1.txt", "Input_2.txt", "Input_3.txt", "Input_4.txt", "Input_5.txt"
};

char* output[5] = {
	"Output_1.txt", "Output_2.txt", "Output_3.txt", "Output_4.txt", "Output_5.txt"
};

void file_read(int i) {
	FILE* fp = NULL;
	int j = 0;

	fp = fopen(input[i], "r");

	if (fp == NULL) {
		printf("file cannot open\n");
		exit();
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &list[j].weight, &list[j].iq);
		j++; num++;
	}

	for (int i = 0; i < num - 1; i++) {
		list[i].idx = i + 1; // elephant's index starting at 1
	}
}

// Function to sort the elephants
// Sort by weight firstly, secondarily by iq if the weight is the same
void sorting_elephant() {
	elephant temp;
	int i, j;
	// sort by weight first
	for (i = 1; i < num - 1; i++) {
		temp = list[i];
		for (j = i - 1; j >= 0 && temp.weight < list[j].weight; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = temp;
	}

	// If the weight is the same, sort by iq secondarily

	for (int i = 0; i < num - 1; i++)
	{
		for (int j = i + 1; j < num - 1; j++)
		{
			if (list[i].weight == list[j].weight)
			{
				if (list[i].iq > list[j].iq)
				{
					temp = list[i];
					list[i] = list[j];
					list[j] = temp;
				}
			}
		}
	}
/*
*	// print sorting result 
	for (int i = 0; i < num - 1; i++) {
		printf("%d : ", i);
		printf("%d %d %d\n", list[i].weight, list[i].iq, list[i].idx);
	}

*/
}


void print(FILE* fp, int index)
{ // print result 
	if (back[index] != -1) {
		print(fp, back[index]);
		printf("%d ", list[index].idx);
		fprintf(fp, "%d ", list[index].idx);
	}
	else {
		printf("%d ", list[index].idx);
		fprintf(fp, "%d ", list[index].idx);
	}
}

void file_write(int i, int len, int index) {
	// print result in file 
	FILE* fp = NULL;
	fp = fopen(output[i], "w");
	// print result lenght
	printf("%d\n", len); //print the length of elephant sequence found
	fprintf(fp, "%d\n", len);

	print(fp, index);
	printf("\n");
	fclose(fp);

}

void sequence(int i) {
	for (int i = 0; i < num; i++) {
		//initilaize
		seq[i] = 1; back[i] = -1;

		for (int j = 0; j <= i - 1; j++) {
			if ((list[j].iq > list[i].iq) && (list[j].weight < list[i].weight) && (seq[j] + 1 > seq[i])) {
				seq[i] = seq[j] + 1; // Stores the number of elements that meet the condition in the list in front.
				back[i] = j;
			}
		}
	}
	int len = -1;
	int max_idx = 0;

	// find which index is max index 
	for (int i = 0; i < num; i++) {
		if (len < seq[i]) {
			len = seq[i];
			max_idx = i;
		}
	}
	file_write(i, len, max_idx);
}


int main() {
	for (int i = 0; i <= 4; i++) {
		file_read(i);
		sorting_elephant();
		sequence(i);
		num = 0; // reset num variable 
		printf("\n");
	}

	return 0;
}
