from ubuntu:24.04


run apt-get update \
  && apt-get install -y \
    cmake \
    build-essential \
    g++ \
    libcpprest-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

workdir /tmp/pkg
copy . /tmp/pkg/

run rm -rf build
run mkdir build
workdir /tmp/pkg/build
run cmake .. && make install
run ldconfig
run rm -rf /tmp/pkg

workdir /
