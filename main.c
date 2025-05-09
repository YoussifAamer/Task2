/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000
#define MAX 5000

// Function to generate random requests
void generateRequests(int requests[]) {
    for (int i = 0; i < SIZE; i++) {
        requests[i] = rand() % MAX;
    }
}

// Function for FCFS
int FCFS(int requests[], int head) {
    int total_movement = 0;
    for (int i = 0; i < SIZE; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
    }
    return total_movement;
}

// Function for SCAN
int SCAN(int requests[], int head) {
    int total_movement = 0;
    int direction = 1; // 1 means moving toward higher numbers
    int i, j;

    // Sort requests
    for (i = 0; i < SIZE-1; i++) {
        for (j = 0; j < SIZE-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }

    // Find where head is
    for (i = 0; i < SIZE; i++) {
        if (requests[i] >= head) {
            break;
        }
    }

    // Move toward the end
    for (j = i; j < SIZE; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
    }

    // Go to the last cylinder if not already there
    if (head != MAX - 1) {
        total_movement += abs((MAX - 1) - head);
        head = MAX - 1;
    }

    // Reverse direction and service the requests on the way back
    for (j = i - 1; j >= 0; j--) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
    }

    return total_movement;
}

// Function for C-SCAN
int CSCAN(int requests[], int head) {
    int total_movement = 0;
    int i, j;

    // Sort requests
    for (i = 0; i < SIZE-1; i++) {
        for (j = 0; j < SIZE-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }

    // Find where head is
    for (i = 0; i < SIZE; i++) {
        if (requests[i] >= head) {
            break;
        }
    }

    // Move toward the end
    for (j = i; j < SIZE; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
    }

    // Jump to beginning (simulate circular movement)
    if (head != MAX - 1) {
        total_movement += abs((MAX - 1) - head);
        head = 0;
        total_movement += MAX - 1;
    } else {
        head = 0;
    }

    // Continue servicing from the start
    for (j = 0; j < i; j++) {
        total_movement += abs(requests[j] - head);
        head = requests[j];
    }

    return total_movement;
}

int main() {
    int requests[SIZE];
    int head;
    
    printf("Enter initial position of disk head (0 - 4999): ");
    scanf("%d", &head);

    generateRequests(requests);

    // Copy of requests for each algorithm
    int requests1[SIZE], requests2[SIZE];
    for (int i = 0; i < SIZE; i++) {
        requests1[i] = requests[i];
        requests2[i] = requests[i];
    }

    printf("Total head movement for FCFS: %d\n", FCFS(requests, head));
    printf("Total head movement for SCAN: %d\n", SCAN(requests1, head));
    printf("Total head movement for C-SCAN: %d\n", CSCAN(requests2, head));

    return 0;
}
