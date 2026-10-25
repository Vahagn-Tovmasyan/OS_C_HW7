#include <stdio.h>

#define MAX 100

typedef struct {
    int pid, arrival_time, burst_time;
    int waiting_time, turnaround_time, response_time;
} Process;

/* Execute a process and print its Gantt chart segment. */
int execute(Process *p, int time) {
    if (time < p->arrival_time) {
        printf(" Idle [%d-%d] |", time, p->arrival_time);
        time = p->arrival_time;
    }
    p->waiting_time = time - p->arrival_time;
    p->response_time = p->waiting_time;
    p->turnaround_time = p->waiting_time + p->burst_time;
    printf(" P%d [%d-%d] |", p->pid, time, time + p->burst_time);
    return time + p->burst_time;
}

void print_results(Process p[], int n) {
    double wt = 0, tat = 0, rt = 0;
    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid,
               p[i].arrival_time, p[i].burst_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
        wt += p[i].waiting_time;
        tat += p[i].turnaround_time;
        rt += p[i].response_time;
    }
    printf("Average Waiting Time: %.2f\n", wt / n);
    printf("Average Turnaround Time: %.2f\n", tat / n);
    printf("Average Response Time: %.2f\n", rt / n);
}

void fcfs(Process input[], int n) {
    Process p[MAX];
    int time = 0;
    for (int i = 0; i < n; i++) p[i] = input[i];

    /* Stable bubble sort preserves input order for equal arrivals. */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\n=== FCFS ===\nGantt Chart: |");
    for (int i = 0; i < n; i++) time = execute(&p[i], time);
    print_results(p, n);
}

void sjf(Process input[], int n) {
    Process p[MAX];
    int done[MAX] = {0}, time = 0;
    for (int i = 0; i < n; i++) p[i] = input[i];

    printf("\n=== SJF (Non-preemptive) ===\nGantt Chart: |");
    for (int count = 0; count < n; count++) {
        int best = -1, next = -1;
        for (int i = 0; i < n; i++) {
            if (done[i]) continue;
            if (next == -1 || p[i].arrival_time < p[next].arrival_time)
                next = i;
            if (p[i].arrival_time > time) continue;
            if (best == -1 || p[i].burst_time < p[best].burst_time ||
                (p[i].burst_time == p[best].burst_time &&
                 p[i].arrival_time < p[best].arrival_time))
                best = i;
        }
        if (best == -1) {
            printf(" Idle [%d-%d] |", time, p[next].arrival_time);
            time = p[next].arrival_time;
            count--;  /* Select again now that new processes have arrived. */
            continue;
        }
        time = execute(&p[best], time);
        done[best] = 1;
    }
    print_results(p, n);
}

int main(void) {
    Process p[MAX];
    int n;
    printf("Enter number of processes (1-100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid process count.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", p[i].pid);
        if (scanf("%d %d", &p[i].arrival_time, &p[i].burst_time) != 2 ||
            p[i].arrival_time < 0 || p[i].arrival_time > 1000000 ||
            p[i].burst_time < 1 || p[i].burst_time > 1000000) {
            printf("Arrival must be 0-1000000; burst must be 1-1000000.\n");
            return 1;
        }
    }
    fcfs(p, n);
    sjf(p, n);
    return 0;
}
