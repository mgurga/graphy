# graphy
Simple, hackable, and (reasonably) fast redis server implementation in C++ 11.

## Features
- [Mostly](https://github.com/mgurga/graphy/projects/2) compatible with Redis v1.0.0
- Zero dependencies
- Robust library functions in [graphy.h](https://github.com/mgurga/graphy/blob/master/src/graphy.h)
- Unit Tests using googletest
- Custom database storage format

## How to build
You can build graphy using GNU make or [just](https://github.com/casey/just). 
Using just you can pass commands to graphy as soon as the interactive shell starts which makes testing easier.
just is not required to build.

First clone the code and change directory
```
git clone https://github.com/mgurga/graphy
cd graphy
```

Build using GNU make:
```make```

Build using just:
```just```

## Running unit tests
To run tests you must have the [googletest](https://github.com/google/googletest) framework installed and detectable by CMake.
First clone the code and change directory
```
git clone https://github.com/mgurga/graphy
cd graphy
```

Using GNU make:
```make test```

Using just:
```just test```
