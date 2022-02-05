shell command: build
    cd build && ./graphy {{command}}

test: build
    cd build && ./graphy test

run command: build
    cd build && ./graphy r {{command}}

drun command: build
    cd build &&   ./graphy rd {{command}}

build:
    #!/usr/bin/env bash
    mkdir -p build
    cd build
    cmake ..
    mold -run make -j $(nproc)

clean:
    rm -rf build
