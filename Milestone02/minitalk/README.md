*This project has been created as part of the 42 curriculum by nfaronia.*

# 📡 Minitalk

## 🚀 Description
**Minitalk** is a small interprocess communication project that teaches sending messages between processes using **UNIX signals**.

The project consists of:

- A **server** that receives messages
- A **client** that sends messages

The client sends each character **bit by bit** using `SIGUSR1` and `SIGUSR2`, and the server reconstructs the message and prints it to the standard output.

## 🛠️ Instructions

### 🛠️ Compilation
To compile the project, run:
```
make
```
This will generate two executables:
- server
- client

To compile the Bonus, run:
```
make bonus
```
This will generate two executables:
- server_bonus
- client_bonus

Additional Makefile rules:
```
make clean    # remove object files
make fclean   # remove object files and executable
make re       # recompile the project
```

### 💻 Execution
**Server**
```
./server
```
The server will display its PID, which is required by the client.
**Client**
Run the client with the server PID and a message:
```
./client <server_pid> "minitalk!"
```
The client will send the message to the server using UNIX signals.

**🎉 Example Output**
```
📱  MINITALK SERVER BONUS
📡 PID: 19009
✅ Server initialized successfully.
⚠️ NOTE : Press Ctrl+C to exit.
⏳ Waiting for messages...

minitalk
```

### 📡 Communication
```
SIGUSR1 → 0
SIGUSR2 → 1
```
- Each character is sent bit by bit
- The server reconstructs characters and prints the received message

### ✨ Bonus
- Message acknowledgment from the server to the client
- Unicode character support
- Improved error handling

## 📚 Resources

### 📚 References
- 42 minitalk subject
- Unix Signal Documentation
  - man 2 kill – sending signals to processes
  - man 2 sigaction – setting up signal handlers
  - man 7 signal – overview of signals
  - man 2 getpid – retrieve process ID
- [Signal Handling In Linux](https://www.geeksforgeeks.org/linux-unix/signal-handling-in-linux-through-the-signal-function/)

### 🤖 AI Usage

AI tools were used as a learning aid to help find study resources, understand algorithms, and clarify edge cases.

