# Process Scheduling Simulation

A simple C program implementing First Come First Served (FCFS) and
non-preemptive Shortest Job First (SJF).

## Compile and run (Linux or macOS)

Open a terminal in this folder and run:

```sh
cc -std=c11 -Wall -Wextra scheduler.c -o scheduler
./scheduler
```

Enter the number of processes, then each process's arrival and burst time.
PIDs are assigned in input order, starting at 1. The program accepts 1–100
processes, arrival times of 0–1,000,000, and burst times of 1–1,000,000.
These limits keep all time calculations within the integer range.

## Algorithms and code

The `Process` structure stores the PID, arrival time, burst time, waiting
time, turnaround time, and response time.

- `fcfs()` copies the input and uses a simple bubble sort by arrival time.
Equal arrival times keep their input order. Each process runs to completion.
- `sjf()` copies the input and repeatedly selects the shortest unfinished
process that has already arrived. Equal bursts are resolved by earlier
arrival, then input order. A `done` array records completed processes.
If no process is ready, time jumps to the next arrival and selection repeats.
- `execute()` calculates the metrics, prints the execution interval, and
returns the completion time. CPU idle intervals appear in the chart.
- `print_results()` prints each process's metrics and their averages.
- `main()` reads and checks input, then calls both scheduling functions.

Each algorithm uses its own copy of the input. FCFS prints table rows in
execution order; SJF prints them in PID order. Both charts show execution order.
Both algorithms take O(n²) time and O(n) additional space.

## Time calculations

- Waiting time = start time − arrival time.
- Turnaround time = completion time − arrival time = waiting time + burst time.
- Response time = first start time − arrival time.

Both algorithms are non-preemptive, so waiting time and response time are equal.
AT = arrival time, BT = burst time, WT = waiting time,
TAT = turnaround time, RT = response time.

## Sample run

Input:

```text
4
0 8
1 4
2 9
3 5
```

Expected execution:

```text
FCFS: | P1 [0-8] | P2 [8-12] | P3 [12-21] | P4 [21-26] |
SJF:  | P1 [0-8] | P2 [8-12] | P4 [12-17] | P3 [17-26] |
```


| Algorithm | Average WT | Average TAT | Average RT |
| --------- | ---------- | ----------- | ---------- |
| FCFS      | 8.75       | 15.25       | 8.75       |
| SJF       | 7.75       | 14.25       | 7.75       |


The assignment's SJF sample chart contains an error: it places P2 first,
although only P1 has arrived at time 0. Its table and averages agree with
the correct order P1, P2, P4, P3 implemented here.

## Edge-case examples

Same arrival time and equal bursts:

```text
3
0 5
0 2
0 2
```

FCFS order: P1, P2, P3. SJF order: P2, P3, P1.

Idle CPU and unsorted arrival times:

```text
3
10 2
2 3
10 1
```

Both algorithms idle from 0 to 2 and from 5 to 10.  
FCFS order: P2, P1, P3. SJF order: P2, P3, P1.

