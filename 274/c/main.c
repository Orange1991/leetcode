#include <stdio.h>
#include <stdlib.h>

int hIndex(int* citations, int citationsSize) {
    int* count = (int*)malloc(sizeof(int) * (citationsSize + 1));
    memset(count, 0, sizeof(int) * (citationsSize + 1));
    int i;
    for (i = 0; i < citationsSize; ++i) {
        if (citations[i] >= citationsSize)
	    ++count[citationsSize];
	else
	    ++count[citations[i]];
    }

    for (i = citationsSize; i > -1; --i) {
        if (count[i] >= i) 
	    return i;
	else
	    count[i - 1] += count[i];
    }

    return 0;
}

int main() {
    int citations[] = {3, 0, 6, 1, 5};
    printf("%d\n", hIndex(citations, 5));
    return 0;
}
