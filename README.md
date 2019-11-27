# Sysbro

A system assistant for deepin/Ubuntu18.10.

![](screenshots/20191116163955.png)

[Downloads](https://github.com/rekols/sysbro/releases)

项目地址：[https://rekols.github.io/sysbro/index.html](https://rekols.github.io/sysbro/index.html)

Gitgee: [https://gitee.com/rekols/sysbro](https://gitee.com/rekols/sysbro)

## Dependencies

* sudo apt install g++ qt5-default qttools5-dev-tools libdtkwidget-dev libsensors4-dev libpci-dev

## Build

* mkdir build
* cd build
* qmake ..
* make

## Build a deb package

* dpkg-buildpackage -b

## License

sysbro is licensed under GPLv3.
