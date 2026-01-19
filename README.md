This project has been created as part of the 42 curriculum by pedrferr.

Minitalk
A C program that implements a small client <-> server data exchange using only UNIX signals (SIGUSR1 and SIGUSR2).

Description
Minitalk is a low-level communication project where a client sends a string to a server bit by bit using signals.
The server reconstructs each character from the received bits and prints the message as it arrives (no noticeable delay).

Project Requirements
- Two executables: `server` and `client`
- Server must:
  - Start first
  - Print its PID on launch
  - Receive and print messages from multiple clients in a row (no restart needed)
- Client must:
  - Receive: server PID + string
  - Send the string to the server using only signals
- Allowed signals: SIGUSR1 and SIGUSR2 only
- Performance constraint:
  - Output must feel instantaneous
  - If 100 characters take ~1 second to display, it is considered too slow

How It Works (Signal Protocol)
A common approach is mapping bits to signals:
- SIGUSR1 => bit 0
- SIGUSR2 => bit 1

Server side:
- Keep a running `current_byte` and `bit_index` (0..7)
- For each received signal, set the corresponding bit
- When 8 bits are received, you have a full character:
  - Print it immediately
  - Reset state for the next character
- End-of-message is usually represented by a null terminator (`'\0'`)

Important Note About Reliability
Linux does not queue these signals reliably when many are pending.
For correctness and speed, an ACK-based approach is commonly used:
- Server sends an acknowledgement signal back to the client after receiving each bit (or each byte)
- Client only sends the next bit after receiving the ACK

Allowed Functions (Mandatory)
Typical allowed functions include:
write, signal, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, exit
(+ ft_printf if it is your own implementation)

Usage
Server:
./server
# prints PID, then waits for signals

Client:
./client <server_pid> "your message here"

Makefile
The project includes a Makefile that:
- Compiles with: -Wall -Wextra -Werror using cc
- Provides rules: all, clean, fclean, re
- Avoids unnecessary relinking
- Builds both `client` and `server`

Error Handling
The program should handle invalid inputs robustly, and must not crash.
Typical cases to handle:
- Invalid PID (non-numeric or non-existing process)
- Wrong argument count
- Signal send failure (kill() error)

Bonus (If Mandatory Is Perfect)
- Server sends an ACK to the client after each received message (or per bit/byte)
- Unicode support (extended encoding)

Resources
UNIX signals:
https://man7.org/linux/man-pages/man7/signal.7.html

sigaction:
https://man7.org/linux/man-pages/man2/sigaction.2.html

kill:
https://man7.org/linux/man-pages/man2/kill.2.html

AI Usage
AI tools were used only to help understand the subject, reason about signal-based communication, and review implementation constraints.
All implementation decisions and code were written and fully understood by the author.
