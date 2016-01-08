# wifi_car
基于arduino+esp8266+l298n+python django DIY的一辆wifi智能小车

<h2>硬件部分</h2>

*  arduino作为主控，esp8266接收控制wifi控制信号，l298n为4个电机作为驱动。

<img src="/images/car.JPG" style="width:200px;height:200px;">

<h2>软件部分</h2>

*  car.ino 文件为小车arduino程序。
*  robot_car 文件为python django web app 文件。
*  上位机控制端利用python 的django框架，搭建了一个web app，通过web的操作，来对小车进行操作。
*  django的运行：<code>python manage.py runserver 0.0.0.0:8000 </code>
*  在django的views.py模块中，将本机搭建为一个 web server，等待小车的连接。
*  在car.ino中，connect server 的ip为运行python django服务的对应ip。

<img src="/images/web.png">

<h2>使用</h2>

*  1.查看本机ip地址。在robot_car/control/views.py 修改本机ip地址，同样在car.ino修改ip地址为本机ip地址。
*  2.在 robot_car 文件中运行:<code>python manage.py runserver 0.0.0.0:8000</code>，开启wifi小车。
*  3.前往浏览器进入127.0.0.1:8000，这时候，服务并没有处于启用状态。重启wifi小车，让小车和django server建立tcp连接。当浏览器刷新出控制界面，则连接成功。
*  4.若不成功，重复操作2/3。
