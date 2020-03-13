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


int main(){
    v_int sample = getSample();
    // displaySample(sample);
    initialMinMax(sample);
    return 0;
}