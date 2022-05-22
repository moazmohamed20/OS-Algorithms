#include <iostream>

using namespace std;

class Queue
{
private:
    int front, rear, counter, size;
    int *array;

public:
    int length() { return counter; }
    bool isFull() { return counter == size; }
    bool isEmpty() { return counter == 0; }
    Queue(int init_size)
    {
        size = init_size;
        array = new int[size];
        front = rear = counter = 0;
    }
    void enqueue(int data)
    {
        array[rear] = data;
        rear = (rear + 1) % size;
        counter++;
    }
    int dequeue(void)
    {
        int temp = array[front];
        front = (front + 1) % size;
        counter--;
        return temp;
    }
};

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

int RoundRobin(Process processes[], int size, int quantum)
{
    int totalWaitTime = 0;

    // Order Received Processes List By Arrive Time
    sort(processes, size);

    // Copy Received Processes List To New List
    Process *list = new Process[size];
    for (int i = 0; i < size; i++)
        list[i] = processes[i];

    // Time Started... Let's Go Throw Processes
    int time = 0, enqueued = 0, current = 0;

    // Enqueue All myQueue With Arrive = 0
    Queue myQueue(size);
    for (int i = 0; i < size; i++)
    {
        if (list[i].arrive == 0)
        {
            myQueue.enqueue(i);
            enqueued++;
        }
    }

    // While Queue Has Items Or List Has Processes Not Enqueued Yet
    while (!myQueue.isEmpty() || enqueued < size)
    {
        // If Queue Has Items
        if (!myQueue.isEmpty())
        {
            current = myQueue.dequeue();
            // Hold The Dequeued Process For A quantum Period
            for (int i = 0; i < quantum; i++)
                // If The Process Not Finished
                if (list[current].burst > 0)
                {
                    cout << time << " ~ " << time + 1 << "\t\t" << list[current].num << endl;
                    list[current].burst--;
                    time++;
                }
            // If The Process Finished During quantum Period
            if (list[current].burst == 0)
                totalWaitTime += time - processes[current].arrive - processes[current].burst;
        }
        // If List Has Processes Not Enqueued Yet
        else
        {
            cout << time << " ~ " << time + 1 << endl;
            time++;
        }

        // Enqueue The Processes That Arrived During quantum Period
        for (int i = enqueued; i < size; i++)
            if (list[i].arrive <= time)
            {
                myQueue.enqueue(i);
                enqueued++;
            }

        // If The Current Processes Not Finished
        if (list[current].burst > 0)
            myQueue.enqueue(current);
    }

    return totalWaitTime;
}

int main(int argc, char const *argv[])
{
    Process processes[] = {{1, 0, 1, 3}, {2, 3, 8, 4}, {3, 4, 5, 2}, {4, 5, 2, 2}, {5, 8, 4, 1}};

    int totalWaitTime = 0;
    totalWaitTime = RoundRobin(processes, 5, 3);
    cout << "Total Waiting Time = " << totalWaitTime;

    getchar();
    return 0;
}
