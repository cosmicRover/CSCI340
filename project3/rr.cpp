#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int vals[6][4];
int waitTimes[6];
int turnAroundTimes[6];

void readFile()
{
    std::ifstream file("processes.tsv");
    int process, priority, burst, arrival;

    int counter = 0;

    while (file >> process >> priority >> burst >> arrival)
    {
        // std::cout << process << " " << priority << " " << burst << " " << arrival;

        vals[counter][0] = process;
        vals[counter][1] = priority;
        vals[counter][2] = burst;
        vals[counter][3] = arrival;

        counter++;
    }

    file.close();

    std::cout << "Read values from processes.tsv\n";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << vals[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void calculateWaitTime()
{

    int pos;

    for (int i = 0; i < 6; i++)
    {
        pos = i;
        for (int j = j + 1; j < 6; j++)
        {
            if (vals[j][1] > vals[pos][1])
            {
                pos = j;
            }
        }

        int temp = vals[i][1];
        vals[i][1] = vals[pos][1];
        vals[pos][1] = temp;

        temp = vals[i][2];
        vals[i][2] = vals[pos][2];
        vals[pos][2] = temp;
    }

    waitTimes[0] = 0;
    printf("Process\tburst time\tpriority\twaiting time\tturn around time\n");
    for (int i = 0; i < 6; i++)
    {
        waitTimes[i] = 0;
        turnAroundTimes[i] = 0;
        for (int j = 0; j < i; j++)
        {
            waitTimes[i] = waitTimes[i] + vals[j][2];
        }

        turnAroundTimes[i] = waitTimes[i] + vals[i][2];

        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, vals[i][2], vals[i][1], waitTimes[i], turnAroundTimes[i]);
    }
}

int main()
{
    readFile();
    calculateWaitTime();
}