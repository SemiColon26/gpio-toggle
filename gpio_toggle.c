#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t running = 1;

void handle_sigint(int sig) {
    running = 0;
}

void write_status(const char *status) {
    FILE *fp = fopen("status.txt", "w");
    if (fp) {
        fprintf(fp, "%s\n", status);
        fclose(fp);
    } else {
        perror("Failed to write status");
    }
}

void print_status() {
    FILE *fp = fopen("status.txt", "r");
    char status[10] = "IDLE";
    if (fp) {
        if (fgets(status, sizeof(status), fp)) {
            printf("Current status: %s", status);
        }
        fclose(fp);
    } else {
        printf("Current status: IDLE\n");
    }
}

void start_toggle() {
    signal(SIGINT, handle_sigint);
    for (int i = 0; i < 10 && running; i++) {
        write_status("ON");
        printf("ON\n");
        sleep(1);
        if (!running) break;
        write_status("OFF");
        printf("OFF\n");
        sleep(1);
    }
    write_status("IDLE");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [start|stop|status]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        start_toggle();
    } else if (strcmp(argv[1], "stop") == 0) {
        write_status("IDLE");
        printf("Stopped toggling.\n");
    } else if (strcmp(argv[1], "status") == 0) {
        print_status();
    } else {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
