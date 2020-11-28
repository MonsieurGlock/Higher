#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;
class file {

public:
	int max = 0;
	/*string readLine(string fileName , int line) {
		string str;
		ifstream myfile(fileName);
		while (!myfile.eof()) {

		}
		getline(myfile , str);

		
	}*/
	

	void read(void) {
		//FILE* f = fopen("name.txt", "r");
		//char s[10] = "";
		//int num=0;
		//int line = 0;
		//int temp=0;
		//int count=0;
		////find max
		//int score[10] = {0,0,0,0,0,0,0,0,0,0};

		//while ((fgets(s, 10, f)) != NULL) {
		//	score[count] = atoi(s);
		//	count++;
		//}
		//fclose(f);


		//int n = 10;
		//int i,j;
		//f = fopen("name.txt", "r");
		//int m;

		//for (i = 0; i <= n - 2; i++) {
		//	for (j = 0; j <= n - i; j++) {
		//		if (score[j] > score[j + 1]) {
		//			m = score[j];
		//			score[j] = score[j + 1];
		//			score[j + 1] = m;
		//		}
		//	}
		//}


		//for (i = 0; i < 10; i++) {
		//	printf("%d\n", score[i]);
		//}
		FILE* f = fopen("name.txt", "r");
		char s[10] = "";
		int max=0;
		int num;
		while ((fgets(s, 10, f)) != NULL) {
			num = atoi(s);
			if (num > max) {
				max = num;
			}
		}
		fclose(f);
		int count = 0;
		int score[5] = { 0,0,0,0,0 };
		int i;
		while (max != 0 && count != 5){
			f = fopen("name.txt", "r");
			while ((fgets(s, 10, f)) != NULL) {
				num = atoi(s);
				if (num == max){
					score[count] = num;
					count++;
				}
			}
			fclose(f);
			max--;
		}
		count = 0;
		for (i = 0; i < 5; i++) {
			printf("%d\n", score[i]);
		}

	}





	void write(char m[10],int score) {

		FILE* f = fopen("name.txt", "a");
		fprintf(f, "%d %s\n" ,score ,m);
		fclose(f);

	}

private:
};