# DES Algorithm

Implementation of DES algorithm in C++.

**What is DES Algorithm?**

Data Encryption Standard (DES) is a block cipher algorithm that takes plain text in blocks of 64 bits and converts them to ciphertext using keys of 48 bits. It is a symmetric key algorithm, which means that the same key is used for encrypting and decrypting ​data. Encryption and decryption using the DES algorithm.

## Table of Contents

- [DES Algorithm](#des-algorithm)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Group Details](#group-details)

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
-v, --version        Display program version info and exit.
-f, --file TEXT      Takes a file as an input.
-o, --output TEXT    Writes the output to the specified file.
-e, --encrypt-mode   Runs in encrypt mode.
-d, --decrypt-mode   Runs in decrypt mode.
--help, -h           show help
```

Encrypt Text
```bash
./DES -f=../input.txt -o=./output.txt -e
```

```bash
./DES -f=./output.txt -o=./decrypted.txt -d
```


## Group Details
1905642 - Sounak Mukherjee <br>
1905658 - Aditya Meharia <br>
1905667 - Sagnik Chaudhuri <br>
1905674 - Debmalya Chatterjee <br>
1905725 - Ujjwal Singh Shekhawat <br>
1905726 - Rohan Kumar <br>
1905828 - Pratyush Khuntia <br>
1905831 - Junaid Rahim <br>

Submitted to Prof. Chittaranjan Pradhan