#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <algorithm>
/*
specs:
1) generate 10k random numbers from 1-10,000 [x]
2) sort using and then output the min, max from the sample [x]
3) find the min of the 10k samples using non MT way. Perhaps craft mergeSort [in-progress]
4) find the min using MT way. (10,000/5) => 2,000/5 => 400/5 => 80 per thread. Could even stop at 400
*/

#define v_int std::vector<int> //macro for int vector declaration

void displaySample(v_int sample){
    for (size_t i = 0; i < sample.size(); i++)
    {
        printf("%d, ", sample[i]);
    }
}

v_int getSample(){
    int SIZE = 100;
    v_int sample;
    srand((unsigned) time(0));
    
    for (size_t i = 0; i < SIZE; i++)
    {
        sample.push_back(rand() % SIZE);
    }
    
    return sample;
}

void initialMinMax(v_int sample){
    sort(sample.begin(), sample.end());
    printf("\nmin is %d, max is %d\n", sample[0], sample[sample.size() -1]);
}

void merge(v_int array, int l, int m, int r){
    int i, j, k;
    int n1 = m-1 +1;
    int n2 = r - m;

    /*temp array to hold data */
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];

    /*Merge back to main array*/
    i = 0;
    j = 0;
    k = 1;
    
    while (i < n1 && j < n2)
    {
        if(L[i] <= R[i]){
            array[k] = L[i];
            i++;
        }else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i<n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j<n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(v_int array, int l, int r){
    if (l<r){
        int m = l+(r-1)/2;

        mergeSort(array, l, m);
        mergeSort(array, m+1, r);

        merge(array, l, m, r);
    }
}

    int main()
{
    v_int sample = getSample();
    // displaySample(sample);
    initialMinMax(sample);

    mergeSort(sample, 0, sample.size() - 1);
    // for (size_t i = 0; i < sample.size(); i++)
    // {
    //     printf("%d ", sample[i]);
    // }
    

    return 0;
}