#!/bin/bash
source /u/sw/etc/bash.bashrc
module load gcc-glibc
module load boost
rm main
make clean
make
