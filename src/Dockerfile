FROM nvidia/cuda:11.1.1-devel-ubuntu20.04 AS base

LABEL maintainer="Ashley Walker ashley.walker@infarm.io"

ARG DEBIAN_FRONTEND=noninteractive

# Installs the pre-pre-requisites
RUN apt-get update --fix-missing && \
    apt-get upgrade -y && \
    apt-get install --no-install-recommends -y nano git apt-transport-https ca-certificates gnupg software-properties-common wget \
    ninja-build pkg-config build-essential zip curl zip unzip tar zlib1g-dev

# Install the PGP for Cmake and CLang/LLVM
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
# Add the required repositories
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'

RUN apt-get install --no-install-recommends -y cmake 

RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-12 100 && \ 
   update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 100
RUN apt-get install --no-install-recommends -y protobuf-compiler libprotobuf-dev clang
# docker build --target base -t infarm/debayer .
#######################################################################

FROM base as build

ARG DEBIAN_FRONTEND=noninteractive
ARG VCPKG_BUILD_TYPE=release
WORKDIR /Debayer_deps
ARG HOME=/Debayer_deps
WORKDIR /build
WORKDIR /Debayer
COPY ./Debayer .
RUN apt install libpq-dev postgresql-server-dev-all -y
# Install CUVI
RUN bash ./CUVI/install.sh
RUN mkdir build && cd build
# I dont know why,but 2 times is required
RUN cmake -G "Ninja" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="/build/out/install/Linux-Clang-Release" "/Debayer/CMakeLists.txt" -DVCPKG_TARGET_TRIPLET=x64-linux 
RUN cmake -G "Ninja" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="/build/out/install/Linux-Clang-Release" "/Debayer/CMakeLists.txt" -DVCPKG_TARGET_TRIPLET=x64-linux

RUN ninja
RUN bash /Debayer/linking.sh
#RUN cmake -G "Ninja" --configure -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="/build/out/install/Linux-Clang-Release" "/Debayer/CMakeLists.txt"


#RUN mkdir -p /build/out/build/Linux-Clang-Release
#RUN cmake --build /Debayer/ --target debayer 
#RUN mkdir -p /build/out/install/Linux-Clang-Release
#RUN cmake --install "/build/out/install/Linux-Clang-Release" --target debayer
# RUN cd /build/out/build/Linux-Clang-Release/
# RUN cmake --configure
# RUN cmake --build "/build/out/build/Linux-Clang-Release" --target debayer .
# RUN cmake --build .. --target debayer .

# RUN mkdir -p /build/out/install/Linux-Clang-Release/
# RUN cmake --install "/build/out/install/Linux-Clang-Release" --target debayer
# RUN cmake --install .. --target debayer

# docker build --target build -t infarm/debayer .
#######################################################################

# FROM nvidia/cuda:11.1.1-devel-ubuntu20.04 AS runtime

# ARG DEBIAN_FRONTEND=noninteractive

ENTRYPOINT [ "/Debayer/bin/debayer" ]

# docker run -it --gpus 1 -p 50051:50051 -p 50052:50052 --restart=always gundydc.azurecr.io/infarm/debayer:{TAG}