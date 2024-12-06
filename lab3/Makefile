all: sgemv

sgemv:
	mpicc -Wall -o sgemv SGEMV.c 

run_sgemv:
	mpiexec -n 4 SGEMV.c

clean:
	rm -rf sgemv

clean_res:
	rm -rf *.out

graph_time:
	gnuplot graph/sgemv_time.gp

res_time:
	python3 graph/speedup_28000_time.py &&  python3 graph/speedup_45000_time.py

res_speedup:
	python3 graph/speedup_28000_speedup.py &&  python3 graph/speedup_45000_speedup.py