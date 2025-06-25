FROM ubuntu:22.04

RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    pkg-config \
    libnl-3-dev \
    libnl-genl-3-dev \
    libtool \
    autoconf \
    automake \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

CMD ["bash"]
