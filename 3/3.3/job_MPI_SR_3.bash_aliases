#!/bin/bash -l
#SBATCH --time=00:20:00
#SBATCH --mem-per-cpu=1GB
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH --output=MPI_SR_3.out
####For temporary user accounts, comment out this line.
#SBATCH -p courses
#SBATCH -A courses
####

module load gcc/9.2.0
module load openmpi/3.1.4

mpicc -o SR3 MPI_SR_3.c

time srun SR3