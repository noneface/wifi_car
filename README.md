# wifi_car
基于arduino+esp8266+l298n+python django DIY的一辆wifi智能小车

<h2>硬件部分</h2>

*  arduino作为主控，esp8266接收控制wifi控制信号，l298n为4个电机作为驱动。

<img src="/images/car.JPG" style="weight:200px;">

<h2>软件部分</h2>
*  上位机控制端利用python 的django框架，搭建了一个web app，通过web的操作，来对小车进行操作。
*  django的运行：<code>python manage.py runserver 0.0.0.0:8000 </code>
*  在django的views.py模块中，将本机搭建为一个 web server，等待小车的连接。
*  在car.ino中，connect server 的ip为运行python django服务的对应ip。

<img src="/images/web.png">
