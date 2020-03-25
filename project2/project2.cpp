#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>
/*
specs:
1) generate 10k random numbers from 1-10,000 [x]
2) sort using and then output the min, max from the sample [x]
3) find the min of the 10k samples using non MT way. P̶e̶r̶h̶a̶p̶s̶ ̶c̶r̶a̶f̶t̶ ̶m̶e̶r̶g̶e̶S̶o̶r̶t̶ Linear pass[x]
4) find the min using MT way. (10,000/5) => 2,000/5 => 400/5 => 80 per thread. Could even stop at 400
*/

#define v_int std::vector<int> //macro for int vector declaration
// #define thread std::thread     //macro for posix thread declaration, the C++ 11 way

/*global vector to store minimums*/
v_int mins;


void displaySample(v_int sample)
{
    for (size_t i = 0; i < sample.size(); i++)
    {
        printf("%d, ", sample[i]);
    }
}

/*get random numbers up to a million*/
v_int getSample()
{
    int SIZE = 10000;
    v_int sample;
    srand((unsigned)time(0));

    for (size_t i = 0; i < SIZE; i++)
    {
        sample.push_back(rand() % 100000);
    }

    return sample;
}

void initialMinMax(v_int sample)
{
    sort(sample.begin(), sample.end());
    printf("\nmin is %d, max is %d\n", sample[0], sample[sample.size() - 1]);
}

/*get min in linear time */
int getMin(v_int arr)
{
    int min = 2147483647;
    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

v_int subDivideArray(v_int original, int beignIndex, int endIndex)
{
    v_int subSample;

    for (int i = beignIndex; i < endIndex; i++)
    {
        subSample.push_back(original[i]);
    }
    return subSample;
}


void threadGetMinFn(v_int arr){
    int min = getMin(arr);
    printf("min from thread is --> %d\n", min);
}


void threadSubDivFn(v_int arr)
{
    int subSample[20][100];
    std::thread threads2[20];

    for (int i = 0; i < 20; i++)
    {
        v_int val = subDivideArray(arr, i, i + 100);
        for (int j = 0; j < val.size(); j++)
        {
            subSample[i][j] = val[j];
        }
    }

    // multiple threads to get minimum from sub threads
    for (int i = 0; i < 20; i++)
    {
        v_int val;
        for (int j = 0; j < 100; j++)
        {
            val.push_back(subSample[i][j]);
        }
        // threads2[i] = std::thread(threadGetMinFn, val);
        // printf("%d\n", int(val.size()));
        int min = 2147483647;
        for (int i = 0; i < val.size(); i++)
        {
            printf("%d ", val[i]);
        }
        printf("\n");

        // printf("%d\n", min);   
    }

    for (int i = 0; i < 20; i++)
    {
        if(threads2[i].joinable()){
            threads2[i].join();
        }
    }
}

int main()
{
    v_int sample = getSample();
    // displaySample(sample);
    initialMinMax(sample);
    int nonMtMin = getMin(sample);
    printf("Min from nonMt is: %d\n", nonMtMin);

    /*the MT way */
    /*divide sample up in 5 ways*/
    int subSample[5][2000];
    std::thread threads[5];

    for (int i = 0; i < 5; i++)
    {
        v_int val = subDivideArray(sample, i, i+2000); 
        for (int j = 0; j < val.size(); j++)
        {
            subSample[i][j] = val[i];
        }
        
    }

    // multiple threads to get minimum from sub threads
    for (int i = 0; i < 5; i++)
    {   
        v_int val;
        for (int j = 0; j < 2000; j++)
        {
            val.push_back(subSample[i][j]);
        }
        threads[i] = std::thread(threadSubDivFn, val);
        // printf("%d\n", int(val.size()));
    }

    for (int i = 0; i < 5; i++)
    {
        if(threads[i].joinable()){
            threads[i].join();
        }
    }

    // for (int i = 0; i < mins.size(); i++)
    // {
    //     printf("%d\n", mins[i]);
    // }
    

    return 0;
}