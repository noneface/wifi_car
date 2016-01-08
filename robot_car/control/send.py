import socket
import time
# Create your views here.
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind(("192.168.1.104",33333))
sock.listen(5)

while True:
	connection,address = sock.accept()
	print address