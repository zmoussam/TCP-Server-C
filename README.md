# TCP_Server
A TCP server listens on a well-known port (or IP address and port pair) and accepts connections from TCP clients. A TCP client initiates a connection request to a TCP server in order to setup a connection with the server. A real TCP server can accept multiple connections on a socket.

<img width="449" alt="Screen Shot 2023-08-05 at 6 00 12 PM" src="https://github.com/zmoussam/TCP_Server_C-/assets/90983110/1978b6ae-3007-4a92-94a7-9c4a3490ea53">

# TCP Server in C++

This repository contains a simple TCP server implemented in C++. The server allows users to send and receive messages from their terminal using a TCP connection. It can serve as a basic foundation for building more complex network applications or for learning about network programming with sockets.

## Prerequisites

Before using the TCP server, make sure you have the following:

- C++ compiler (e.g., g++)
- Basic understanding of networking concepts and C++ programming

## Getting Started

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/zmoussam/TCP_Server_C-
   
2. Navigate to the project directory:
    ```bash
    cd TCP
    
3. Compile the server source code:
   ```bash
   g++ TCP_server.cpp -o server

4. Run the server:
   ```bash
   ./server

## Usage

1. Once the server is running, open another terminal window and use a TCP client (e.g., netcat) to connect to the server:
   Replace 9999 with the port number specified in the server.cpp file.
   ```bash
   nc localhost 9999

2. You can now send and receive messages through the terminal. Type a message and press Enter to send it to the server. The server will display incoming messages on its terminal.

3. To exit, simply close the TCP client terminal and stop the server by pressing Ctrl + C in the terminal where the server is running

## Customization

- You can modify the port number in the server.cpp file to use a different port.
- Extend the server's functionality by adding more features, such as handling multiple clients simultaneously or implementing custom protocols.

## Contributing

Contributions are welcome! If you find any issues or want to add improvements, feel free to open a pull request.
