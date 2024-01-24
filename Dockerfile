# Use an official base image with a well-supported version of Ubuntu
FROM ubuntu:20.04

# Set environment variables to avoid user interaction during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies and other utilities
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libtbb-dev \
    libgl1-mesa-dev \
    libxt-dev \
    libxmu-dev \
    tcl-dev \
    tk-dev \
    libfreetype6-dev \
    && rm -rf /var/lib/apt/lists/*


# Define the build directory environment variable
ENV BUILD_DIR=/build/docker/opencascade

# Create the build directory
RUN mkdir -p $BUILD_DIR

# Set the working directory to the build directory
WORKDIR $BUILD_DIR

# Clone OpenCASCADE from the official repository
RUN git clone https://github.com/Open-Cascade-SAS/OCCT.git . --depth=2

# Create a separate directory for the build files
RUN mkdir occt_build

# Change the working directory to the build directory
WORKDIR $BUILD_DIR/occt_build

# Configure the project with CMake
RUN cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -D3RDPARTY_TCL_INCLUDE_DIR="/usr/include/tcl" \
    -D3RDPARTY_TK_INCLUDE_DIR="/usr/include/tk" \
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_ft2build="/usr/include/freetype2" \
    -D3RDPARTY_FREETYPE_INCLUDE_DIR_freetype2="/usr/include/freetype2" \
    ..

# Build the project
RUN make -j$(nproc)

# Install the project
RUN make install


RUN apt-get update && apt-get install -y qtbase5-dev \
qt5-default \
libqt5widgets5 \

# Change the working directory to the root
WORKDIR /

# Command to keep the container running
CMD ["/usr/bin/bash"]
