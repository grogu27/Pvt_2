#float
def memory(w, n):
    return w*(n**2 + 2*n)                      

def memory_distributed(w, count_elem, commsize):
    return w*((count_elem**2)/commsize + 2*count_elem) 

def count_el(mem, w):
    return ((mem/w + 1)**0.5)-1

ram_on_node = 8
count_proc = 1
count_nodes = 1
float = 8
n = 10000
d = memory(float, n)

available_memory = (count_nodes * ram_on_node / count_proc) * 1024*1024*1024 * 0.8
count_elem = count_el(available_memory, float)
distributed = memory_distributed(float, 29307, 1)


print("Size: ", d, "B")
print("Size: ", d / (1024*1024*1024), "GiB")
print("Memory left: ", ram_on_node - (d / (1024*1024*1024)), "GiB")
print("------------------")
print("N: ", count_elem)
print("Size: ", distributed / (1024*1024*1024), "GiB")

#N:  41447        1 node (1 proc on node)
#N:  175850   18 node (1 proc on node)


