#!/bin/bash -l
#SBATCH --time=00:05:00
#SBATCH --mem-per-cpu=500M
#SBATCH --nodes=1
##### This program can only be run with two cores
#SBATCH --ntasks-per-node=2
#SBATCH --output=MPI_SR_2.out
####For temporary user accounts, comment out this line.
#SBATCH -p courses
#SBATCH -A courses
####

module load gcc/9.2.0
module load openmpi/3.1.4

mpicc -o SR2 MPI_SR_2.c

time srun SR2