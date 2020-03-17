#include <iostream>
#include <cmath>
#include <limits>
#include <ctime>
#include <stdio.h>
#include <unistd.h>
#include <map>
#include <assert.h>


using namespace std;


// EXERCISE 4


double round(double x, unsigned n){
    int temp = floor(x * pow(10, n) + 0.5);
    float final = (float)temp/pow(10,n);
    return final;
}



// EXERCISE 5


int gcdFunc(int n1, int n2){

    int gcd;

    if (n1 == 0){
        gcd = n2;
    }
    else if (n2 == 0){
        gcd = n1;
    }
    else{
        while (n1 != n2){
            if (n1 < n2){
                n2 -= n1;
            }
            else{
                n1 -= n2;
            }
        }
        gcd = n1;
    }
    return gcd;
}


// EXERCISE 6

int timeElapsed(){
    static int firstTime = time(NULL);

    return time(NULL) - firstTime;
}



// EXERCISE 7


bool readInt(int &x){
    cout << "Enter a number please: ";
    cin >> x;
    bool result = true;

    if (cin.fail()){
        cin.clear();
        x = NULL;
        result = false;
    }
    else if (cin.peek() != '\n' || cin.peek() != '/'){
        x = NULL;
        result = false;
    }

    cin.ignore(1000, '\n');
    return result;
}


// EXERICSE 8


bool readFractionElement(int &x){
    cin >> x;
    bool result = true;

    if (cin.fail()){
        cin.ignore(1000, '\n');
        cin.clear();
        x = NULL;
        result = false;
    }
    return result;
}


bool readFraction(int &numerator, int &denominator){
    cout << "Enter a fraction: ";
    bool temp1 = readFractionElement(numerator);

    if (cin.peek() != '/'){
        temp1 = false;
    }
    cin.ignore(1);

    bool temp2 = readFractionElement(denominator);

    return temp1 && temp2;
}


void reduceFraction(int &numerator, int &denominator){
    int gcd = gcdFunc(numerator, denominator);
    cout << gcd << endl;
    numerator /= gcd;
    denominator /= gcd;
}

void calculator(int n1, int n2, int d1, int d2, char op){

    int nR, dR;

    switch(op){
        case '+':
            if (d1 == d2){
               nR = n1 + n2;
               dR = d1;
            }
            else{
                dR = d1 * d2;
                nR = n1*d2 + n2*d1;
            }
            break;
        case '-':
            if (d1 == d2){
                nR = n1 - n2;
                dR = d1;
            }
            else{
                dR = d1 * d2;
                nR = n1*d2 - n2*d1;
            }
            break;
        case '*':
            nR = n1 * n2;
            dR = d1 * d2;
            break;
        case '/':
            nR = n1 * d2;
            dR = d1 * n2;
            break;
    }

    cout << "The result is: " << nR << "/" << dR;


    reduceFraction(nR, dR);

    cout << "The result is: " << nR << "/" << dR;
}



// EXERCISE 9

bool leapYear(int year){
    if (year%400 == 0){
        return true;
    }
    else if (year%4 == 0 && year%100 != 0){
        return true;
    }else {
        return false;
    }
}


int numberOfDays(int month, int year){ // month starts at 0=january
    if (month >= 8){
        if(month % 2 == 0){
            return 31;
        }
        else{
            return 30;
        }
    }
    else{
        if(month == 2){
            return 30 - 2 + leapYear(year);
        }
        else if (month % 2 == 1){
            return 31;
        }
        else{
            return 30;
        }
    }
}


int dayOfWeek(int d, int m, int year){
    map<int, int> codeLeap = {
            {1, 6},
            {2, 2},
            {3, 3},
            {4, 6},
            {5, 1},
            {6, 4},
            {7, 6},
            {8, 2},
            {9, 5},
            {10, 0},
            {11, 3},
            {12, 5},
    };

    map<int, int> codeNotLeap = {
            {1, 0},
            {2, 3},
            {3, 3},
            {4, 6},
            {5, 1},
            {6, 4},
            {7, 6},
            {8, 2},
            {9, 5},
            {10, 0},
            {11, 3},
            {12, 5},
    };

    int code;

    if (leapYear(year)){
        code = codeLeap[m];
    }
    else{
        code = codeNotLeap[m];
    }

    int a = 0;

    for (int i = 0; i < 2; ++i) {
        a += year%10 * pow(10, i);
        year /= 10;
    }

    int s = 0;

    for (int i = 0; i < 2; ++i) {
        s += year%10 * pow(10, i);
        year /= 10;
    }

    return (int)(floor(5*a/4) + code + d - 2 * (s%4) + 7) % 7;
}


void showCalendar(int m, int year){
    cout << "Sun\t\tMon\t\tTue\t\tWed\t\tThu\t\tFri\t\tSat\n\n";
    int currDayOfWeek = dayOfWeek(1, m, year);
    int currDay = 1;
    int totalDays = numberOfDays(m, year);
    // Redefining saturday as last day
    if (currDayOfWeek == 0){
        currDayOfWeek = 7; //
    }

    for (int i = 1;; ++i) {
        if(currDay > totalDays)
            break;
        if (currDayOfWeek == 8){
            currDayOfWeek = 1;
            cout << endl;
        }
        if (i < currDayOfWeek){
            cout << " \t\t";
        }
        else{
            cout << currDay << "\t\t";
            currDayOfWeek ++;
            currDay++;
        }
    }
}


// EXERCISE 12

int rollDie(int low= 1, int high= 6){
    assert(high>= low);
    return(rand() % (high-low+1)) + low;
}

// EXERCISE 13

double integrate(double func(double), double a, double b, int n){
    double h = (b-a)/n;
    double cumSum = 0;
    for (int i = 1; i <= n; ++i) {
        cumSum += (0.5*h*(func(a+(i-1)*h) + func(a+i*h)));
    }
    return cumSum;
}

double f(double x){
    return sqrt(4-x*x);
}

int main() {
    cout << integrate(f, -2, 2, 50);
}
