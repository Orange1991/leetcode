#include <stdio.h>

int hIndex(int* citations, int citationsSize) {
    int formmer = 0, latter = citationsSize - 1, center;
    while (formmer <= latter) {
        center = (formmer + latter) / 2;
	if (citationsSize - center == citations[center]) 
	    return citations[center];
	else if (citationsSize - center < citations[center])
	    latter = center - 1;
	else
	    formmer = center + 1;
    }

    return citationsSize - formmer;
}

int main() {
    int count[] = {0, 1, 3, 5, 6};
    printf("%d\n", hIndex(count, 5));
    int count2[] = {0, 1};
    printf("%d\n", hIndex(count2, 2));
    int count3[] = {0, 10, 13, 15, 16};
    printf("%d\n", hIndex(count3, 5));
    int count4[] = {100};
    printf("%d\n", hIndex(count4, 1));
    printf("%d\n", hIndex(count4, 0));
    int count5[] = {11, 15};
    printf("%d\n", hIndex(count5, 2));
    int count6[] = {0, 0, 4, 4};
    printf("%d\n", hIndex(count6, 4));
    int count7[] = {1, 4, 7, 9};
    printf("%d\n", hIndex(count7, 4));
    return 0;
}
