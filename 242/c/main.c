#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isAnagram(char* s, char* t) {
    int lenS = strlen(s), lenT = strlen(t), i;   
    if (lenS != lenT) return false;
    int nums[26];
    for (i = 0; i < 26; ++i)
        nums[i] = 0; 
    for (i = 0; i < lenS; ++i)
        ++nums[*(s + i) - 'a'];
    
    for (i = 0; i < lenS; ++i)
        --nums[*(t + i) - 'a'];
    for (i = 0; i < 26; ++i)
        if (nums[i] != 0) return false;
    return true;
}

void test(char* s, char* t) {
    printf("s = %s, t = %s : ", s, t);
    if (isAnagram(s, t)) 
        printf("t(%s) is an anagram of s(%s).\n", s, t);
    else
        printf("t(%s) is not an anagram of s(%s).\n", s, t);
}

int main() {
    test("anagram", "nagaram");
    test("rat", "cat");
    return 0;
}
