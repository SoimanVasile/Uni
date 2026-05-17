#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

// Helper function to check if a number contains the digit 7
bool has_7(int n) {
    while (n > 0) {
        if (n % 10 == 7) return true;
        n /= 10;
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N < 2) {
        fprintf(stderr, "N must be at least 2\n");
        return 1;
    }

    // Create an array of N pipes to form the ring
    int pipes[N][2];
    for (int i = 0; i < N; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            return 1;
        }
    }

    // Spawn N children
    for (int i = 0; i < N; i++) {
        if (fork() == 0) {
            // CHILD PROCESS i
            
            // 1. Close ALL pipe ends except the two this child needs.
            // Child i reads from pipe i, and writes to pipe (i+1)%N.
            for (int j = 0; j < N; j++) {
                if (j != i) close(pipes[j][0]); 
                if (j != (i + 1) % N) close(pipes[j][1]);
            }

            int read_fd = pipes[i][0];
            int write_fd = pipes[(i + 1) % N][1];

            // Seed random generator uniquely for each process
            srand(time(NULL) ^ getpid()); 

            int num;
            // 2. Read loop. If the previous process exits, read() returns 0 (EOF) and the loop breaks.
            while (read(read_fd, &num, sizeof(int)) > 0) {
                num++; // Increment the number
                
                bool should_boltz = (num % 7 == 0 || has_7(num));
                
                if (should_boltz) {
                    if (rand() % 3 == 0) {
                        // 1/3 chance to FAIL
                        printf("Process %d: %d (FAILED! Should be boltz. Game Over.)\n", i + 1, num);
                        break; // Break the loop to terminate
                    } else {
                        // SUCCESS
                        printf("Process %d: boltz\n", i + 1);
                    }
                } else {
                    printf("Process %d: %d\n", i + 1, num);
                }

                // Add a small delay so the output is readable
                usleep(50000); 

                // Send the number to the next process
                write(write_fd, &num, sizeof(int));
            }

            // 3. Clean up and exit. 
            // Closing the write_fd triggers the EOF cascade for the next process.
            close(read_fd);
            close(write_fd);
            exit(0);
        }
    }

    // PARENT PROCESS
    
    // 1. Kickstart the game by sending '0' to the first process (which will increment it to 1)
    int start_val = 0;
    write(pipes[0][1], &start_val, sizeof(int));

    // 2. The parent MUST close all its copies of the pipe descriptors.
    // If the parent leaves write ends open, the EOF cascade will fail!
    for (int i = 0; i < N; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // 3. Wait for all N children to finish
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    return 0;
}
