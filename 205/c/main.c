#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** 判断两个字符串是否同构 */
bool isIsomorphic(char* s, char* t) {   
    int len = strlen(s);
    if (len != strlen(t)) return false;

    // mapTo表示s中的某种字符替换到t之后的字符
    // mapFrom表示t中的某种字符替换到s之后字符
    int mapTo[256], mapFrom[256];
    // 初始化为-1
    int i = -1;
    while (++i < 256) mapTo[i] = mapFrom[i] = -1;

    i = 0;
    char from, to;
    while (i < len) {
        from = *(s + i);
        to = *(t + i);
        // 如果两个字符都没有做过替换
        if (mapTo[from] == -1 && mapFrom[to] == -1) { 
            mapTo[from] = to;  // 替换并记录两个字符的映射
            mapFrom[to] = from;
        } else {
            // 如果两个字符中有一个做过映射，且与当前映射情况不符，返回false
            if (mapTo[from] != -1 && mapTo[from] != to)
                return false;
            if (mapFrom[to] != -1 && mapFrom[to] != from)
                return false;
        }
        ++i;
    }

    return true;
}

void test(char* s, char* t) {
    printf("s = %s,\nt = %s,\n", s, t);
    if (isIsomorphic(s, t)) printf("they are isomorphic.\n");
    else printf("they are not isomorphic.\n");
}

int main() {
    test("egg", "add");
    test("foo", "bar");
    test("paper", "title");
    test("a", "a");
    test("ab", "ab");
    test("13", "42");
    return 0;
}
