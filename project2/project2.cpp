#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <algorithm>
/*
specs:
1) generate 10k random numbers from 1-10,000 [x]
2) sort using and then output the min, max from the sample [x]
3) find the min of the 10k samples using non MT way. P̶e̶r̶h̶a̶p̶s̶ ̶c̶r̶a̶f̶t̶ ̶m̶e̶r̶g̶e̶S̶o̶r̶t̶ Linear pass[x]
4) find the min using MT way. (10,000/5) => 2,000/5 => 400/5 => 80 per thread. Could even stop at 400
*/

#define v_int std::vector<int> //macro for int vector declaration

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
    int SIZE = 100;
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

int main()
{
    v_int sample = getSample();
    // displaySample(sample);
    initialMinMax(sample);
    int nonMtMin = getMin(sample);
    printf("Min from nonMt is: %d\n", nonMtMin);
    /*TODO get min the MT way*/

    return 0;
}