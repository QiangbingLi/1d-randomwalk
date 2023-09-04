# A GUI to simulate and visualize 1d random walk 

Tested to work with QT6 in Ubuntu22.0.4


## install QT6 if not yet installed
$ sudo apt install qt6-base-dev

## install opengl library
$ sudo apt install libgl-dev

## Build it.
$ qmake6 -project

$ qmake6 randomwalk.pro

$ make

## Run it.
$ ./randomwalk

## screenshots of unbiased and biased run

![unbiased](https://github.com/QiangbingLi/1d-randomwalk/blob/main/captures/Capture.PNG "unbiased")
![biased](https://github.com/QiangbingLi/1d-randomwalk/blob/main/captures/Capture-biased.PNG "biased")
