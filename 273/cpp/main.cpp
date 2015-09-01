#include <iostream>

using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        string units[] = {"", "Thousand", "Million", "Billion"};
        string numbers[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        string tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        string word = "";
        int level = 0;
        while (num) {
            word = threeBitsNumberToWords(num % 1000, units[level++], numbers, tens) + " " + word;
            num /= 1000;
        }
        word = removeDuplicateSpaces(word);
        if (word == "") return "Zero";
        else return word;
    }
private:
    string threeBitsNumberToWords(int num, string unit, string numbers[], string tens[]) {
        if (num == 0) return "";
        string words = "";
        if (num / 100) words += numbers[num / 100] + " Hundred ";
        num %= 100;
        if (num < 20) words += numbers[num];
        else {
            words += tens[num / 10] + " ";
            words += numbers[num %= 10];
        }
        if (unit == "") return words;
        else return words + " " + unit;
    }

    string removeDuplicateSpaces(string& word) {
        if (word == "") return word;
        string ret = "";
        ret += word[0];
        char last = word[0];
        int len = word.size();
        for (int i = 1; i < len; ++i) {
            if (last == ' ' && word[i] == ' ') continue;
            ret += word[i];
            last = word[i];
        }
        if (ret[0] == ' ') ret = ret.substr(1);
        if (ret[ret.size() - 1] == ' ') ret = ret.substr(0, ret.size() - 1);
        return ret;
    }

};

void test(int num) {
    Solution s;
    cout << num << " : " << s.numberToWords(num) << endl;
}

int main() {
    for (int i = 0; i <= 100; ++i)
        test(i);
    test(123);
    test(123000);
    test(1000010);
    return 0;
}
