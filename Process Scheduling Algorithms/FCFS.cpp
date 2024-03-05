#include <iostream>

using namespace std;

struct Process
{
    int num, arrive, burst, priority;
};

void sort(Process array[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (array[i].arrive > array[j].arrive)
            {
                Process temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
}

int FirstComeFirstServed(Process processes[], int size)
{
    int totalWaitTime = 0;

    // Order Received Processes List By Arrive Time
    sort(processes, size);

    // Copy Received Processes List To New List
    Process list[size];
    for (int i = 0; i < size; i++)
        list[i] = processes[i];

    // Time Started... Let's Go Throw Processes
    int time = 0;
    for (int i = 0; i < size; i++)
    {
        // Don't Leave The Process Until It Is Finished
        while (list[i].burst > 0)
        {
            // If The Process Has Arrived
            if (time >= list[i].arrive)
            {
                cout << time << " ~ " << time + 1 << "\t\t" << list[i].num << endl;
                list[i].burst--;
            }
            // If Process Hasn't Arrived Yet
            else
            {
                cout << time << " ~ " << time + 1 << endl;
            }
            time++;
        }
        totalWaitTime += time - processes[i].arrive - processes[i].burst;
    }

    return totalWaitTime;
}

int main(int argc, char const *argv[])
{
    Process processes[] = {{1, 0, 1, 3}, {2, 3, 8, 4}, {3, 4, 5, 2}, {4, 5, 2, 2}, {5, 8, 4, 1}};

    int totalWaitTime = 0;
    totalWaitTime = FirstComeFirstServed(processes, 5);
    cout << "Total Waiting Time = " << totalWaitTime;

    getchar();
    return 0;
}