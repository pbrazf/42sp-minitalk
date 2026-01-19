*This project has been created as part of the 42 curriculum by pedrferr.*

# Minitalk
A small client-server communication program that sends a string using only UNIX signals (SIGUSR1 and SIGUSR2).

## Description
Minitalk is a minimal “message passing” project where two executables communicate without sockets, pipes, or shared memory.

- **server** starts first, prints its PID, and waits for signals.
- **client** takes the server PID and a message, then sends the message bit by bit using only SIGUSR1 and SIGUSR2.
- **server** reconstructs each character from 8 received bits and prints the resulting string.
- An acknowledgment (ACK) mechanism is used to prevent signal loss and keep the transmission fast and reliable.

## Instructions

### Build
```bash
make
```

### Run
Terminal 1:
```bash
./server
```

Terminal 2 (replace `<PID>` with the printed PID):
```bash
./client <PID> "Hello from minitalk"
```

### Expected behavior
- The server prints its PID, then prints the received message.
- The server can receive multiple messages sequentially without restarting.

## Implementation Notes
- Signals represent bits:
  - `SIGUSR1` = 0
  - `SIGUSR2` = 1
- Bits are sent in the order: bit 7 → bit 0.
- The server rebuilds one byte after receiving 8 bits.
- End of message is detected by sending a `\0` byte.
- ACK is used to avoid losing signals under fast sending.

## Resources
- `man signal`
- `man sigaction`
- `man kill`
- `man pause`
- `man usleep`

## AI Usage
I used AI as a learning assistant to:
- clarify how UNIX signals work in practice (handlers, `sigaction`, `SA_SIGINFO`);
- validate the mental model for bit/byte reconstruction and message termination;
- review small code snippets for logic errors and suggest minimal fixes consistent with the 42 Norm.
All core implementation choices and the final code were written and understood by me.