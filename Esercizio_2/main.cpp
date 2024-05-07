#include "SortingAlgorithm.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>       // For time measurement
#include <numeric>      // For function "iota"
#include <algorithm>
#include <random>       // Set of classes and functions for generating random numbers

using namespace std;
using namespace SortLibrary;

// EVALUATION of the performance of the BUBBLE SORT algorithm
template<typename T>
double time_BubbleSort(vector<T>& v)
{
    chrono::steady_clock::time_point startTime_Bubble = chrono::steady_clock::now();
    BubbleSort(v);
    chrono::steady_clock::time_point endTime_Bubble = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(endTime_Bubble - startTime_Bubble).count();
}

// EVALUATION of the performance of the MERGE SORT algorithm
template<typename T>
double time_MergeSort(vector<T>& v)
{
    chrono::steady_clock::time_point startTime_Merge = chrono::steady_clock::now();
    MergeSort(v);
    chrono::steady_clock::time_point endTime_Merge = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(endTime_Merge - startTime_Merge).count();
}

// DEFINITION of a function that print the vector on the screen
void printVector(vector<int> v)
{
    cout << "VECTOR OF SIZE " << v.size() << " : " << endl;
    for(int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

// DEFINITION of a function that print the vector on the screen in REVERSE
void printReverseVector(vector<int> v)
{
    cout << "VECTOR OF SIZE " << v.size() << " : " << endl;
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = v.size() - i - 1;    // Decrease the value from n-1 to 0
    }
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

// "argc" is the number of command line arguments, "argv" the vector containing these arguments
// The first argument is the NAME of the program
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "ATTENTION: MUST provide at least one argument in the COMMAND LINE for the size of the vector!" << endl;
        return 1;
    }

    const int num_tests = 250;

    // Sizes entered in the COMMAND LINE:  15   30   50   100   1000   2000
    for (int i = 1; i < argc; ++i)
    {
        unsigned int sizeVector = atoi(argv[i]);
        if (sizeVector <= 0)
        {
            cerr << "ATTENTION: Entered an invalid size!" << endl;
            return 2;
        }

        // ***************************************************************************************************************
        cout << "1st CASE: Vector with uniformly distributed random values (values can be duplicated)" << endl;

        double sumBubbleSort = 0.0;     // Initialization of sumBubbleSort, type double
        double sumMergeSort = 0.0;      // Initialization of sumMergeSort, type double
        vector <int> v1(sizeVector);
        vector <int> v2;

        random_device rd;   // Initialize a random number non-deterministic generator
        mt19937 gen(rd());  // Initialize 'gen' based on the Mersenne Twister using a random value provided by 'random_device'
        uniform_int_distribution<> dis(0, 4000);
        // Generate random numbers between 0 and 4000 included (uniformly ordered values)

        for (unsigned int j = 0; j < num_tests; j++)
        {
            for (unsigned int k = 0; k < sizeVector; k++)
            {
                v1[k] = dis(gen);
            }
            v2 = v1;
            sumBubbleSort = sumBubbleSort + time_BubbleSort(v1);
            sumMergeSort = sumMergeSort + time_MergeSort(v2);
        }
        double averageBubbleSort = sumBubbleSort / num_tests;       // Initialization of averageBubbleSort, type double
        double averageMergeSort = sumMergeSort / num_tests;         // Initialization of averageMergeSort, type double
        printVector(v2);        // Or it's the same printVector(v1);

        cout << "AVERAGE of elapsed times with BUBBLE SORT \t"
             << averageBubbleSort << " nanoseconds (ns)" << endl;
        cout << "AVERAGE of elapsed times with MERGE SORT :\t"
             << averageMergeSort << " nanoseconds (ns)" << endl;

        if(averageBubbleSort < averageMergeSort)
        {
            cout << "BUBBLE SORT is the most EFFICIENT \n" << endl;
        }
        else
        {
            cout << "MERGE SORT is the most EFFICIENT \n" << endl;
        }

        // ***************************************************************************************************************
        cout << "2nd CASE: Vector with values distributed in crescent order" << endl;

        sumBubbleSort = 0.0;
        sumMergeSort = 0.0;
        vector <int> v3(sizeVector);
        iota(v3.begin(), v3.end(), 0);
        // iota: function that sets all elements of the sequence with incremental values starting from an initial value

        for (unsigned int j = 0; j < num_tests; j++)
        {
            sumBubbleSort = sumBubbleSort + time_BubbleSort(v3);
            sumMergeSort = sumMergeSort + time_MergeSort(v3);
        }
        averageBubbleSort = sumBubbleSort / num_tests;
        averageMergeSort = sumMergeSort / num_tests;
        printVector(v3);

        cout << "AVERAGE of elapsed times with BUBBLE SORT :\t"
             << averageBubbleSort << " nanoseconds (ns)" << endl;
        cout << "AVERAGE of elapsed times with MERGE SORT : \t"
             << averageMergeSort << " nanoseconds (ns)" << endl;

        if(averageBubbleSort < averageMergeSort)
        {
            cout << "BUBBLE SORT is the most EFFICIENT \n" << endl;
        }
        else
        {
            cout << "MERGE SORT is the most EFFICIENT \n" << endl;
        }

        // ***************************************************************************************************************
        cout << "3rd CASE: Vector with values distributed in decrescent order" << endl;

        sumBubbleSort = 0.0;
        sumMergeSort = 0.0;
        vector <int> v4;
        iota(v3.begin(), v3.end(), 0);
        reverse(v3.begin(), v3.end());   // Reverse the order of the elements in the vector v2

        for (unsigned int j = 0; j < num_tests; j++)
        {
            v4 = v3;
            sumBubbleSort = sumBubbleSort + time_BubbleSort(v3);
            sumMergeSort = sumMergeSort + time_MergeSort(v4);
        }
        averageBubbleSort = sumBubbleSort / num_tests;
        averageMergeSort = sumMergeSort / num_tests;
        printReverseVector(v4);     // Or it's the same printReverseVector(v3);

        cout << "AVERAGE of elapsed times with BUBBLE SORT :\t"
             << averageBubbleSort << " nanoseconds (ns)" << endl;
        cout << "AVERAGE of elapsed times with MERGE SORT :\t"
             << averageMergeSort << " nanoseconds (ns)" << endl;

        if(averageBubbleSort < averageMergeSort)
        {
            cout << "BUBBLE SORT is the most EFFICIENT \n" << endl;
        }
        else
        {
            cout << "MERGE SORT is the most EFFICIENT \n" << endl;
        }

        // ***************************************************************************************************************
        cout << "4th CASE: Vector with all the same values" << endl;

        sumBubbleSort = 0.0;
        sumMergeSort = 0.0;
        vector <int> v5(sizeVector, 19);   // Vector with all values equal to 19, for the size of the vector
        vector <int> v6;

        for (unsigned int j = 0; j < num_tests; j++)
        {
            v6 = v5;
            sumBubbleSort = sumBubbleSort + time_BubbleSort(v5);
            sumMergeSort = sumMergeSort + time_MergeSort(v6);
        }

        averageBubbleSort = sumBubbleSort / num_tests;
        averageMergeSort = sumMergeSort / num_tests;
        printVector(v6);        // Or it's the same printVector(v5);

        cout << "AVERAGE of elapsed times with BUBBLE SORT :\t"
             << averageBubbleSort << " nanoseconds (ns)" << endl;
        cout << "AVERAGE of elapsed times with MERGE SORT :\t"
             << averageMergeSort << " nanoseconds (ns)" << endl;

        if(averageBubbleSort < averageMergeSort)
        {
            cout << "BUBBLE SORT is the most EFFICIENT \n" << endl;
        }
        else
        {
            cout << "MERGE SORT is the most EFFICIENT \n" << endl;
        }
    }

    cout << "--- FINAL RESULTS --- \n"
         << "* In the CASE of Vector with all the same values, BUBBLE SORT is always the most efficient (small or large size) \n"
         << "* In the CASE of Vector with values distributed in crescent or decrescent order, "
         << "BUBBLE SORT is the most efficient (small or large size) \n"
         << "* In the CASE of Vector with uniformly distributed random values, MERGE SORT is the most efficient "
         << "for vectors with large size and BUBBLE SORT is the most efficient for vectors with small size" << endl;

    return 0;
}
