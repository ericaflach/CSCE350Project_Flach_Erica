/*
Written by Erica Flach
*/
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std::chrono;
using namespace std;

void readAndParseFile(float* p);
void writeOutput(float* p);
void quickSort(float* p);
void recQuickSort(float* p, int left, int right);
float medianOfThree(float* p, int left, int right);
void swap(float* p, int dex1, int dex2);
int partitionIt(float* p, int left, int right, double pivot);
void manualSort(float*p, int left, int right);
void printArray(float* p);
void writeTime(string time);

string in_file_name;
string out_file_name;
string time_file_name = "Flach_Erica_ExecutionTime.txt";
int array_size = 0;
float* arr_ptr;

void readAndParseFile(float* p) {//Reads the file and places each floating point number into the array
    fstream newFile;
    string str;
    newFile.open(in_file_name,ios::in);
        if(newFile.is_open())
        {
            getline(newFile, str);
            newFile.close();
        }

    string delimiter = " ";
    size_t pos = 0;
    string token;
    int index = 0;
        while((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0,pos);
            float token_float = stof(token);
            p[index] = token_float;
            index++;
            str.erase(0, pos + delimiter.length());
        }
}

void writeOutput(float* p) {//Writes the sorted array into the output file
    ofstream myfile (out_file_name);
    if (myfile.is_open())
    {
        for(int i = 0; i < array_size; i++){
            myfile << p[i] << " " ;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

void quickSort(float* p) {
    recQuickSort(p, 0, array_size-1);
}

void recQuickSort(float* p, int left, int right) {//Quicksort alorithm
    int size = right - left + 1;
    if(size <= 3)
        manualSort(p, left, right);
    else {
        double median = medianOfThree(p, left, right);
        int partition = partitionIt(p, left, right, median);
        recQuickSort(p, left, partition-1);
        recQuickSort(p, partition+1, right);
    }
}

float medianOfThree(float* p, int left, int right) {//selects pivot based on median of first, middle, and last values
    int center = round((left + right) / 2);
    if(p[left] > p[center]){
        swap(p, left, center);
    }
    if(p[left] > p[right]) {
        swap(p, left, right);
    }
    if(p[center] > p[right]) {
        swap(p, center, right);
    }
    swap(p, center, right-1);
    return p[right-1];
}

void swap(float* p, int dex1, int dex2) {//Swaps two array values
    float temp = p[dex1];
    p[dex1] = p[dex2];
    p[dex2] = temp;
}

int partitionIt(float* p, int left, int right, double pivot) {//Partitions the array into greater than and less that pivot
    int leftPtr = left;
    int rightPtr = right-1;
    while(true) {
        while(p[++leftPtr] < pivot)
            ;
        while(p[--rightPtr] > pivot)
            ;
        if(leftPtr >= rightPtr)
            break;
        else
            swap(p, leftPtr, rightPtr);
    }
    swap(p, leftPtr, right-1);
    return leftPtr;
}

void manualSort(float*p, int left, int right) {//Sorting the array once there are only a few elements left
    int size = right - left + 1;
    if(size <= 1)
        return;
    if(size == 2) {
        if(p[left] > p[right])
            swap(p, left, right);
        return;
    }
    else {
        if(p[left] > p[right-1])
            swap(p, left, right);
        if(p[left] > p[right])
            swap(p, left, right);
        if(p[right-1] > p[right])
            swap(p, right-1, right);
    }
}

void printArray(float* p) {//Prints array
    for(int i = 0; i < array_size; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
}

void writeTime(string time) {//Writes the execution time to ExecutionTime.txt
    ofstream myfile (time_file_name);
    if (myfile.is_open())
    {
        myfile << time;
        myfile.close();
    }
    else cout << "Unable to open file";
}

int main(int argc, char **argv)
{
    in_file_name = argv[1];
    out_file_name = argv[2];

    array_size = 10;

    float arr[array_size];
    arr_ptr = arr;
    
    auto start = high_resolution_clock::now();
    
    readAndParseFile(arr_ptr);
    quickSort(arr_ptr);
    writeOutput(arr_ptr);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    string time = "Execution Time: " + std::to_string(duration.count()) + " milliseconds";
    writeTime(time);
    return 0;
}