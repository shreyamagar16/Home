#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// ---- helper: prints CPU Utilization & Throughput ----
void printUtilStats(int ct[], int bt[], int n)
{
    int totalTime = 0;
    float totalBT = 0;

    for(int i=0;i<n;i++)
    {
        if(ct[i] > totalTime) totalTime = ct[i];
        totalBT += bt[i];
    }

    if(totalTime == 0) totalTime = 1; // avoid divide by zero

    cout << "CPU Utilization = " << (totalBT/totalTime)*100 << "%\n";
    cout << "Throughput = " << (float)n/totalTime << " processes per unit time\n";
}

// ---- helper: validates AT/BT input ----
bool validAtBt(int at, int bt)
{
    if(at < 0 || bt <= 0)
    {
        cout << "Invalid input! AT must be >= 0 and BT must be > 0. Re-enter.\n";
        return false;
    }
    return true;
}

void fcfs()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], ct[20], tat[20], wt[20], pid[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];

        if(!validAtBt(at[i], bt[i])) { i--; continue; }

        pid[i] = i+1;
    }

    // sort by arrival time so FCFS actually runs in arrival order
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++)
            if(at[j] > at[j+1])
            {
                swap(at[j], at[j+1]);
                swap(bt[j], bt[j+1]);
                swap(pid[j], pid[j+1]);
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

        cout << "P" << pid[i] << "\t" << at[i] << "\t" << bt[i]
             << "\t" << ct[i] << "\t" << tat[i]
             << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage WT = " << avgwt/n;
    cout << "\nAverage TAT = " << avgtat/n << "\n";
    printUtilStats(ct, bt, n);
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

        if(!validAtBt(at[i], bt[i])) { i--; continue; }
    }

    int currentTime = 0;
    int done = 0;

    while(done < n)
    {
        int idx = -1;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && at[i] <= currentTime)
            {
                // tie-break: shorter BT wins, then earlier AT, then lower index
                if(idx == -1 || bt[i] < bt[idx] ||
                  (bt[i] == bt[idx] && at[i] < at[idx]))
                {
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
    printUtilStats(ct, bt, n);
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

        if(!validAtBt(at[i], bt[i])) { i--; continue; }

        rt[i] = bt[i];
    }

    int complete = 0;
    int time = 0;

    while(complete < n)
    {
        int idx = -1;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                // tie-break: shorter remaining time wins, then earlier AT
                if(idx == -1 || rt[i] < rt[idx] ||
                  (rt[i] == rt[idx] && at[i] < at[idx]))
                {
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
    printUtilStats(ct, bt, n);
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

        if(!validAtBt(at[i], bt[i]) || pr[i] < 0)
        {
            if(pr[i] < 0) cout << "Invalid input! Priority must be >= 0. Re-enter.\n";
            i--; continue;
        }
    }

    int done = 0;
    int time = 0;

    while(done < n)
    {
        int idx = -1;

        for(int i=0;i<n;i++)
        {
            if(!completed[i] && at[i] <= time)
            {
                // tie-break: lower priority number wins, then earlier AT
                if(idx == -1 || pr[i] < pr[idx] ||
                  (pr[i] == pr[idx] && at[i] < at[idx]))
                {
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
    printUtilStats(ct, bt, n);
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

        if(!validAtBt(at[i], bt[i]) || pr[i] < 0)
        {
            if(pr[i] < 0) cout << "Invalid input! Priority must be >= 0. Re-enter.\n";
            i--; continue;
        }

        rt[i] = bt[i];
    }

    int complete = 0;
    int time = 0;

    while(complete < n)
    {
        int idx = -1;

        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                // tie-break: lower priority number wins, then earlier AT
                if(idx == -1 || pr[i] < pr[idx] ||
                  (pr[i] == pr[idx] && at[i] < at[idx]))
                {
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
    printUtilStats(ct, bt, n);
}

void roundRobin()
{
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20];

    for(int i=0;i<n;i++)
    {
        cout << "AT BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];

        if(!validAtBt(at[i], bt[i])) { i--; continue; }

        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;
    if(tq <= 0)
    {
        cout << "Invalid Time Quantum! Must be > 0. Defaulting to 1.\n";
        tq = 1;
    }

    // arrival order: indices sorted by AT (stable -> ties keep lower index first)
    int order[20];
    for(int i=0;i<n;i++) order[i] = i;

    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++)
            if(at[order[j]] > at[order[j+1]])
                swap(order[j], order[j+1]);

    queue<int> q;
    int time = 0, complete = 0, ptr = 0;

    // push processes that have already arrived at time 0
    while(ptr < n && at[order[ptr]] <= time)
        q.push(order[ptr++]);

    while(complete < n)
    {
        if(q.empty())
        {
            time = at[order[ptr]]; // CPU idle -> jump to next arrival
            while(ptr < n && at[order[ptr]] <= time)
                q.push(order[ptr++]);
        }

        int cur = q.front();
        q.pop();

        int run = min(tq, rt[cur]);
        rt[cur] -= run;
        time += run;

        // new arrivals during this run join the queue before cur is re-queued
        while(ptr < n && at[order[ptr]] <= time)
            q.push(order[ptr++]);

        if(rt[cur] > 0)
            q.push(cur);
        else
        {
            ct[cur] = time;
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
    printUtilStats(ct, bt, n);
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
            case 1: fcfs(); break;
            case 2: sjf_non_preemptive(); break;
            case 3: sjf_preemptive(); break;
            case 4: priority_non_preemptive(); break;
            case 5: priority_preemptive(); break;
            case 6: roundRobin(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice\n";
        }

    } while(choice != 7);

    return 0;
}