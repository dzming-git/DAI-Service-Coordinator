FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && \
    apt install -y \
        git \
        gcc \
        g++ \
        gdb \
        cmake \
        make \
        build-essential \
        wget \
        unzip \
        net-tools \
        && \
    apt purge -y --auto-remove

CMD ["echo", "140.82.114.4", "github.com", ">>", "/etc/hosts"]

# 安装gRPC

ENV GRPC_VERSION='1.58.1'

RUN \
    cd / && \
    git clone https://github.com/grpc/grpc  && \
    cd /grpc && \
    git checkout v${GRPC_VERSION} && \
    git submodule update --init && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake ../.. && \
    make && \
    make install && \
    cd third_party/protobuf/ && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /grpc

# 安装 libhv
# https://github.com/ithewei/libhv

RUN \
    cd / && \
    git clone https://github.com/ithewei/libhv.git  && \
    cd /libhv && \
    ./configure && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /libhv

EXPOSE 5000

COPY . ./workspace
WORKDIR /workspace

# docker build . -t task_coordinator:latest
