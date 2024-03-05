#include <iostream>

using namespace std;

#define FRAMES_NUMBER 3

int Optimal(int pages[], int size)
{
    // 0) Initialize Frames With '-1'
    int frames[FRAMES_NUMBER];
    for (int i = 0; i < FRAMES_NUMBER; i++)
        frames[i] = -1;

    int paeFaults = 0; // Count The Page Faults

    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {

        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < FRAMES_NUMBER; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] << endl;
                break;
            }

        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < FRAMES_NUMBER; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;

                    // Printing
                    cout << pages[pageIndex] << "\t\t";
                    for (int f = 0; f < FRAMES_NUMBER; f++)
                        cout << frames[f] << "\t";
                    cout << endl;

                    break;
                }

            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                // Init Array To Store The Next Index For Each Page In The Frames
                int nextUse[FRAMES_NUMBER];
                for (int i = 0; i < FRAMES_NUMBER; i++)
                    nextUse[i] = size + 1;

                // Assign Next Index For Each Page In The Frames
                for (int i = 0; i < FRAMES_NUMBER; i++)
                    for (int p = pageIndex; p < size; p++)
                        if (pages[p] == frames[i])
                        {
                            nextUse[i] = p;
                            break;
                        }

                // Find The Victim Frame (With The Highest Index)
                int victim = 0;
                for (int i = 0; i < FRAMES_NUMBER; i++)
                    if (nextUse[i] > nextUse[victim])
                        victim = i;

                frames[victim] = pages[pageIndex];
                paeFaults++;

                // Printing
                cout << pages[pageIndex] << "\t\t";
                for (int f = 0; f < FRAMES_NUMBER; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    return paeFaults;
}

int main(int argc, char const *argv[])
{
    int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 2, 6, 7, 3, 2};

    cout << "Number Of Page Faults = " << Optimal(pages, 13);

    getchar();
    return 0;
}