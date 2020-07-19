#include <bits/stdc++.h>
using namespace std;
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare_arrival(process &p1, process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}
bool compare_id(process &p1, process &p2)
{
    return p1.pid < p2.pid;
}

int main(int argc, char const *argv[])
{
    int n;
    struct process p[100];
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilization;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int total_waiting_time = 0;
    float throughput;
    float avg_turn_around_time;

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }
    sort(p, p + n, compare_arrival);
    for (int i = 0; i < n; i++)
    {
        p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0) ? p[i].arrival_time : (p[i].start_time - p[i - 1].completion_time);
    }
    avg_turn_around_time = total_turnaround_time / n;
    avg_response_time = total_response_time / n;
    avg_waiting_time = total_waiting_time / n;
    cpu_utilization = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;

    sort(p, p + n, compare_id);

    cout << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t"
         << "\n"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\n";
    }
    cout << "Average Turnaround Time " << avg_turn_around_time << endl;
    cout << "Avg Response Time " << avg_response_time << endl;
    cout << "Avg Waiting Time " << avg_waiting_time << endl;
    cout << "CPU utilization " << cpu_utilization << endl;

    return 0;
}
