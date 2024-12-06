all: prog

prog:
	mpicc -Wall -o prog main.c -lm

run_sgemv:
	mpiexec -n 4 main.c

clean:
	rm -rf prog

clean_res:
	rm -rf *.out

graph_time:
	gnuplot graph/lab4_time.gp

graph_speedup:
	gnuplot graph/lab4_speedup.gp

res_time:
	python3 graph/speedup_1000_time.py &&  python3 graph/speedup_10000_time.py

res_speedup:
	python3 graph/speedup_1000_speedup.py &&  python3 graph/speedup_10000_speedup.py