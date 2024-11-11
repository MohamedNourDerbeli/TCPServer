# Simple TCP Server

A basic TCP server in C that listens on a specified port and handles client connections. The server responds with a simple "httpd v1.0" message.

## Features

- Listens for incoming TCP connections on port 8181.
- Accepts connections from clients.
- Reads data from the client and sends a fixed response: "httpd v1.0".
- Gracefully shuts down the server when interrupted with `Ctrl + C`.

## Requirements

- A C compiler (e.g., GCC).
- Linux or any Unix-like OS.

## Usage

1. Clone the repository or copy the `tcpser.c` file.
2. Compile the server code:
    ```bash
    gcc tcpser.c -o tcpser
    ```
3. Run the server:
    ```bash
    ./tcpser
    ```
   The server will start listening on port 8181 for incoming connections.

4. You can test the server with a tool like `telnet`:
    ```bash
    telnet localhost 8181
    ```

5. To stop the server, press `Ctrl + C`.
