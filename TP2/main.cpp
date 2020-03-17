#include <iostream>
#include <cmath>
#include <climits>
#include <iomanip>
#include <stdlib.h>


using namespace std;


int ex2a() {
    float n1, n2, n3, aux;
    cin >> n1 >> n2 >> n3;

    if (n1 < n2) {
        aux = n2;
        n2 = n1;
        n1 = aux;
    }
    if (n1 < n3) {
        aux = n3;
        n3 = n1;
        n1 = aux;
    }
    if (n2 < n3) {
        aux = n3;
        n3 = n2;
        n2 = aux;
    }
    cout << n1 << n2 << n3;
    // END OF 2B

    if (n2 + n1 > n3) {
        cout << "Not possible" << endl;
    } else{
        cout << "Very possible" << endl;
    }
}

int ex3(){
    int n1, n2;
    cout << INT16_MIN;
    cin >> n1 >> n2;
    if (INT16_MAX - n1 < n2){
        cout << "Sum overflow" << endl;
    }
    else if (INT16_MIN - n2 > n1){
        cout << "Sum underflow;" << endl;
    }
    else{
        cout << n1+n2 << endl;
    }
}


int ex4(){
   int weight;
   cout << "Insert weight "; cin >> weight;

   if (weight <= 500){
       cout << "Cost is " << weight << endl;
   }
   else if (weight <= 1000){
       float temp = (weight-500) / 100.0;
       cout << "Cost is " << ceil(temp) * 1.5 + 5;
   }
   else {
       float temp = (weight-1000) / 250.0;
       cout << "Cost is " << ceil(temp) * 5 + 12.5;
   }
}


int ex5(){
    float A, B, C;

    cout << "Insert the coeficients (A B C) "; cin >> A >> B >> C;

    float temp = sqrt(abs(pow(B, 2) -4 * A * C));

    cout << pow(B, 2) -4*A*C << endl;


    if (pow(B, 2) -4*A*C > 0)
    {
        cout << "The equation has 2 real roots: " << (-B + temp)/(2 * A) << "and " << (-B - temp)/(2 * A);
    }
    else if (pow(B, 2) -4 *A*C == 0)
    {
        cout << "The equation has 1 real root: " << (-B)/(2 * A);
    }
    else{
        cout << "The equation has 2 imaginary roots: " << (-B)/(2 * A) << " + " << temp/(-2*A) << "i  and  " << (-B)/(2 * A) << " - " << temp/(-2*A) << "i";
    }
}


int ex6(){
    float n, q, j;

    cout << "Please insert n years, q dollars, j interest rate (n q j)" << endl;
    cin >> n >> q >> j;

    for (int i = 0; i < n; i++) {
        q += q * j/100;
    }

    cout << q;
}


int ex7a(int n){
    //int n;
    bool prime = true;

    //cout << "Insert number "; cin >> n;

    int max = sqrt(n);

    for (int i = 2; i <= max; i++){
        if (n % i == 0){
            prime = false;
            break;
        }
    }
    return prime;
    if (prime){
        cout << "The number you inserted is a prime";
    }else{
        cout << "The number you inserted is not a prime";
    }
}


int ex7b(){
    for (int x = 1; x <= 1000; x++){
        if (ex7a(x)){
            cout << x << endl;
        }
    }
}


int ex7c(){
    unsigned long n = ULONG_MAX;

    while (n > 1){
        if (ex7a(n)){
            cout << n;
            break;
        }
        n--;
    }
}


int ex8(){
    cout << "Insert the limits and the step (min max step) ";
    float xMin, xMax, step;
    cin >> xMin >> xMax >> step;

    cout << "ang\t\tsin\t\t\tcos\t\t\ttan" << endl;
    for (float i = xMin; i <= xMax; i+=step){
        double temp = i * M_PI / 180.0;
        cout << fixed; cout << setprecision(6);
        double x;
        if ((int)i - i == 0 && (int)i % 90 == 0 && (int)i % 180 != 0){
            x = INFINITY;
        }
        else{
            x = tan(temp);
        }
        cout << i << "\t" << sin(temp) << "\t" << cos(temp) << "\t" << x << endl;
    }
}


int lenght(unsigned long n){
    int counter = 0;
    while (n > 0){
        counter += 1;
        n /= 10;
    }
    return counter;
}

// They are ints so u can add digit multiplying reversded by 10
int ex9(){
    unsigned long n;
    unsigned long copyN;
    unsigned long reversedN = 0;
    int LEN;
    cin >> n;
    copyN = n;
    LEN = lenght(n);
    for (int i = 1; i <= LEN; i++){
        reversedN += (copyN % 10) * pow(10, LEN-i);
        copyN /= 10;
    }
    if (reversedN == n){
        cout << "Is palindrome";
    }else{
        cout << "Is not palindrome";
    }
}


int ex10(){
    int n, i;
    cin >> n;
    i = 2;

    while(1){
        if (ex7a(n)){
            cout << n;
            break;
        }
        else if (!ex7a(i)){
            i ++;
            continue;
        }

        if (n % i == 0){
            n /= i;
            cout << i << "X";
        }
        else{
            i ++;
        }
    }
}


long int fact(long int n){
    unsigned long long fact_ = 1;
    for (int i = 2; i <= n; i++){
        fact_ *= i;
    }
    return fact_;
}


int ex11(){
    int n;
    float x;
    double sumPI, sumE, sumEX;

    sumPI = 0; sumE = 0; sumEX = 0;

    cout << "Input n and x (n x) "; cin >> n >> x;
    for(int i = 1; i <= n; i++){
        sumPI += pow(-1, i + 1) * 4/(2*i-1);
        sumE += (double)1/ fact(i-1);
        sumEX += pow(-1, i + 1) * x / fact(i-1);
    }

    cout << sumPI << endl << sumE << endl << sumEX;
}


int ex12(){
    int n, i;
    float x, variation;
    double sumPI;
    i = 0;
    sumPI = 0;

    cout << "Input n, x and variation (n x variation) "; cin >> n >> x >> variation;
    while(1){
        double bef = sumPI;
        sumPI += pow(-1, i + 1) * 4/(2*i-1);
        i++;
        if (abs(sumPI - bef) <= variation){
            break;
        }
    }

    cout << sumPI - 4 << endl;
}


int ex13a(){
    int LEN, a = 0, b = 0;
    cout << "Input the number of items: "; cin >> LEN;
    cout << "Proceed to instroduce the numbers:" << endl;
    for (int i = 0; i < LEN; i++){
        int temp; cin >> temp;
        a += temp;
        b += pow(temp, 2);
    }
    double stdDeviation = sqrt((b- (pow(a,2)/LEN))/LEN);
    cout << stdDeviation;
}


int ex13b(){
    int len = 0, a = 0, b = 0;

    while(1){
        int temp; cin >> temp;
        if(temp == 0){
            break;
        }
        a += temp;
        b += pow(temp, 2);
        len++;
    }
    double stdDeviation = sqrt((b- (pow(a,2)/len))/len);
    cout << stdDeviation;
}


int ex13c(){
    int len = 0, a = 0, b = 0;

    while(1){
        int temp; cin >> temp;
        if(cin.fail()){
            cout << "heiz";
            if(cin.eof()) {
                cout << "detected\n";
                break;
            }
        }
        a += temp;
        b += pow(temp, 2);
        len++;
    }

    double stdDeviation = sqrt((b- (pow(a,2)/len))/len);
    cout << stdDeviation;
}


int ex14(){
    double rq = 1, rqn, n, delta;
    int maxIter;
    cout << "Insert Number, delta and max iterations: ";
    cin >> n >> delta >> maxIter;

    int digits = log(n)+1;

    cout <<" SQRT VALUE: " << sqrt(n) <<endl;

    for(int i = 0; i < maxIter; i++){
        rqn = (rq + n / rq) / 2;
        if (abs(n - pow(rqn, 2)) <= delta){
            cout << "End" << endl;
            break;
        }
        rq = rqn;
    }
    cout << setprecision(digits);
    cout << rqn << endl;
}


int ex15(){
    srand(time(NULL));
    int n1 = 2 + rand() % 7;
    int n2 = 2 + rand() % 7;

    cout << "Make " << n1 << " X " << n2 << endl;

    int t1 = time(NULL);
    int answer;

    cout << "Type your answer ";
    cin >> answer;
    int t2 = time(NULL);
    cout << t2-t1 << endl;
    if (answer == n1 * n2){
        if (t2-t1 <= 5){
            cout << "E bem!";
        }
        else if (t2-t1 <= 10){
            cout << "Satisfactory";
        }
        else{
            cout << "Tas muito lento meu";
        }
    }
    else{
        cout << "Very Bad";
    }
}


int ex16(){

    float mem = 0;
    int n1, n2;
    char op;


    while (1){
        float result;

        cout << "Please enter a command: ";
        cin >> n1 >> op >> n2;

        switch(op){
            case 'X':
                result = n1 * n2;
                break;
            case '/':
                result = (float) n1 / n2;
                break;
            case '+':
                result = n1 + n2;
                break;
            case '-':
                result = n1 - n2;
                break;
            default:
                cout << "Invalid" << endl;
                continue;
        }

        cout << "Your result is: " << result << endl << "Please enter a LINE: ";

        string command;

        cin >> command;

        if (command == "C"){
            system("clear");
        }
        else if (command == "E"){
            return 0;
        }
        else if (command == "M"){
            mem = result;
        }
        else if (command[0] == 'M'){
            if (command[1] == 'C'){
                mem = 0;
            }
            else if (command[1] == '+'){
                mem += result;
            }
            else if (command[1] == '-'){
                mem -= result;
            }
            else if (command[1] == 'R'){
                cout << "Currently registered in memory is: " << mem << endl;
            }
            else {
                cout << "Error" << endl;
            }
        }
        else{
            cout << "Error" << endl;
        }

    /*    if (toupper(command) == "END"){
            break;
        }*/
    }
    cout << "SKIP here";
}


int main() {
    ex16();
    return 0;
}