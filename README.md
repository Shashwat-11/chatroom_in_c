# Chatroom in C

This project implements a chatroom application in C using socket programming and multithreading. The server can handle multiple clients simultaneously, allowing users to send and receive messages in real-time. The server uses threads to manage communication with each connected client.
![A server connected to three clients](picture/pic.png)

## Features

- **Socket Programming**: Implements basic socket communication for client-server interaction.
- **Multithreading**: Uses threads to manage multiple clients concurrently while maintaining fluidity and quick reaction.
- **Real-time Messaging**: Clients can send and receive messages in real-time.
- **Text-based Interface**: A simple terminal-based interface for chat interaction.

## Requirements

- C Compiler (e.g., GCC)
- POSIX compliant operating system (Linux/macOS)
- Thread library (pthread)

## How to run

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/Shashwat-11/chatroom_in_c
2. Use the following command to run the server
   ```bash
   ./server <port>
3. To create and connect clients do following
   ```bash
   ./client <port> <ip>
 4.Leave port and ip empty if using on the same machine

5.To exit a client type exit in chat and to close the server type close in server
