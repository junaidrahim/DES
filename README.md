# DES Algorithm

Implementation of DES algorithm in C++.

**What is DES Algorithm?**

Data Encryption Standard (DES) is a block cipher algorithm that takes plain text in blocks of 64 bits and converts them to ciphertext using keys of 48 bits. It is a symmetric key algorithm, which means that the same key is used for encrypting and decrypting ​data. Encryption and decryption using the DES algorithm.

```
             Plain Text: 1010101111001101111001101010101111001101000100110010010100110110
            Cipher Text: 1001111000100110100111110101101011111010010011011011101101110000
  Decrypted Cipher Text: 1010101111001101111001101010101111001101000100110010010100110110
```

## Table of Contents

- [DES Algorithm](#des-algorithm)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Uninstalling](#uninstalling)

## Installation

1. Clone this repository

```shell
git clone https://github.com/junaidrahim/DES.git
cd DES
git checkout main
```

2. Building the binaries

```sh
mkdir build
cd build
cmake ..
make
```

This will build the `main` binaries in `build` directory.

## Usage


```sh
$ ./DES --help

USAGE:
   ./DES [OPTIONS]

OPTIONS:
   -v, --version        Display program version info and exit.
   -f, --file TEXT      Takes a file as an input.
   -o, --output TEXT    Writes the output to the specified file.
   --help, -h           show help
```
**Input File Format:**
```
Plaintext
```

## Uninstalling


