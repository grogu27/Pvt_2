all: ring one_to_all all_to_one all_to_all

ring: ./Ring/1.c
	mpicc -Wall -o ./Ring/ring.mpi ./Ring/1.c

one_to_all: ./One_to_all/1.c
	mpicc -Wall -o ./One_to_all/one_to_all ./One_to_all/1.c

all_to_one: ./All_to_one/1.c
	mpicc -Wall -o ./All_to_one/all_to_one ./All_to_one/1.c

all_to_all: ./All_to_all/1.c
	mpicc -Wall -o ./All_to_all/all_to_all ./All_to_all/1.c

clean:
	rm -rf ./Ring/ring ./One_to_all/one_to_all ./All_to_one/one_to_all.mpi ./All_to_all/all_to_all.mpi

clean_res:
	rm -rf *.out

graph:
	gnuplot graph/ring.gp && gnuplot graph/one_to_all && gnuplot graph/all_to_one && && gnuplot graph/all_to_all