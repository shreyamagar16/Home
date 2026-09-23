#include <iostream>
using namespace std;

void fcfs()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], ct[20], tat[20], wt[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];
    }

    ct[0] = at[0] + bt[0];

    for(int i=1;i<n;i++)
    {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i]
             << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

void sjf_non_preemptive()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], ct[20], tat[20], wt[20];
    bool completed[20] = {0};

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];
    }

    int currentTime = 0;
    int done = 0;

    while(done < n)
    {
        int idx = -1;
        int minBT = 9999;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && at[i] <= currentTime)
            {
                if(bt[i] < minBT)
                {
                    minBT = bt[i];
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            currentTime++;
            continue;
        }

        currentTime += bt[idx];
        ct[idx] = currentTime;

        completed[idx] = true;
        done++;
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i]
             << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

void sjf_preemptive()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    int complete = 0;
    int time = 0;

    while(complete < n)
    {
        int idx = -1;
        int minRT = 9999;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0 && rt[i] < minRT)
            {
                minRT = rt[i];
                idx = i;
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if(rt[idx] == 0)
        {
            ct[idx] = time;
            complete++;
        }
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i]
             << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

void priority_non_preemptive()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], pr[20];
    int ct[20], tat[20], wt[20];
    bool completed[20] = {0};

    for(int i=0;i<n;i++)
    {
        cout << "AT BT Priority for P" << i+1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
    }

    int done = 0;
    int time = 0;

    while(done < n)
    {
        int idx = -1;
        int best = 9999;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && at[i] <= time)
            {
                if(pr[i] < best)
                {
                    best = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        time += bt[idx];
        ct[idx] = time;

        completed[idx] = true;
        done++;
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << pr[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

void priority_preemptive()
{
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], pr[20];
    int rt[20], ct[20], tat[20], wt[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT Priority for P" << i+1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        rt[i] = bt[i];
    }

    int complete = 0;
    int time = 0;

    while(complete < n)
    {
        int idx = -1;
        int best = 9999;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(pr[i] < best)
                {
                    best = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if(rt[idx] == 0)
        {
            ct[idx] = time;
            complete++;
        }
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << pr[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

void roundRobin()
{
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], rt[20];
    int ct[20], tat[20], wt[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];

        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int complete = 0;
    int time = 0;

    while(complete < n)
    {
        bool executed = false;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                executed = true;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;

                    ct[i] = time;
                    complete++;
                }
            }
        }

        if(!executed)
            time++;
    }

    float avgwt=0,avgtat=0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgtat += tat[i];

        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i]
             << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== CPU Scheduling Algorithms =====\n";
        cout << "1. FCFS\n";
        cout << "2. SJF Non-Preemptive\n";
        cout << "3. SJF Preemptive (SRTF)\n";
        cout << "4. Priority Non-Preemptive\n";
        cout << "5. Priority Preemptive\n";
        cout << "6. Round Robin\n";
        cout << "7. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                fcfs();
                break;

            case 2:
                sjf_non_preemptive();
                break;

            case 3:
                sjf_preemptive();
                break;

            case 4:
                priority_non_preemptive();
                break;

            case 5:
                priority_preemptive();
                break;

            case 6:
                roundRobin();
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid Choice\n";
        }

    } while(choice != 7);

    return 0;
}