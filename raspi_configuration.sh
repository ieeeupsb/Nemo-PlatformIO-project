#! /bin/bash

git clone https://github.com/ieeeupsb/Nemo.git

#Numpy
sudo apt install python3-numpy

# OpenCV
dev libatlas-base-dev gfortran libhdf5-dev libhdf5-serial-dev libhdf5-103 python3-pyqt5 python3-dev -y
pip install -U numpy
pip install opencv-python==4.5.3.56

#matplotlib
sudo apt install python3-matplotlib python3-tk

# install pandas
pip install pandas

