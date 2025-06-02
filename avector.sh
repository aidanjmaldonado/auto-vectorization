#!/bin/bash

#SBATCH -p instruction
#SBATCH -J avector
#SBATCH -e avector.err
#SBATCH -o avector.out
#SBATCH -N 1
#SBATCH -n 8
#SBATCH -t 00:05:00

module load papi/6.0.0

./avector