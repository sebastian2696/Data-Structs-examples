# Lab10
This lab is based on Lab09, in addition to the requirements of Lab09, you are also expected to construct the list of all reachable nodes for each node on the graph.

**You are required to use BFS for the implementation. Feel free to add additional data strcture to the code (e.g. Queue) if you need them**

A directed graph consists of vertices that are connected together by edges, where edges have a direction associated with them.

For the example we gave in Lab09:
```
		4
		^
		|
		|
		1 - - > 2 - -> 3
```									

The Reachable node list is:
```
1-> 4,3,2
2-> 3
3-> NULL
4-> NULL
```
**Notice the difference of the reachable node list from the adjacency list!**

The instructions of functions, you are expected to finish, are given along with the code. Please read instructions carefully before you start to code.

We provide several test files for you to check your code. You can also use gen_graph.py to generate new test files. Please run it by using the command like this:
```
python gen_graph.py 5 10,
```
where 5 is the number of vertices, and 10 is the number of edges.

You can also run the provided example binary ``` GraphBFS_full ``` to verify the correctness of your code.
