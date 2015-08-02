#include <stdio.h>
#include <string.h>

void reverseWords(char *s) {
    int len = 0, formmer = 0, latter = 0;
    char *tmp = s, tmpChar;
    while (*tmp++ != '\0') ++len;

    /* 字符串逆置 */
    latter = len - 1;
    while (formmer < latter) {
        tmpChar = *(s + formmer);
        *(s + formmer) = *(s + latter);
        *(s + latter) = tmpChar;
        ++formmer;
        --latter;
    }

    /* 单词逆置 */
    formmer = 0;
    int end = 0;
    while (formmer < len) {
        end = formmer;
        while (end < len - 1 && *(s + end + 1) != ' ') ++end;
        latter = end;
        while (formmer < latter) {
            tmpChar = *(s + formmer);
            *(s + formmer) = *(s + latter);
            *(s + latter) = tmpChar;
            ++formmer;
            --latter;
        }
        formmer = end + 2;
    }

    /* 去除空格 */
    formmer = 0;
    latter = 0;
    while (latter < len) {
        while (latter < len && *(s + latter) == ' ') ++latter;
        while (latter < len && *(s + latter) != ' ') 
            *(s + formmer++) = *(s + latter++);
        *(s + formmer++) = ' ';
    }
    *(s + --formmer) = '\0';
    if (*(s + --formmer) == ' ') *(s + formmer) = '\0';
}

int main() {
    char str[] = "the sky is blue";
    printf("%d : ---%s---\n", strlen(str), str);
    reverseWords(str);
    printf("%d : ---%s---\n", strlen(str), str);
    char str2[] = "   the   sky  is   blue  ";
    printf("%d : ---%s---\n", strlen(str2), str2);
    reverseWords(str2);
    printf("%d : ---%s---\n", strlen(str2), str2);

    return 0;
}
