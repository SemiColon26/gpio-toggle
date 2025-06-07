# GPIO Toggle CLI App

Hello sir,
This is a simple command-line app written in C that simulates GPIO (General Purpose Input/Output) toggling. It was built as part of a task assigned. 

---

##  What This App Does

This tool mimics a basic GPIO toggle operation using the terminal.

You can:

- Start the toggling (prints "ON"/"OFF" every second for 10 seconds)
- Check the current toggle **status** at any time
- Stop the toggling process gracefully (sets status to IDLE)

---

##  How to Build and Run

Open your terminal and **navigate to the project directory**:
--->cd gpio-toggle

The command to compile your program (using gcc) is:

--->gcc -Wall -o gpio-toggle gpio_toggle.c

If you have a Makefile, you can simply run:
--->make
which will run the compile command automatically.

You’ll need two terminals to use the app smoothly:

In Terminal 1:
Command to start toggle:
--->./gpio-toggle start

In Terminal 2: Check status or stop toggling
Check status:
--->./gpio-toggle status

Stop toggling:
--->./gpio-toggle stop

The toggling runs in Terminal 1 and outputs every second.
Use Terminal 2 to send commands without interrupting Terminal 1.
Tested on WSL (Windows Subsystem for Linux).

