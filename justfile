shell: build
    cd build && ./graphy

graphy command: build
    cd build && ./graphy {{command}}

test: build-testing
    cd build/test/ && ./test_graphy

testc command: build-testing
    cd build/test/ && ./test_graphy {{command}}

run command: build
    cd build && ./graphy r {{command}}

drun command: build
    cd build &&   ./graphy rd {{command}}

build:
    #!/usr/bin/env bash
    mkdir -p build
    cd build
    cmake ..
    make -j $(nproc)

build-testing:
    #!/usr/bin/env bash
    mkdir -p build
    cd build
    cmake .. -DBUILD_TESTING=true
    make -j $(nproc)

clean:
    rm -rf build
