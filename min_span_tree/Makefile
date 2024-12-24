all: prog

prog:
	mpicc -Wall -o prog min_span_tree.c 

run_sgemv:
	mpiexec -n 4 min_span_tree.c

clean:
	rm -rf prog

clean_res:
	rm -rf *.out

graph_time:
	gnuplot graph/lab4_time.gp

graph_speedup:
	gnuplot graph/lab4_speedup.gp

res_time:
	python3 graph/speedup_1000_time.py &&  python3 graph/speedup_3000_time.py &&  python3 graph/speedup_5000_time.py &&  python3 graph/speedup_8000_time.py &&  python3 graph/speedup_10000_time.py

res_speedup:
	python3 graph/speedup_1000_speedup.py &&  python3 graph/speedup_3000_speedup.py &&  python3 graph/speedup_5000_speedup.py &&  python3 graph/speedup_8000_speedup.py &&  python3 graph/speedup_10000_speedup.py
