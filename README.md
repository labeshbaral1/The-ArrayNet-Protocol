# The ArrayNet Protocol

## Responsibilities

This project implements the ArrayNet Protocol, a fictional network protocol designed for transmitting arrays of 32-bit signed integers between two hosts. The core responsibilities of this project include:

- Performing byte-level and bit-level computations to manipulate data within the ArrayNet packet structure.
- Traversing and manipulating arrays of bytes to simulate the sending, receiving, and processing of network packets.
- Ensuring the integrity and correct ordering of transmitted data through checksum verification and fragment offset handling.

## Technologies / C++ Concepts Used

### Language Used
C++

### Key Concepts
- **Data Structures**: Utilization of arrays to model network packets and their payloads.
- **Memory Management**: Dynamic memory allocation and management for packet creation and array reconstruction.
- **Bitwise Operations**: Application of bitwise operators for data manipulation and checksum computation.
- **Algorithm Design**: Design and implementation of algorithms for packet verification, data reconstruction, and packetization of arrays.

## Result

The implementation of the ArrayNet Protocol showcases several features, including:

- **Packet Creation and Analysis**: Ability to construct ArrayNet packets with headers and payloads, as well as to parse and analyze incoming packets.
- **Checksum Verification**: Implementation of a custom checksum algorithm to verify the integrity of received packets and identify corrupted data.
- **Data Reconstruction**: Capability to reconstruct the original array from a set of received packets, handling out-of-order delivery and discarding corrupted packets.
- **Dynamic Packetization**: Efficient packetization of arrays into a sequence of packets, adhering to the specified maximum payload size and other header fields.

### Screenshots and Diagrams
Template of a network chunk

<img width="751" alt="Screenshot 2024-03-26 at 2 16 19 PM" src="https://github.com/labeshbaral1/cse220_hw1/assets/99603007/71b38b69-7789-46ee-b27a-d850dc8106fc">


## How to Use

This section outlines the steps necessary to compile and run the project, demonstrating the functionalities of the ArrayNet Protocol implementation.

### Installation

First, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/yourusername/yourrepository.git
```

### Compilation

Navigate to the project directory where the source code is located. Compile the source code using a C++ compiler, such as g++, with the following command:

```bash
g++ -o arraynet hw1.c -std=c++11
```

This command compiles the hw1.c file into an executable named arraynet. The -std=c++11 option specifies the C++11 standard, which may be necessary for some features used in the project. Adjust the source file name (hw1.c) and the output executable name (arraynet) as needed based on your project structure.


### Running the Program

After successful compilation, run the program by executing the generated executable file. You can do this with the following command:

```bash
./arraynet
```
