# ROS Bazel

## Setup

Install Bazel: https://docs.bazel.build/versions/master/install-ubuntu.html#install-with-installer-ubuntu

Disable ccache if it is installed (temporarily):

```bash
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
```

Run (in separate terms):

```bash
roscore
bazel run //ros/talker
bazel run //ros/listener
```

## Features

The core of ROS C++ works:
- Msg generation
- Srv generation
- roscpp client communication

*Python is not supported*.
