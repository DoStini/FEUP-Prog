#include <iostream>
#include <vector>

using namespace std;



// EXERCISE 1


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


// EXERCISE 2

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
    if (x > y){
        return true;
    }
    else{
        return false;
    }
}
bool descending(int x, int y){
    if (x < y){
        return true;
    }
    else{
        return false;
    }
}


void bubbleSort(vector<int> &v, bool f(int x, int y)){
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
}





int main() {
    vector<int> v = {50, 20, 1, 5, 10, 10, 2, 10};
    bubbleSort(v, ascending);
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
}