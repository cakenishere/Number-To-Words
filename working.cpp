// working.cpp by Bill Weinman <http://bw.org/>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;

    static const char * _singles[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    
    static const char * _teens[] = {
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };
    
    static const char * _tens[] = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninty",
    };
    
    static const char * _hundred = "hundred";
    
    static const char * _powers[] = {
        "", "thousand", "million", "billion", "trillion", "quadrillion"
    };
    
    static const char * _hyphen = "-";
    static const char * _space = " ";

void printchr(string words){
    for(auto i = words.begin(); i != words.end(); i++){
        cout << (int)(*i);
    }
    printf("\n");
}

void appendbuf(vector<string> & str, const char * words){
    str.push_back(words);
    str.push_back(_space);
}

vector<string> numtowords(int num){
    vector<string> numwords;
//Special
    if(num == 0){
        appendbuf(numwords, _singles[num]);
    }

//Hundreds
    if(num >= 100 && num < 1000){
        appendbuf(numwords, _singles[(int)(num/100)]);
        appendbuf(numwords, _hundred);
        num %= 100;
    }
//Tens
    if(num >= 20 && num < 100){
        appendbuf(numwords, _tens[(int)(num/10)]);
        num %= 10;
    }
    else if(num >= 10 && num < 20){
        appendbuf(numwords, _teens[num%10]);
        num = 0;
    }

//Singles
    if(num >= 1 && num < 10) appendbuf(numwords, _singles[num]);
    
    return numwords;
}

template <typename T>
void printv(vector<T> v){
    printf("WORDS\t: ");
    for(auto i : v){
        cout << i;
    }
    cout << "\n";
}

void bound(int i){
    switch(i){
        case 1:
            printf("\n----------------------------------------------------\n");
            break;
        case 2:
            printf("----------------------------------------------------\n\n");
            break;
    }
}

void numword(){
    //Initialize
    uint16_t num;
    stack<int> digits_3;
    string number;
    vector<string> numwords;

    //Prompt the number from user
    printf("Please enter yout number (0 ~ 999,999,999,999,999,999) : ");
    getline(cin, number);
    bound(1);
    printf("NUMBER\t: %s\n", number.c_str());
    
    //Divided the number into sections of 3 digits
    while(number.size() != 0){
        num = 0;
        for(int i = 0; i < 3 & number.size() != 0; i++){
            num += ((uint16_t)(number[number.size() - 1]) - 48)*(uint16_t)pow(10, i);
            number.pop_back();
        }
        digits_3.push(num);
    }

    //Translate the sections of number into words
    while(digits_3.empty() != true){
        for(auto it : numtowords(digits_3.top())){
            numwords.push_back(it);
        }
        digits_3.pop();
        appendbuf(numwords, _powers[digits_3.size()]);
    }
        
    printv(numwords); //PRINT OUT THE VALUE
    bound(2);
        
}


int main()
{   
    string option;
    puts("NUMBER TO WORDS");
    puts("This program is made by Tan Caken, 7-8-2021");
    do{
        puts("Choose one of the following option");
        puts("1. Input a number into words");
        puts("2. Close the program");
        printf("Input : ");
        getline(cin, option);

        if(option[0] == '1' && option.size() == 1) numword();
        else if(option[0] == '2' && option.size() == 1) puts("Thank for using my program. Feel free to feedback!");
        else puts("Please only input 1 or 2");

        puts(" ");

    }while(option[0] != '2' || option.size() != 1);    
}
