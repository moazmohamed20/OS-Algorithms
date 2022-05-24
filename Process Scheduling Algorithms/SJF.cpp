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

int ShortestJobFirst(Process processes[], int size, bool preemptive)
{
    int totalWaitTime = 0;

    // Order Received Processes List By Arrive Time
    // We Need To Order By Arrive Time Because Many Processes May Have The Same Burst Time So We Choose What Came First
    sort(processes, size);

    // Copy Received Processes List To New List
    Process list[size];
    for (int i = 0; i < size; i++)
        list[i] = processes[i];

    // Time Started... Let's Go Throw Processes
    int time = 0;
    while (true)
    {
        // 1) Find Shortest Job
        int minIndex = -1;
        int minBurst = 1000;
        for (int i = 0; i < size; i++)
        {
            if (time >= list[i].arrive // If Process Has Arrived
                && list[i].burst > 0   // And Not Used Before
                && list[i].burst < minBurst)
            {
                minIndex = i;
                minBurst = list[i].burst;
            }
        }

        // 2) If The Process Was Ready (Arrived)
        if (minIndex != -1)
        {
            // Don't Leave The Process Until It Is Finished (If Not Preemptive)
            do
            {
                cout << time << " ~ " << time + 1 << "\t\t" << list[minIndex].num << endl;
                list[minIndex].burst--;
                time++;
            } while (!preemptive && list[minIndex].burst > 0);
            if (list[minIndex].burst == 0)
                totalWaitTime += time - processes[minIndex].arrive - processes[minIndex].burst;
        }
        // 3) If No Process Is Ready
        else
        {
            // Check If There Is Any UnFinished Process
            bool allFinished = true;
            for (int i = 0; i < size; i++)
                if (list[i].burst > 0)
                {
                    allFinished = false;
                    cout << time << " ~ " << time + 1 << endl;
                    time++;
                    break;
                }

            if (allFinished)
                break;
        }
    }

    return totalWaitTime;
}

int main(int argc, char const *argv[])
{
    Process processes[] = {{1, 0, 1, 3}, {2, 3, 8, 4}, {3, 4, 5, 2}, {4, 5, 2, 2}, {5, 8, 4, 1}};

    int totalWaitTime = 0;
    totalWaitTime = ShortestJobFirst(processes, 5, false);
    cout << "Total Waiting Time = " << totalWaitTime;

    getchar();
    return 0;
}