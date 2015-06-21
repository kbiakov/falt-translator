#include "trans.h"

using namespace std;

unsigned int maxStrs = 100;
size_t defLen = 80;


progCpp :: progCpp() {
    fileSource = new char*[maxStrs];
    for (int i = 0; i < maxStrs; i++) {
        fileSource[i] = new char[defLen];
    }
}

progCpp :: ~progCpp() {
    for (int i = 0; i < maxStrs; i++) {
        delete[] fileSource[i];
    }
    delete[] fileSource;
}

void progCpp::open(char *name) {
    ifstream progOpen;
    progOpen.open(name);

    int i = 0;
    while (progOpen.getline(fileSource[i], defLen) && i < maxStrs) i++;
    linesCount = i;
}

void progCpp::save(char *name) const {
    ofstream saveProg;
    saveProg.open(name);

    for (int i = 0; i < linesCount; i++) {
        saveProg.write(fileSource[i], strlen(fileSource[i]));
    }
}

void progCpp::transInt(unsigned int n) {
    strncpy(fileSource[n], "int", 3);
    strcat(fileSource[n], ";\n");
    puts(fileSource[n]);
}

void progCpp::transFloat(unsigned int n) {
    putSpaces(fileSource[n], 3, 2);
    strncpy(fileSource[n], "float", 5);
    strcat(fileSource[n], ";\n");
    puts(fileSource[n]);
}

void progCpp::transBeg(unsigned int n, bool first) {
    if (first) {
        putSpaces(fileSource[n], 1, 14);
        strncpy(fileSource[n], "void progCpp() { ", 17);
    } else {
        strncpy(fileSource[n], "{", 3);
    }

    strcat(fileSource[n], "\n");
    puts(fileSource[n]);
}

void progCpp::transEnd(unsigned int n) {
    strncpy(fileSource[n], "}", 3);
    strcat(fileSource[n], "\n");
    puts(fileSource[n]);
}

void progCpp::transIf(unsigned int n) {
    strncpy(fileSource[n], "if (", 4);
    *strstr(fileSource[n], "òî") = NULL;
    strcat(fileSource[n], ")\n");
    puts(fileSource[n]);
}

void progCpp::transWhile(unsigned int n) {
    putSpaces(fileSource[n], 4, 2);
    strncpy(fileSource[n], "while (", 7);
    *strstr(fileSource[n], " òî") = NULL;
    strcat(fileSource[n], ") do\n");
    puts(fileSource[n]);
}

void progCpp::transAssign(unsigned int n) {
    strcat(fileSource[n], ";\n");
    puts(fileSource[n]);
}

bool progCpp::isCorrCods(unsigned int n) const {
    char *abc = "0123456789abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/!=<>&|";

    /*
    unsigned int lBrk = 0, rBrk = 0;

    for (int i = 0; i < strlen(fileSource[n]); i++) {
        if (fileSource[n][i] == ' ') {
            // ... ?
        } else if (fileSource[n][i] == '(') {
            ++lBrk;
        } else if (fileSource[n][i] == ')') }
            ++rBrk;
        } else {
            bool findSym = 0;
            for (int j = 0; j < strlen(abc) && !findSym; j++) {
                if (fileSource[n][i] == abc[j]) {
                    findSym = 1;
                }
            }
            if (!findSym) return 0;
        }
    }

    if (lBrk != rBrk) return 0;
    */

    return 1;
}

bool progCpp::isCorrAsns(unsigned int n) const {
    char abc[] = "0123456789abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/";

    /*
    unsigned int lBrk = 0, rBrk = 0;

    for (int i = 0; i < strlen(fileSource[n]); i++) {
        if (fileSource[n][i] == ' ') {
            // ... ?
        } else if (fileSource[n][i] == '(') {
            ++lBrk;
        } else if (fileSource[n][i] == ')') {
            ++rBrk;
        } else {
            bool findSym = 0;
            for (int j = 0; j < strlen(abc) && !findSym; j++) {
                if (fileSource[n][i] == abc[j]) {
                    findSym = 1;
                }
            }
            if (!findSym) return 0;
        }
    }

    if (lBrk != rBrk) return 0;
    */

    return 1;
}

void progCpp::translate() {
    try {
        char *tmpStr;
        char *altStr, *altStr1;
        size_t tmp, tmp1;

        unsigned int targetStr;
        unsigned begNums, endNums;

        // search & translate declaration of int and float variables with name checking
        begNums = endNums = 0;
        for (targetStr = 0; targetStr < linesCount; targetStr++) {
            // translate all assignments, declarations and conditions are ignored
            if (strstr(fileSource[targetStr], "=") != NULL && isCorrAsns(targetStr)
                    && !strstr(fileSource[targetStr], "öåë")
                    && !strstr(fileSource[targetStr], "âåù")
                    && !strstr(fileSource[targetStr], "åñëè")
                    && !strstr(fileSource[targetStr], "ïîêà")) {
                        transAssign(targetStr);
            }

            // translate declarations and perhaps definitions of int variables
            if (tmpStr = strstr(fileSource[targetStr], "öåë")) {
                tmp = fileSource[targetStr] - tmpStr;
                if (tmp == NULL) {
                    transInt(targetStr);
                } else throw std::logic_error("Error! Invalid variable declaration.");
            }

            // translate declarations and perhaps definitions of float variables
            if (tmpStr = strstr(fileSource[targetStr], "âåù")) {
                tmp = fileSource[targetStr] - tmpStr;
                if (tmp == NULL) {
                    transFloat(targetStr);
                } else throw std::logic_error("Error! Invalid variable declaration.");
            }

            // translate begin keywords
            if (tmpStr = strstr(fileSource[targetStr], "íà÷")) {
                if (tmp == 0 && strlen(fileSource[targetStr]) == 3) {
                    ++begNums;
                    transBeg(targetStr, begNums == 1);
                } else throw std::logic_error("Error! Invalid begin keyword state.");
            }

            // translate end keywords
            if (tmpStr = strstr(fileSource[targetStr], "êîí")) {
                if (tmp == 0 && strlen(fileSource[targetStr]) == 3) {
                    ++endNums;
                    transEnd(targetStr);
                } else throw std::logic_error("Error! Invalid end keyword state.");
            }

            // validate condition operators
            if (tmpStr = strstr(fileSource[targetStr], "åñëè")) {
                tmp = fileSource[targetStr] - tmpStr;
                tmpStr = strstr(fileSource[targetStr], "òî");
                if (tmpStr == NULL) {
                    throw std::logic_error("Error! Invalid condition construction.");
                } else if (tmp == 0) {
                    // if (isCorrCods(altStr)) {
                        transIf(targetStr);
                    // } else throw std::logic_error("Error! Invalid condition construction.");
                } else throw std::logic_error("Error! Invalid condition construction.");
            }

            // validate loop operators
            if (tmpStr = strstr(fileSource[targetStr], "ïîêà")) {
                tmp = fileSource[targetStr] - tmpStr;
                tmpStr = strstr(fileSource[targetStr], "òî");

                if (tmpStr == NULL) {
                    throw std::logic_error("Error! Invalid loop construction.");
                } else if (tmp == 0) {
                    // if (isCorrCods(altStr)) {
                        transWhile(targetStr);
                    // } else throw std::logic_error("Error! Invalid loop construction.");
                } else throw std::logic_error("Error! Invalid loop construction.");
            }
        }

        // check counts of begin/end keywords
        if (begNums != endNums) {
            throw std::logic_error("Error! Counts of begin/end keywords doesn't match.");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}


progPas::progPas() {
    fileSource = new char*[maxStrs];
    for (int i = 0; i < maxStrs; i++) {
        fileSource[i] = new char[defLen];
    }
}

progPas::~progPas() {
    for (int i = 0; i < maxStrs; i++) {
        delete[] fileSource[i];
    }
    delete[] fileSource;
}

void progPas::open(char *name) {
    ifstream progOpen;
    progOpen.open(name);

    int i = 0;
    while (progOpen.getline(fileSource[i], defLen) && i < maxStrs) i++;
    linesCount = i;
}

void progPas::save(char *name) const {
    ofstream saveProg;
    saveProg.open(name);

    saveProg.write("program progPas;\n", strlen("program progPas;\n"));
    for (int i = 0; i < linesCount; i++) {
        saveProg.write(fileSource[i], strlen(fileSource[i]));
    }
}

void progPas::transInt(unsigned int n, char* moveBuffer) {
    strncpy(fileSource[n], "var", 3);
    char* tmpStr = strstr(fileSource[n], "=");

    if (tmpStr) {
        *(tmpStr - 1) = ':';
        strcat(moveBuffer, tmpStr - 2);
        *(tmpStr - 1) = NULL;
        strcat(moveBuffer, ";\n");
    }

    strcat(fileSource[n], ": Integer;\n");
    puts(fileSource[n]);
}

void progPas::transFloat(unsigned int n, char* moveBuffer) {
    strncpy(fileSource[n], "var", 3);
    char* tmpStr = strstr(fileSource[n], "=");

    if (tmpStr) {
        *(tmpStr-1) = ':';
        strcat(moveBuffer,tmpStr-2);
        *(tmpStr-1) = NULL;
        strcat(moveBuffer,";\n");
    }

    strcat(fileSource[n], ": Real;\n");
    puts(fileSource[n]);
}

void progPas::transBeg(unsigned int n, bool* firstBegin, char* moveBuffer) {
    strncpy(fileSource[n], "begin\n", 7);

    if (*firstBegin) {
        strcat(fileSource[n], moveBuffer);
    }

    *firstBegin = false;
    puts(fileSource[n]);
}

void progPas::transEnd(unsigned int n, bool last) {
    strncpy(fileSource[n], "end", 3);

    if (last) {
        strcat(fileSource[n], ".\n");
    } else {
        strcat(fileSource[n], ";\n");
    }

    puts(fileSource[n]);
}

void progPas::transIf(unsigned int n) {
    strncpy(fileSource[n], "if  ", 4);
    *strstr(fileSource[n], "òî") = NULL;
    strcat(fileSource[n], "then\n");
    puts(fileSource[n]);
}

void progPas::transWhile(unsigned int n) {
    putSpaces(fileSource[n], 4, 2);
    strncpy(fileSource[n], "while ", 6);
    *strstr(fileSource[n], "òî") = NULL;
    strcat(fileSource[n], " do\n");
    puts(fileSource[n]);
}

void progPas::transAssign(unsigned int n, bool firstBegin, char* moveBuffer) {
    *(strstr(fileSource[n], "=") - 1) = ':';
    strcat(fileSource[n], ";\n");

    if (firstBegin) {
        strcat(moveBuffer, fileSource[n]);
        fileSource[n][0] = 0;
    }

    puts(fileSource[n]);
}

bool progPas::isCorrCods(unsigned int n) const {
    char *abc = "0123456789abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/!=<>&|";
    unsigned int lBrk = 0, rBrk = 0;

    for (int i = 0; i < strlen(fileSource[n]); i++) {
        if (fileSource[n][i] == ' ') {
            // ... ?
        } else if (fileSource[n][i] == '(') {
            ++lBrk;
        } else if (fileSource[n][i] == ')') {
            ++rBrk;
        } else {
            bool findSym = 0;
            for (int j = 0; j < strlen(abc) && !findSym; j++) {
                if (fileSource[n][i] == abc[j]) {
                    findSym = 1;
                }
            }
            if (!findSym) return 0;
        }
    }

    if (lBrk != rBrk) return 0;

    return 1;
}

bool progPas::isCorrAsns(unsigned int n) const {
    char abc[] = "0123456789abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/";

    /*
    unsigned int lBrk = 0, rBrk = 0;
    
    for (int i = 0; i < strlen(fileSource[n]); i++) {
        if (fileSource[n][i] == ' ') {
            // ... ?
        } else if (fileSource[n][i] == '(') {
            ++lBrk;
        } else if (fileSource[n][i] == ')') {
            ++rBrk;
        } else {
            bool findSym = 0;
            for (int j = 0; j < strlen(abc) && !findSym; j++) {
                if (fileSource[n][i] == abc[j]) {
                    findSym = 1;
                }
            }
            if (!findSym) return 0;
        }
    }

    if (lBrk != rBrk) return 0;
    */
    
    return 1;
}

void progPas::translate() {
    try {
        char moveBuffer[80];
        bool firstBegin = true;
        char *tmpStr;
        char *altStr, *altStr1;
        size_t tmp, tmp1;

        unsigned int targetStr;
        unsigned begNums, endNums;

        // search & translate declaration of int and float variables with name checking
        begNums = endNums = 0;
        moveBuffer[0] = 0;
        for (targetStr = 0; targetStr < linesCount; ++targetStr) {
            // translate all assignments, declarations and conditions are ignored
            if (strstr(fileSource[targetStr], "=") != NULL && isCorrAsns(targetStr)
                    && !strstr(fileSource[targetStr], "öåë")
                    && !strstr(fileSource[targetStr], "âåù")
                    && !strstr(fileSource[targetStr], "åñëè")
                    && !strstr(fileSource[targetStr], "ïîêà")) {
                transAssign(targetStr, firstBegin, moveBuffer);
            }

            // translate declarations and perhaps definitions of float variables
            if (tmpStr = strstr(fileSource[targetStr], "öåë")) {
                tmp = fileSource[targetStr] - tmpStr;
                if (tmp == NULL) {
                    transInt(targetStr, moveBuffer);
                } else throw std::logic_error("Error! Invalid variable declaration.");
            }

            // translate declarations and perhaps definitions of float variables
            if (tmpStr = strstr(fileSource[targetStr], "âåù")) {
                tmp = fileSource[targetStr] - tmpStr;
                if (tmp == NULL) {
                    transFloat(targetStr,moveBuffer);
                } else throw std::logic_error("Error! Invalid variable declaration.");
            }
            
            // translate begin keywords
            if (tmpStr = strstr(fileSource[targetStr], "íà÷")) {
                if (tmp == 0 && strlen(fileSource[targetStr]) == 3) {
                    ++begNums;
                    transBeg(targetStr, &firstBegin, moveBuffer);
                } else throw std::logic_error("Error! Invalid begin keyword state.");
            }

            // translate end keywords
            if (tmpStr = strstr(fileSource[targetStr], "êîí")) {
                if (tmp == 0 && strlen(fileSource[targetStr]) == 3) {
                    ++endNums;
                    transEnd(targetStr, targetStr == linesCount-1);
                } else throw std::logic_error("Error! Invalid end keyword state.");
            }

            // validate condition operators
            if (tmpStr = strstr(fileSource[targetStr], "åñëè")) {
                tmp = fileSource[targetStr] - tmpStr;
                tmpStr = strstr(fileSource[targetStr], "òî");
                if (tmpStr == NULL) {
                    throw std::logic_error("Error! Invalid condition construction.");
                } else if (tmp == 0) {
                    // if (isCorrCods(altStr)) {
                        transIf(targetStr);
                    // } else throw std::logic_error("Error! Invalid condition construction.");
                } else throw std::logic_error("Error! Invalid condition construction.");
            }

            // validate loop operators
            if (tmpStr = strstr(fileSource[targetStr], "ïîêà")) {
                tmp = fileSource[targetStr] - tmpStr;
                tmpStr = strstr(fileSource[targetStr], "òî");
                if (tmpStr == NULL) {
                    throw std::logic_error("Error! Invalid loop construction.");
                } else if (tmp == 0) {
                    // if (isCorrCods(altStr)) {
                        transWhile(targetStr);
                    // } else throw std::logic_error("Error! Invalid loop construction.");
                } else throw std::logic_error("Error! Invalid loop construction.");
            }
        }

        // check counts of begin/end keywords
        if (begNums != endNums) {
            throw std::logic_error("Error! Counts of begin/end keywords doesn't match.");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}


/*
void substring(char *v, char *str, size_t n, size_t m) {
    char *alt1, *alt2;
    int i, len;

    len = n + m;
    strncpy(alt1, str, len);

    len = strlen(alt1);
    for (i = 0; i < len; ++i) {
        alt2[len - i] = alt1[i];
    }
    strncpy(alt1, alt2, len - n);
    alt1[len - n] = '\0';

    len = strlen(alt1);
    for (i = 0; i < len; ++i) {
        alt2[len - i] = alt1[i];
    }

    v = alt2;
    
    /*
    int i,j;
    for (i=0, j=n-1; j<n-1+m; ++i, ++j)
    	v[i] = str[j];
    v[i] = '\0';
    *
}
*/

/*
bool isCorrect(char *str) {
    char *nums = "0123456789";
    char *abcs = "abcdefghijklmnopqrstuvwyxz";
    char *ABCs = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    unsigned int i, j, left, right;
    left = right = 0;
    for (i = 0; str[i] == ' ' || i < strlen(str); i++) {
        ++left;
    }

    if (left == strlen(str) - 1) return 0;
    for (i = strlen(str) - 1; str[i] == ' ' || i >= 0; i--) {
        ++right;
    }

    bool corr = 1;
    for (i = left; i <= right && corr; ++i) {
        bool inSet = 0;
        for (j = 0; j < strlen(nums) && !inSet; j++) {
            if (str[i] == nums[j]) {
                inSet = 1;
            }
        }
        for (j = 0; j < strlen(nums) && !inSet; j++) {
            if (str[i] == abcs[j] || str[i] == ABCs[j]) {
                inSet = 1;
            }
        }
        if (!inSet) corr = 0;
    }

    return corr;
}
*/

void putSpaces(char *str, unsigned int pos, unsigned int num) {
    int int i, len = strlen(str);

    for (i = 0; i < num; i++) {
        strcat(str, " ");
    }

    for (i = len + num - 1; i >= pos; i--) {
        str[i] = str[i - num];
    }

    for (i = pos; i <= num; i++) {
        str[i] = ' ';
    }
}
