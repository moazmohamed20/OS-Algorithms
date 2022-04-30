#include <iostream>

using namespace std;

#define PN 5 // Processes Number
#define RN 3 // Resources Number
int p, r;    // For Iterations

// Allocation Table
int allocation[PN][RN] = {
    {0, 2, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};

// Maximum Table
int maximum[PN][RN] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};

// Current Available Numbers Of Each Resource
int available[RN] = {3, 2, 2};

// Need Table
int need[PN][RN];

void calcNeed()
{
    for (p = 0; p < PN; p++)
        for (r = 0; r < RN; r++)
            need[p][r] = maximum[p][r] - allocation[p][r];
}

bool isSystemSafe()
{
    // Calculate Need Table
    calcNeed();

    // Temporary Copy Of: 'available[RN]'
    int tempAvail[RN];
    for (r = 0; r < RN; r++)
        tempAvail[r] = available[r];

    // Array To Mark The Finished Processes With '1'
    int finished[PN] = {0};

    bool hasChanged = false;
    do
    {
        hasChanged = false;
        // Loop Through Processes
        for (p = 0; p < PN; p++)
            // If The Procces Not Executed Before
            if (finished[p] == 0)
            {
                // Check: Is This Process Need Resources More Than The Available?
                for (r = 0; r < RN; r++)
                    if (need[p][r] > tempAvail[r])
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

    // Check: Is There A Process That Not Executed?
    for (p = 0; p < PN; p++)
        if (finished[p] == 0)
        {
            cout << "\nSystem Is UnSafe\n";
            return false;
        }

    cout << "\nSystem Is Safe\n";
    return true;
}

bool allocateIfSafe(int processNo, int request[RN])
{
    // Temporary Copies Of: The Process Original Values From All Tables
    int tempNeed[RN], tempAlloc[RN], tempAvail[RN];
    for (r = 0; r < RN; r++)
    {
        // Store The Original Values
        tempAlloc[r] = allocation[processNo][r];
        tempNeed[r] = need[processNo][r];
        tempAvail[r] = available[r];

        // Change Tables Values
        allocation[processNo][r] += request[r];
        need[processNo][r] -= request[r];
        available[r] -= request[r];
    }

    if (isSystemSafe())
        return true;

    // Restore The Original Values
    for (r = 0; r < RN; r++)
    {
        allocation[processNo][r] = tempAlloc[r];
        need[processNo][r] = tempNeed[r];
        available[r] = tempAvail[r];
    }
    return false;
}

int main(int argc, char const *argv[])
{
    // The Number Of Requested Resources
    int request[RN] = {1, 0, 2};
    if (allocateIfSafe(1, request))
        cout << "The Request Is Accepted\n";
    else
        cout << "The Request Is Rejected\n";

    getchar();
    return 0;
}