FROM ubuntu:22.04

RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y \
    autoconf \
    automake \
    build-essential \
    cmake \
    gdb \
    git \
    clang \
    iproute2 \
    libnl-3-dev \
    libnl-genl-3-dev \
    libnl-route-3-dev \
    libtool \
    make \
    netcat-openbsd \
    pkg-config \
    strace \
    tcpdump \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app



CMD ["bash"]
