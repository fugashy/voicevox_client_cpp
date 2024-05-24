from ubuntu:24.04


run apt-get update \
  && apt-get install -y \
    cmake \
    build-essential \
    g++ \
    libcpprest-dev \
  && rm -rf /var/apt/list/*


workdir /tmp/pkg
copy . /tmp/pkg/

run rm -rf build
run mkdir build
workdir /tmp/pkg/build
run cmake .. && make install
run ldconfig
run rm -rf /tmp/pkg

workdir /
