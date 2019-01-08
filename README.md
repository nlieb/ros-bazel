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
- roscpp pub/sub communication

*Python is not supported*.

## IDE Support

Works well with CLion 2018.2.7 and version `2018.12.03.0.2` of the Bazel plugin found [here](https://plugins.jetbrains.com/plugin/9554-bazel). We recommend [Jetbrains Toolbox](https://www.jetbrains.com/toolbox/) for selecting a specific version of CLion.
