#!/usr/bin/env python3

import socket

HOST = "10.0.130.100"  # Receiver's IP address
PORT = 2000  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    flag = int('0x8000000', base=16)
    s.sendall(b"Hello, world", flag)
    data = s.recv(1024)

print("Received", repr(data))
