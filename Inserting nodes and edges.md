## Inserting nodes and edges

### Inserting a node:

Write the number of nodes you are going to insert
Any char followed by its X axis and Y axis(default 0)
Example:

``` 
4
A
B
C
D
```

Equals

``` c++
graph1.insertNode('A');
graph1.insertNode('B');
graph1.insertNode('C');
graph1.insertNode('D');
```

### Inserting edges:

Write the number of edges you are going to insert.
Input the origin node, destination node, weight and whether it is directed or not(1 or 0). If you leave the fourth parameter blank, the default is 0.
Example

``` 
4
A B 11
A C 24
A D 1
B D 4
```

Equals

``` c++
graph1.insertEdge('A', 'B', 11);
graph1.insertEdge('A', 'C', 24);
graph1.insertEdge('A', 'D', 1);
graph1.insertEdge('B', 'D', 4);
```

