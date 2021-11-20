# NICMEM project
## Introduction
Our project’s aim was to enable the use of NIC memory in the kernel, and utilize it when sending data over TCP. That way, there’s no need to copy the data from the user to the main kernel memory (RAM) before sending it, which achieves better performance.

## Implementation steps and status
1) Add user-kernel API to indicate sending data while utilizing NIC memory. **Completed**
2) Allocate memory for the data on the NIC memory. **Completed**
3) Add kernel-driver API to get pointer to NIC memory and make it available for the kernel. **Partially completed**
4) Copy the data to the NIC memory. **Not completed**
5) Alter the driver to use the NIC memory, by attaching the allocated NIC memory to the data packet (skb) as a memory page. **Not completed**
6) Modify benchmark (netperf, or other) and measure performance. **Not completed**

## Launching prerequisite
In order to use the NIC memory, the machine has to be compiled with the attached kernel sources, which is a modified verison of linux kernel 5.14.0.
Also, both machines used for sending and recieving the data, has to be configured to use the Mellanox NIC as their primary NIC. 
To configure the machine (the following needs to be done on both machines):
Find the Mellanox NIC interface name:
```sh
ip a
```
and then configure it to be the primary NIC:
```sh
ip1=10.0.130.38
ip2=10.0.130.100
if1=SENDER_INTERFACE_NAME # interface name on sender
if2=RECIEVER_INTERFACE_NAME # interface name on reciever
mtu=1500
[SENDER]$ sudo ifconfig $if1 $ip1 netmask 255.255.255.0 mtu $mtu
[RECIEVER]$ sudo ifconfig $if2 $ip2 netmask 255.255.255.0 mtu $mtu
```
## Usage example
Once the launching prerequisites are completed, NIC memory is available when sending data. To use it, simply add a flag, as in the following example, to the socket’s *sendall* method:
```sh
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    flag = int('0x8000000', base=16)
    s.sendall(b"Hello, world", flag)
```
Ready to use scripts are attached in the *nicmem_usage_example* folder. To use them:
1. Edit HOST address in both *echo_server.py* and *echo_client.py*, with both having the same PORT.
2. On the client side (the one that has the project's kernel compiled), run:
```sh
python echo_client.py
```
3. On the server side, run:
```sh
python echo_server.py
```
