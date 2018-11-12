# CollectGame design
**Table of contents**
- [Class diagram](#p1)
- [Algorithms](#p2)


<br><a name="p1"></a> 
# Class diagram
Some relevant details about the class structure :
### State pattern
The node uses a state pattern, as it has different behaviour according to his state and only some transitions possible. Details are in class's comments.

### Why Signal / slots
I used signal and avoided inclusion cycles. That makes the unit tests much easier.

### node <--> item relation
To easily implement the ownership between nodes and items, the relation direction is reversed (In the diagram the node doesn't know which item it has). This way we do not have to manage many different collections of item in each node, and unique ownership is guaranteed  (the same item can't be held by several nodes) without any code.

### Map
The map is modeled thanks to classes: The grid and the graph. The map can access the same nodes through both classes, using X;Y indexes of the grid or vertex / edges relations of the graph.

<br><a name="p2"></a> 
# Algorithms
Here are the two interesting algorithms of the project:

### Map creation algorithm
The algorithm considers that each node has 3 states: absent, existing, candidate to to exist

1. Creation of a XY grid of nodes
2. Insertion of all the nodes in a graph where physically adjacent nodes are linked. e.g. (x=0, y=0) with (x=1, y=0) ...
3. Choice of the first existing node randomly
4. The nodes connected to the chosen node become candidate

5. X time (according to the quantity of existing node wanted):
    - Choose a node randomly among the candidate nodes
    - Make it exist
    - Make the "absent" nodes around this one "candidate"

6. Remove of absent and candidate nodes from the graph, (and edges linked to absent and candidate nodes)

7. X time (according to the wanted quantity of remaining edges):
    - Make a selection of the non-bridge edges (see what's a non-bridge edge hereafter)
    - Choose a non-bridge edge randomly and remove it (if any)


### Non-bridge edges selection algorithm

First what's a bridge? According to Wikipedia, "a bridge is an edge of a graph whose deletion increases its number of connected components".
So I call here a non-bridge an edge of a graph whose deletion does not increase its number of connected components.

Secondly, the algorithm use another concept: the biconnected components. A biconnected-component is a group of vertices in which all vertices are connected at list twice. 

When biconnected_components algorithm is launched in a boost graph, it affects an ID to each biconnected-component, and each edge is tagged with that ID. All the edges with the same ID are in the same biconnected-component. If a biconnected-component has an only edge, that edge is a bridge!

Knowing that the non-bridge edges selection algorithm is:
1. Launch boost's biconnected_components algorithm.
2. Do an Iteration through edges to :  count N= the number of edge of each component  +   save the component ID of each edge.
3. Do another iteration to select edges within the components having N>1.
