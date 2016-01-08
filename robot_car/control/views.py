from django.shortcuts import render
from django.http import HttpResponse
import json
import socket
import time
# Create your views here.

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.bind(("192.168.137.1",8888))  #  修改第一个变量 为本机ip地址
sock.listen(1)
connection,address = sock.accept()
print address[0],"robot car connected  OK!"
def index(request):
   return render(request,"control/index.html")

def get_control(request):
	control = request.POST.get("control","")
	if control == "up":
		connection.send("up")
		time.sleep(0.1)
		connection.send("up")
		time.sleep(0.1)
		connection.send("up")
	if control == "down":
		connection.send("down")
		time.sleep(0.1)
		connection.send("down")
		time.sleep(0.1)
		connection.send("down")
	if control == "stop":
		connection.send("stop")
		time.sleep(0.1)
		connection.send("stop")
		time.sleep(0.1)
		connection.send("stop")
	if control == "right":
		connection.send("right")
		time.sleep(0.1)
		connection.send("right")
		time.sleep(0.1)
		connection.send("right")
	if control == "left":
		connection.send("left")
		time.sleep(0.1)
		connection.send("left")
		time.sleep(0.1)
		connection.send("left")
	errors = []
	mydict = {"errors":errors}
	return HttpResponse(json.dumps(mydict),content_type="application/json")
