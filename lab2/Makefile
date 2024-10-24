all: middle_rectangle_method monte_carlo_method

middle_rectangle_method: Middle_rectangle_method/1.c
	mpicc -Wall -o Middle_rectangle_method/middle_rectangle_method Middle_rectangle_method/1.c -lm

monte_carlo_method:
	mpicc -Wall -o Monte_Carlo_method/monte_carlo_method Monte_Carlo_method/1.c -lm

run_middle_rectangle_method:
	mpiexec -n 4 Middle_rectangle_method/middle_rectangle_method

run_monte_carlo_method:
	mpiexec -n 4 Monte_Carlo_method/monte_carlo_method

clean:
	rm -rf Middle_rectangle_method/middle_rectangle_method Monte_Carlo_method/monte_cartlo_method.mpi 

clean_res:
	rm -rf *.out

graph:
	gnuplot graph/middle_rectangle_method.gp && gnuplot graph/monte_Carlo_method.gp