#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 20

int a[MAX_SIZE];
bool select[MAX_SIZE];
int size;

void print(int index) {
	if (index == size) {
		for (int i = 0; i < size-1; ++i) {
			printf("%d ", a[i]);
		}
		printf("%d\n", a[size-1]);
		return ;
	}
	for (int i = 0; i < size; ++i) {
		if (select[i] == false) {
			select[i] = true;
			a[index] = i+1;
			print(index+1);
			select[i] = false;
		}
	}
}

int main() {
	scanf("%d", &size);
	print(0);
    return 0;
 }
