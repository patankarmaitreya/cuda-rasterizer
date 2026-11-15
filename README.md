# CUDA Rasterizer

A software rasterizer implemented in C++ and CUDA.

The project will first build a correct CPU rasterization pipeline and then port the computationally intensive stages to CUDA. The GPU implementation will be profiled and optimized while using the CPU implementation as a correctness reference.

## Current Status

Sprint 0 complete:

- CUDA 13.5 development environment configured
- CMake-based C++/CUDA build system
- CUDA code isolated behind a plain C++ interface
- Host-to-device and device-to-host memory transfers
- CUDA kernel execution and error handling
- GoogleTest + CTest integration
- Reusable CUDA static library

Current CUDA test operation:

```text
CPU input
    ↓
Host → Device copy
    ↓
CUDA kernel
    ↓
Device → Host copy
    ↓
CPU verification
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/cuda_hello
```

## Test

```bash
ctest --test-dir build --output-on-failure
```

## Tech Stack

- C++17
- CUDA 13.5
- CMake
- GoogleTest
- CTest