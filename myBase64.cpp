#include "myBase64.h"
#include <cstring>
#include <iostream>
#include <algorithm>

using std::find;
using std::memset;

char myBase64::DC[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/'
};

char myBase64::digit2Char(int n) {
    return DC[n];
}

int myBase64::char2Digit(char c) {
    if (c == '=')
        return 0;
    return find(DC, DC + 64, c) - DC;
}

string myBase64::encode(const string & str) {
    // a & 0xFC >> 2
    // a & 0x03 << 4 + b & 0xF0 >> 4
    // b & 0x0F << 2 + c & 0xC0 >> 6
    // c & 0x3F

    unsigned len = str.size();
    unsigned tmpLen = (len / 3 + (len % 3 > 0)) * 3;
    char * tmpStr = new char[tmpLen];
    memset(tmpStr, 0, tmpLen);
    for (int i = 0; i < len; ++i)
        tmpStr[i] = str[i];

    string result;
    uint8_t * unit = (uint8_t*)tmpStr;
    unsigned cnt = tmpLen / 3;

    for (int i = 0; i < cnt; ++i, unit += 3) {
        result += digit2Char((unit[0] & 0xFC) >> 2);
        result += digit2Char(((unit[0] & 0x03) << 4) + ((unit[1] & 0xF0) >> 4));
        result += digit2Char(((unit[1] & 0x0F) << 2) + ((unit[2] & 0xC0) >> 6));
        result += digit2Char(unit[2] & 0x3F);
    }

    uint8_t amountMissing = (len % 3 == 0) ? 0 : 3 - len % 3;
    for (uint8_t i = 0; i < amountMissing; ++i)
        result[result.size() - 1 - i] = '=';

    delete [] tmpStr;
    return result;
}

string myBase64::decode(const string & str) {
    // a = (A << 2) + ((B & 0x30) >> 4);
    // b = ((B & 0x0F) << 4) + ((C & 0x3C) >> 2)
    // c = ((C & 0x03) << 6) + (D & 0x3F)

    string result;
    const char * s = str.c_str();
    unsigned len = str.size();
    for (int i = 0; i < len; i += 4, s += 4) {
        int A, B, C, D;
        A = char2Digit(s[0]), B = char2Digit(s[1]);
        C = char2Digit(s[2]), D = char2Digit(s[3]);

        result += (A << 2) + ((B & 0x30) >> 4);
        result += ((B & 0x0F) << 4) + ((C & 0x3C) >> 2);
        result += ((C & 0x03) << 6) + (D & 0x3F);
    }

    if (str[len - 2] == '=') {
        result = result.substr(0, result.size() - 2);
    } else if (str[len - 1] == '=') {
        result = result.substr(0, result.size() - 1);
    }

    return result;
}