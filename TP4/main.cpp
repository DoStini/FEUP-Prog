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


void localMax(int NE, const int a[][NE]){
    for (int i = 1; i < NE-1; ++i) {
        for (int j = 1; j < NE-1; ++j) {
            int currVal = a[i][j];
            bool valid = true;
            for (int si = -1; i < 2; ++i) {
                for (int sj = -1; j < 2; ++j) {
                    if(a[si+i][sj+j] > currVal){
                        valid = false;
                    }
                }
            }

            if (valid)
                cout << currVal << " ";

        }
    }
}

int main() {
    vector<int> v = {20, 1, 5, 10, 10, 50, 10};
    vector<int> v2 = {50,20,3,15,50};
    vector<int> v3;
    vectorUnion(v, v2,v3);
    for (int i = 0; i < v3.size(); ++i) {
        cout << v3[i] << " ";
    }
}