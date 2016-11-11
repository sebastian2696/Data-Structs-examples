import sys, random
from random import randint

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: python gen_graph.py number_of_vertices number_of_edges")
        sys.exit(1)

    vertices = int(sys.argv[1])
    edges = int(sys.argv[2])

    with open('graph-%s.txt' % vertices, 'w') as f:
        for e in range(0,edges):
		src = randint(0,vertices-1)
		while True:
			dst = randint(0,vertices-1)
			if (dst!=src):
				break
            	f.write("%s %s\n" % (src,dst))
