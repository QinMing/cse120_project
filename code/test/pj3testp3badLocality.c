#include "syscall.h"

#define NumPhysPages    32
int array[50] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49 };

int arrayA[50][50];

unsigned int seed;

void
irand_init()
{
	seed = 931753752;
}

/* a very poor random number generator */
unsigned int
irand(int l, int h)
{
	unsigned int a = 1588635695, m = 429496U, q = 2, r = 1117695901;
	unsigned int val;

	seed = a*(seed % q) - r*(seed / q);
	val = (seed / m) % (h - l) + l;

	return val;
}

main()
{
	int sum;
	int i;
	int j;
	sum = 0;


	for (i = 0; i < 50; i++){
		for (j = 0; j < 50; j++){
			arrayA[i][j] = array[j];
		}
	}

	int k;
	int rand1;
	int rand2;
	irand_init();

	for (k = 0; k < 900; k++){			//in total 180 000 references
		for (i = 0; i < 50; i++){
				rand1 = irand(0, 50);	//random number 0-49,to guarantee the comparison
				rand2 = irand(0, 50);	//random number 0-49,to guarantee the comparison
				sum += arrayA[i][1];	// choose element 1 and 35 to make sure they are on different pages, since every page is 128 contenting 32 integers
				sum += arrayA[i][35];	
				sum += arrayA[1][1];	//frequently referenced element
				sum += arrayA[40][40];	//frequently referenced element
		}
	}

	Exit(sum);
}
