// gpio_toggle.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define STATUS_FILE "status.txt"
#define PID_FILE "pid.txt"

void write_status(const char* status) {
    FILE* f = fopen(STATUS_FILE, "w");
    if (f) {
        fprintf(f, "%s\n", status);
        fclose(f);
    }
}

void write_pid(pid_t pid) {
    FILE* f = fopen(PID_FILE, "w");
    if (f) {
        fprintf(f, "%d\n", pid);
        fclose(f);
    }
}

pid_t read_pid() {
    FILE* f = fopen(PID_FILE, "r");
    if (!f) return -1;
    pid_t pid;
    fscanf(f, "%d", &pid);
    fclose(f);
    return pid;
}

void start_toggle() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        write_pid(getpid());
        for (int i = 0; i < 10; i++) {
            write_status("ON");
            printf("ON\n");
            sleep(1);
            write_status("OFF");
            printf("OFF\n");
            sleep(1);
        }
        write_status("IDLE");
        remove(PID_FILE);
        exit(0);
    } else {
        printf("Toggling started (PID: %d)\n", pid);
    }
}

void stop_toggle() {
    pid_t pid = read_pid();
    if (pid <= 0) {
        printf("No toggle process running.\n");
        return;
    }
    if (kill(pid, SIGTERM) == 0) {
        printf("Toggle process stopped.\n");
        write_status("IDLE");
        remove(PID_FILE);
    } else {
        perror("Failed to stop process");
    }
}

void check_status() {
    FILE* f = fopen(STATUS_FILE, "r");
    if (f) {
        char status[10];
        fgets(status, sizeof(status), f);
        printf("Current status: %s", status);
        fclose(f);
    } else {
        printf("Current status: IDLE\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [start|stop|status]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        start_toggle();
    } else if (strcmp(argv[1], "stop") == 0) {
        stop_toggle();
    } else if (strcmp(argv[1], "status") == 0) {
        check_status();
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
