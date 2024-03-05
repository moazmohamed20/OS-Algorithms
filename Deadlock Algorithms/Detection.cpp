#include <iostream>

using namespace std;

#define PN 5 // Processes Number
#define RN 3 // Resources Number
int p, r;    // For Iterations

// Allocation Table
int allocation[PN][RN] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 3},
    {2, 1, 1},
    {0, 0, 2}};

// Request Table
int request[PN][RN] = {
    {0, 0, 0},
    {2, 0, 2},
    {0, 0, 0},
    {1, 0, 0},
    {0, 0, 2}};

// Current Available Numbers Of Each Resource
int available[RN] = {0, 0, 0};

int *detectDeadlocks()
{
    // Temporary Copy Of: 'available[RN]'
    int tempAvail[RN];
    for (r = 0; r < RN; r++)
        tempAvail[r] = available[r];

    // Array To Mark The Finished Processes With '1'
    int *finished = new int[PN];
    for (p = 0; p < PN; p++)
        finished[p] = 0;

    bool hasChanged = false;
    do
    {
        hasChanged = false;
        // Loop Through Processes
        for (p = 0; p < PN; p++)
            // If The Proccess Not Executed Before
            if (finished[p] == 0)
            {
                // Check: Is This Process Request Resources More Than The Available?
                for (r = 0; r < RN; r++)
                    if (request[p][r] > tempAvail[r])
                        break;
                // If It Hasn't
                if (r == RN)
                {
                    finished[p] = 1;
                    cout << "\nP" << p << "\t";
                    for (r = 0; r < RN; r++)
                    {
                        tempAvail[r] += allocation[p][r];
                        cout << tempAvail[r] << "\t";
                    }
                    hasChanged = true;
                }
            }
    } while (hasChanged);

    return finished;
}

int main(int argc, char const *argv[])
{
    int *deadlocks = detectDeadlocks();

    cout << "\nDeadlocks At: ";
    for (p = 0; p < PN; p++)
        if (deadlocks[p] == 0)
            cout << "P" << p << "\t";

    getchar();
    return 0;
}