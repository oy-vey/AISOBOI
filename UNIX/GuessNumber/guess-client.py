import socket
import struct
import sys

if len(sys.argv) != 2:
    print "Usage: Python guess-client.py [PATH TO SOCKET]"
    sys.exit(1);

SOCKET_PATH = sys.argv[1]
lb = 1
ub = 1000000000

try:
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    sock.connect(SOCKET_PATH)
    res = ''
    while True:
        i = lb + ((ub - lb) / 2)
        msg = struct.pack(">I", i)
        sock.send(msg)
        res = sock.recv(1)
        if res == '>':
            lb = i
        elif res == '<':
            ub = i
        else:
            break
    sys.stdout.write(str(i))
    sys.stdout.write('\n')
    sock.close()
except:
    sock.close()
    sys.exit(1)

