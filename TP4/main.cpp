#include <iostream>
#include <vector>

using namespace std;

const int NE = 5;

// EXERCISE 1

/*
void readArray(int a[], size_t nElem){
    for (int i = 0; i < nElem; ++i) {
        cout << "Index " << i << ": ";
        cin >> a[i];
    }
}


int findValueInArray(const int a[], size_t nElem, int value, size_t pos1 = 0, size_t pos2 = -1){

    if (pos2 == -1){
        pos2 = nElem;
    }

    for (int i = pos1; i < pos2; ++i) {
        if(a[i] == value){
            return i;
        }
    }
    return -1;
}


size_t findMultValuesInArray(const int a[], size_t nElem, int value, int pos1, int pos2, int index[]){
    if (pos2 == -1){
        pos2 = nElem;
    }
    int counter = 0;

    for (int i = pos1; i < pos2; ++i) {
        if(a[i] == value){
            index[counter] = i;
            counter++;
        }
    }
    return counter;
}



void testing(int n1, int n2, int e1, int e2){
    int array[4];
    int index[4] = {-1};
    readArray(array, 4);
    cout << "Counter " << (findMultValuesInArray(array, 4, n1, 0, 3, index) == e1) << endl;
    for (int i = 0; i < 3; ++i) {
        cout << index[i] << endl;
    }
}

 */

// EXERCISE 2


vector<int> readVector(){
    vector<int> v;

    while (1){
        int item; cout << "Enter item: "; cin >> item;
        if (cin.fail()){
            if(cin.eof()){
                cin.clear();
                cout << "Reading ended." << endl;
                break;
            }
            else{
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else{
            v.push_back(item);
        }
    }

    return v;
}

vector<int> readVector(size_t nElem){
    vector<int> v;
    for (int i = 0; i < nElem; ++i) {
        int item; cout << "Enter item: "; cin >> item;
        v.push_back(item);
    }
    return v;
}

vector<int> findMultValuesInVector(const vector<int> a, int value, int pos1 = 0, int pos2 = -1){
    if (pos2 == -1){
        pos2 = a.size();
    }
    int counter = 0;
    vector<int> index;
    for (int i = pos1; i < pos2; ++i) {
        if(a[i] == value){
            index.push_back(i);
            counter++;
        }
    }
    return index;
}


// EXERCISE 3


void bubbleSort(vector<int> &v, char op){
    bool done = false;
    int iter = 1;
    while (!done || iter != v.size()){
        for (int i = 0; i < v.size() - iter; ++i) {
            done = true;
            if ((v[i] > v[i+1] && op == 'a') || (v[i] < v[i+1] && op == 'd')) {
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                done = false;
            }
        }
        iter++;
    }
}


bool ascending(int x, int y){
    return x > y;
}
bool descending(int x, int y){
    return x < y;
}


vector<int> bubbleSort(vector<int> v, bool f(int x, int y)){
    bool done = false;
    int iter = 1;
    while (!done || iter != v.size()){
        for (int i = 0; i < v.size() - iter; ++i) {
            done = true;
            if (f(v[i], v[i+1])){
                int temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                done = false;
            }
        }
        iter++;
    }
    return v;
}


// EXERCISE 4

int binarySearch(const vector<int> v, int value){
    int low = 0, high = v.size();
    bool found = false;

    while(low < high){
        int mid = (low + high)/2;

        if (v[mid] == value){
            return mid;
        }
        else if (v[mid] > value){
            if (mid == high){
                break;
            }
            high = mid;
        }
        else if (v[mid] < value) {
            if (mid == low){
                break;
            }
            low = mid;
        }
    }
    return -1;
}


// EXERCISE 5



void removeDuplicates(vector<int> &v){
    int idx = 0;
    while(idx < v.size()){
        int currVal = v[idx];
        // Search for duplicates
        int findIdx = idx + 1;
        while (findIdx < v.size()){
            if (v[findIdx] == currVal){
                int replaceIdx = findIdx+1;
                while (replaceIdx < v.size()){
                    int temp = v[replaceIdx];
                    v[replaceIdx-1] = v[replaceIdx];
                    replaceIdx++;
                }
                v.resize(v.size()-1);
            }
            findIdx++;
        }
        idx++;
    }
}



// EXERCISE 6


void vectorUnion(const vector<int> v1, const vector<int> v2, vector<int> &v3){
    for (int i = 0; i < v1.size(); ++i) {
        v3.push_back(v1[i]);
    }
    for (int i = 0; i < v2.size(); ++i) {
        v3.push_back(v2[i]);
    }

    removeDuplicates(v3);
    v3 = bubbleSort(v3, ascending);
}


void vectorIntersection(const vector<int> v1, const vector<int> v2, vector<int> &v3){
    for (int i = 0; i < v1.size(); ++i) {
        if (binarySearch(bubbleSort(v2, ascending), v1[i]) != -1){
            v3.push_back(v1[i]);
        }
    }
    v3 = bubbleSort(v3, ascending);
    removeDuplicates(v3);
}



// EXERCISE 7


void localMax(const int a[][NE], bool every){
    for (int i = !every; i < NE-!every; ++i) {
        for (int j = !every; j < NE-!every; ++j) {
            int currVal = a[i][j];
            bool valid = true;
            for (int si = -1; si < 2; ++si) {
                for (int sj = -1; sj < 2; ++sj) {
                    if(  0 <= si+i < NE &&  0 <= sj+j < NE && a[si+i][sj+j] > currVal){
                        valid = false;
                    }
                }
            }

            if (valid) {
                cout << currVal << " ";
            }
        }
    }
}

void localMax(vector<vector<int>> a, bool every){
    for (int i = !every; i < a.size()-!every; ++i) {
        for (int j = !every; j < a.size()-!every; ++j) {
            int currVal = a[i][j];
            bool valid = true;
            for (int si = -1; si < 2; ++si) {
                for (int sj = -1; sj < 2; ++sj) {
                    if(  0 <= si+i && si+i < a.size() &&  0 <= sj+j && sj+j < a.size() && a[si+i][sj+j] > currVal){
                        valid = false;
                    }
                }
            }

            if (valid) {
                cout << currVal << " ";
            }
        }
    }
}



// EXERICIO 8

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


int numberOfDays(int month, int year){ // month starts at 1=january
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
            return 28 + leapYear(year);
        }
        else if (month % 2 == 1){
            return 31;
        }
        else{
            return 30;
        }
    }
}



vector<vector<int>> buildData(){
    srand(time(NULL));
    vector<vector<int>> data;
    for (int i = 1; i < 13; ++i) {
        vector<int> month;
        for (int j = 0; j < numberOfDays(i, 2019); ++j) {
            int value = rand()%100;
            month.push_back(value);
            cout << value << "\t";
        }
        data.push_back(month);
        cout << endl;
    }
    cout << endl;
    return data;
}

double daily(vector<vector<int>> data){
    int nDays = 0;
    int currSum = 0;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            nDays++;
            currSum += data[i][j];
        }
    }
    return (double)currSum/nDays;
}

vector<int> monthly(vector<vector<int>> data){
    vector<int> output;
    for (int i = 0; i < data.size(); ++i) {
        int currSum = 0;
        for (int j = 0; j < data[i].size(); ++j) {
            currSum += data[i][j];
        }
        double value = (double) currSum / numberOfDays(i+1, 2019);
        output.push_back(value);
        cout << value << "\t";
    }
    cout << endl;
    return output;
}

vector<int> maximum(vector<vector<int>> data){
    vector<int> year;
    for (int i = 0; i < data.size(); ++i) {
        vector<int> month;
        int currMax = 0;
        int currDay = 0;
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] > currMax){
                currMax = data[i][j];
                currDay = j;
            }
        }
        year.push_back(currDay+1);
        cout << currDay+1 << "\t";
    }
    cout << endl;
    return year;
}

vector<vector<int>> aboveAverage(vector<vector<int>> data){
    int average = daily(data);
    vector<vector<int>> above;
    for (int i = 0; i < data.size(); ++i) {
        vector<int> month;
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j] > average){
                month.push_back(j+1);
                cout << j+1 << " ";
            }
        }
        cout << endl;
        above.push_back(month);
    }
    return above;
}


// EXERCICIO 9

/*

B)
 o apontador x fica com a posicao de x
o de apontador de y com a posicao de y
ao fazer ptr x= ptr y, o apontador de x fica com a posicao de memoria de y
output é
1, 2
memoria de y, memoria de y
2, 2

*/

// EXERICIO 10

/*
*p = values +1, p fica com a posiçao de memoria de values[1]
values[1]=3
values+1 = posicao memoria de values[1]
*p = 3
*values+3= values[3]=7
p+1 = posicao de memoria de values[2]
p[1]=values[2] porque p[0]= values[1], devido a declaracao de *p= values +1
p-values = 1 diferença de indices de p e values (a diferenca em memoria e de 4 posicoes, 1 inteiro)

*/



// EXERICIO 11


void testSort(){
    int a[5] = {2,1,6,5,9};

    //qsort()
}



// EXERICIO 12


int *readArray(size_t nElem){
    int *a = (int *)(malloc(nElem * sizeof(int)));
    for (int i = 0; i < nElem; ++i) {
        cout << "Index " << i << ": ";
        cin >> a[i];
    }
    return a;
}

int findValueInArray(const int *a, size_t nElem, int value, size_t pos1 = 0, size_t pos2 = -1){
    if (pos2 == -1){
        pos2 = nElem;
    }

    for (int i = pos1; i < pos2; ++i) {
        if(a[i] == value){
            return i;
        }
    }
    return -1;
}


size_t findMultValuesInArray(const int *a, int *index,size_t nElem, int value, int pos1=0, int pos2=-1){
    if (pos2 == -1){
        pos2 = nElem;
    }
    int counter = 0;

    for (int i = pos1; i < pos2; ++i) {
        if(a[i] == value){
            index[counter] = i;
            counter++;
        }
    }
    return counter;
}


void testing(){
    int *array = readArray(6);
    int *index = (int *)(malloc(6 * sizeof(int)));
    cout << "Counter " << findValueInArray(array, 6, 5) << endl;
    cout << "index array" << endl;
    size_t size = findMultValuesInArray(array, index,6, 5);
    for (int i = 0; i < size; ++i) {
        cout << index[i] << endl;
    }
    free(array);
    free(index);
}

int findValueInArray(const int *pos1, const int *pos2, int value){
    for (int *ptr = pos1; ptr < *pos2; ptr ++){
        if( (*ptr) == value){
            return ;
        }
    }

}


int main() {
    testing();
}





















