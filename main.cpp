#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

unsigned short readFile(string &str){
    ifstream file("C:/Users/abram/pr4ctice/text.txt");
    if (file.is_open()) getline(file, str);
    file.close();
}

unsigned short getInput(string &str) {
    cout << " введите строку или нажмите Enter, чтобы считать строку с файла: ";
    //cin.sync();
    getline(cin, str);
    if (str.empty()) readFile(str);
    return 0;
}

void getAlphabet(string &str, bool withCapital = false, bool withLower = false, bool withNumbers = false){
    if (!withCapital && !withLower && !withNumbers) return;
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string numbers = "0123456789";
    if (withCapital) str += upper;
    if (withLower) str += lower;
    if (withNumbers) str += numbers;
}

int findCharEntrance(char chr, const string &str){
    for (int i = 0; i < str.length(); ++i)
        if (str[i] == chr) return i;
    return -1;
}

void correctTheText(string &str){
    unsigned int len = str.length();
    for (int i = 0; i < len; ++i) {
        if (str[i] != ' ') break;
        str = str.substr(i+1, --len);
    }
    for (int i = 0; i < len; ++i) {
        if (str[i] == ' ' && str[i+1] == ' ') {
            str = str.substr(0, i) + str.substr(i+1, --len);
            --i;
        }
    }
    if (str[len-1] == ' ') str = str.substr(0, len-2);
    for (int i = 0; i < len; ++i) {
        if (findCharEntrance(str[i], ".!?") != -1) {
            if (findCharEntrance(str[i-1], " .?!,([{+-*") != -1) {
                str = str.substr(0, i-1) + str.substr(i, len--);
                i--;
            }
            if (str[i + 1] == ' ') continue;
            if ((str[i] == '!' && str[i+1] == '?') || (str[i] == '?' && str[i+1] == '!')) i++;
            if (str[i] == str[i+1] && str[i+1] == str[i+2]) i += 2;
            for (int j = i+1; findCharEntrance(str[j], ".?!,()[]{}+-*") != -1; ++j)
                str = str.substr(0, j) + str.substr(j + 1, len--);
        }
        if (findCharEntrance(str[i], ",+-*()[]{}") != -1) {
            if (str[i-1] == ' ') {
                str = str.substr(0, i-1) + str.substr(i, len--);
                i--;
            }
            if (findCharEntrance(str[i-1], " .?!,([{+-*") != -1) {
                str = str.substr(0, i) + str.substr(i+1, len--);
                i--;
            }
            if (str[i+1] == ' ' && findCharEntrance(str[i+1], "([{+-*") != -1)
                str = str.substr(0, i-1) + str.substr(i, len--);
            for (int j = i+1; findCharEntrance(str[j], ".?!,()[]{}+-*") != -1; ++j)
                str = str.substr(0, j) + str.substr(j + 1, len--);
        }
    }
    string alphabetLower, alphabetUpper;
    getAlphabet(alphabetLower, false, true, false);
    getAlphabet(alphabetUpper, true, false, false);

    if (findCharEntrance(str[0], alphabetUpper) == -1) str[0] = alphabetUpper[findCharEntrance(str[0], alphabetLower)];
    for (int i = 1; i < len; ++i) {
        if (findCharEntrance(str[i], alphabetUpper) != -1) str[i] = alphabetLower[findCharEntrance(str[i], alphabetUpper)];
        if (findCharEntrance(str[i-2], ".?!") != -1 && findCharEntrance(str[i], alphabetLower) != -1)
            str[i] = alphabetUpper[findCharEntrance(str[i], alphabetLower)];
    }
}

void removePunctMarks(string &str){
    unsigned int len = str.length();
    for (int i = 0; i < len; ++i) {
        if (findCharEntrance(str[i], ".?!,()[]{}/+-'*") != -1) {
            str = str.substr(0, i) + str.substr(i + 1, len--);
            i--;
        }
    }
    string alphabetLower, alphabetUpper;
    getAlphabet(alphabetLower, false, true, false);
    getAlphabet(alphabetUpper, true, false, false);
    for (int i = 0; i < len; ++i) {
        if (findCharEntrance(str[i], alphabetUpper) != -1) {
            str[i] = alphabetLower[findCharEntrance(str[i], alphabetUpper)];
            //i--;
        }
    }
}

unsigned int split(string &str, string words[50]){
    unsigned int len = str.length();
    unsigned short kolvo = 0, pos = 0;
    unsigned short wordLen = 0;
    for (int i = 0; i < len; i++) {
        wordLen++;
        if (str[i] == ' '){
            words[kolvo] = str.substr(pos, wordLen-1);
            kolvo++;
            wordLen = 0;
            pos = i+1;
        }
    }
    return kolvo;
}

void reverse1(string &str, string words[50]){
    unsigned lenMas = split(str, &words[0]);
    for (int i = lenMas-1; i >= 0; i--) cout << words[i] << " ";
    cout << "\n";
}

void reverse2(string &str, string words[50]){
    unsigned lenMas = split(str, &words[0]);
    for (int i = 0; i < lenMas; i++){
        unsigned lenWord = words[i].length();
        for (int j = lenWord-1; j >= 0; j--){
            cout << words[i][j];
        }
        cout << " ";
    }
    cout << "\n";
}

void reverse3(string &str, string words[50]){
    unsigned lenMas = split(str, &words[0]);
    for (int i = lenMas-1; i >= 0; i--){
        unsigned lenWord = words[i].length();
        for (int j = lenWord-1; j >= 0; j--){
            cout << words[i][j];
        }
        cout << " ";
    }
    cout << "\n";
}

void howManyLetters(string &str, string words[50]){
    unsigned lenMas = split(str, &words[0]);
    for (int word = 0; word < lenMas; word++){
        cout << "в слове " << words[word] << " ";
        int cnt = 0;
        for (int letter = 0; words[word].size() / sizeof(words[word][0]) > letter; letter++){
            cnt++;
        }
        switch(cnt){
            case 1: {
                cout << cnt << " буква" << "\n";
            }break;
            case 2:
            case 3:
            case 4: {
                cout << cnt << " буквы" << "\n";
            }break;
            default: {
                cout << cnt << " букв" << "\n";
            }break;
        }
    }
}

//void isIdenticalLetters(string &str, string words[50]){
//    unsigned lenMas = split(str, &words[0]);
//    unsigned lenCurrWord, lenNextWord;
//    for (int current = 0; current < lenMas; current++){
//        for (int next = 1 + current; next < lenMas; next++){
//            lenCurrWord = words[current].length();
//            lenNextWord = words[next].length();
//            for (int letterCurr = 0; letterCurr < lenCurrWord; letterCurr++){
//                for (int letterNext = 0; letterNext < lenNextWord; letterNext++){
//                    if (words[current][letterCurr] == words[next][letterNext]){
//                        cout << words[current] << " и " << words[next] << " - ";
//                        cout << words[current][letterCurr] << " ";
//                    }
//                }
//            }
//            cout << endl;
//        }
//    }
//}

int linearSearch(string &subStr, string &str, int *result) {
    int cnt = 0;
    for (int i = 0; str[i]; ++i)
        for (int j = 0; str[i+j] == subStr[j]; ++j)
            if (j == subStr.length() - 1) result[cnt++] = i;
    return cnt;
}

int KMP(string &subStr, string &str, int *result) {
    if (subStr.length() > str.length()) return -1;

    unsigned long prefixLength = subStr.length() + 1 + str.length();
    int prefix[prefixLength];
    string concatStr = subStr + string("$") + str;
    unsigned long len = concatStr.length();

    prefix[0] = 0;
    int cnt = 0;
    for (int i = 1; i < len; ++i) {
        int j = prefix[i-1];
        while ((j > 0) && (concatStr[i] != concatStr[j]))
            j = prefix[j-1];
        if (concatStr[i] == concatStr[j])
            ++j;
        prefix[i] = j;
        if (j == subStr.length()) result[cnt++] = i - 2*j;
    }
    return cnt;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    string input;
    string inp1;
    string words[50];
    int option, YorN = 1;
    unsigned short line = getInput(input);
    cout << "\tчто сделать со строкой?\n 1. отредактировать\n 2. вывести слова последовательности в обратном порядке" <<
    "\n 3. посчитать количество букв в словах\n 4. произвести поиск подстроки\n\n";
    while (YorN == 1) {
        //unsigned short line = getInput(input);
        cout << " выберите: ";
        cin >> option;
        switch (option) {
            case 1: {
                correctTheText(input);
                cout << input << endl;
            }
                break;
            case 2: {
                inp1 = input;
                removePunctMarks(inp1);
                inp1 += ' ';
                reverse1(inp1, &words[0]);
                reverse2(inp1, &words[0]);
                reverse3(inp1, &words[0]);
            }
                break;
            case 3: {
                inp1 = input;
                removePunctMarks(inp1);
                howManyLetters(inp1, &words[0]);
            }
                break;
            case 4: {
                cout << " найти: ";
                string toFind;
                cin.sync();
                getline(cin, toFind);

                int entrance[10];
                int cnt = linearSearch(toFind, input, entrance);
                cout << " линейный поиск: " << cnt << " входов подстроки" << endl;
                cnt = KMP(toFind, input, entrance);
                cout << " КМП: " << cnt << " входов подстроки" << endl;

                cout << " проверка: " << input << '\n';
                for (int i = 0; i < 11; ++i) cout << ' ';
                for (int i = 0; i < cnt; ++i) {
                    int spacesN = (i == 0) ? entrance[i] : entrance[i] - entrance[i - 1] - int(toFind.length());
                    for (int j = 0; j < spacesN; ++j) cout << ' ';
                    cout << toFind;
                }
                cout << endl;
            }
        }
        cout << "\n продолжить выполнение? (1 - да, 0 - нет)" << endl;
        cin >> YorN;
        cout << "\n";
    }
    return 0;
}
