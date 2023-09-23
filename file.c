#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void FCFS(struct Process processes[], int n) {
    int completion_time = processes[0].arrival_time;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > completion_time) {
            completion_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = completion_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        completion_time += processes[i].burst_time;
    }

    printf("FCFS Scheduling:\n");
    printf("Process\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void SJF(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    FCFS(processes, n);
}

void PriorityScheduling(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    FCFS(processes, n);
}

void RoundRobin(struct Process processes[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;
    
    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_quantum) {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    remaining_processes--;
                } else {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }
            }
        }
    }

    FCFS(processes, n);
}

int main() {
    int n = 4;
    struct Process processes[n];

    // Initialize processes
    processes[0].id = 1;
    processes[0].arrival_time = 0;
    processes[0].burst_time = 24;
    processes[0].priority = 3;

    processes[1].id = 2;
    processes[1].arrival_time = 4;
    processes[1].burst_time = 3;
    processes[1].priority = 1;

    processes[2].id = 3;
    processes[2].arrival_time = 5;
    processes[2].burst_time = 3;
    processes[2].priority = 4;

    processes[3].id = 4;
    processes[3].arrival_time = 6;
    processes[3].burst_time = 12;
    processes[3].priority = 2;

    // Calculate remaining_time (for Round Robin)
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    FCFS(processes, n);
    printf("\n");
    SJF(processes, n);
    printf("\n");
    PriorityScheduling(processes, n);
    printf("\n");
    RoundRobin(processes, n, 4);

    return 0;
}
