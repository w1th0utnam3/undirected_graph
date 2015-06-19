# undirected_graph
A simple (probably incomplete) implementation of an undirected graph in c++ using the stl.

During my work on a group assignment I needed a graph container to store objects and their connections.
I knew that there is an implementation in the boost library but I wanted to play a little bit with
templates and see how far I can get with it.

The feature set of the container is limited but definitely enough for simple applications. Furthermore my implementation may be quite far from optimal performance because it uses (among others) `std::unordered_map` containers as its
underlying data structures. Again I didn't want to create a perfectly optimized implementation but to
learn and have fun coding. If you have ideas for improvements or find bugs, feel free to notify me about them!

The project is licensed under the GNU GPL v2 license. Have a look into the LICENSE file for more information.

## Quickstart

To start using the `undirect_graph` simply include the `.h` files in your project and instantiate the graph
with the corresponding template arguments:
```c++
template <typename vertex_data_type_arg, typename vertex_id_type_arg, 
		  typename edge_data_type_arg, typename edge_id_type_arg>
class undirected_graph;
```
The `edge_id_type` has to meet certain criteria, for an easy start use the supplied `undirected_pair<T>` where `T`
would be the `vertex_id_type` of the graph.
```c++
template <typename T>
class undirected_pair;
```
Most of the time you can use `int` or `size_t` as the `vertex_id_type` and `undirected_pair<int>` or respectively
`undirected_pair<size_t>` as the `edge_id_type`. If you want to use your own id types (maybe you already have ids
for the objects in your code) make sure to check the requirements some paragraphs below.

## What does it do?

For a full list of features have in look in the documentation which will be added soon.

The graph allows to store vertex data types with unique ids which are connected by edge data objects which
have in turn unique ids. Naturally the graph is implemented using templates and therefore every data type
is supported.

In most operations the graph behaves similar to the `std::map` container because (a) it is built using maps and
(b) it's what you're probably used to after working with stl containers. The only difference is that most methods
have an appended `_vertex` or `_edge` to indicate on which object the method works.

Some example code:
```c++
typedef undirected_graph<std::string, size_t, double, undirected_pair<size_t>> graph_type;
graph_type graph;

graph.insert_vertex(1, "Hello world!");
graph.insert_vertex(2, "Some more text.");
graph.insert_vertex(3, "Hi");

graph.insert_edge(1, 2, 44.12);
graph.insert_edge(2, 3, 22.34);

for(auto it = graph.begin_edges(); it != graph.end_edges(); ++it) {
		std::cout << "Connection" << it->first.a << "to" << it->first.b 
				  << "with value:" << it->second << std::endl;
}

graph.erase_vertex(2);
```
More example code will be added to the repository soon.

## What does this project supply?

The project consist mainly of three parts:
- `undirected_graph` the main component of the graph I've been writing about this whole document.
- `undirected_pair` a simple data type which behaves similar to a `std::pair` except for the fact that it is just
for one data type, pair(a,b) and pair(b,a) compare as equal and it's sortable. The sorting order
is determined by the smaller and bigger elements of the pairs. It's a simple data type to use for the
edge ids in the graph.
- `graph_search_iterator` is an abstract class that provides an interface for graph traversal iterators.
Two subclasses are supplied: a breadth-first and a depth-first iterator.

## Requirements for the data types

There are no requirements or restrictions on the datatypes supplied as `vertex_data_type` or `edge_data_type`.
However there are some requirements for the id types. 

`vertex_id_type` basically has to fulfil the same requirements as for an `unordered_set` and a `std::map`. Namely:
- Equality operator `==`
- Strict weak ordering operator `<`
- Specialized `std::hash` functor (see http://stackoverflow.com/a/17017281/929037)

The same applies to the `edge_id_type` with some more restrictions:
- Additional constructor with the signature `edge_id(vertex_id a, vertex_id b)`
- Equality operator where `edge_id(a,b) == edge_id(b,a)` (this also affects the `<`-operator and hash functor, see below)
- Access to the two connected `vertex_id`s via a public `a` and `b` member

For a datatype that implements all these requirements have a look at the `undirected_pair`. Nevertheless here are the 
axioms for the `<`-operator of the `edge_id_type`: 
```
Let a, b, c, d be of type vertex_id and idA(a,b), idB(c,d) be of type edge_id. Then:
1. min(a,b) < min(c,d) then: (idA < idB)
2. If not 1 and min(c,d) < min(a,b) then: (idB < idA)
3. If not 1 and not 2 and max(a,b) < max(c,d) then: (idA < idB)
4. If not 1 and not 2 and not 3 then: not (idA < idB)
```

## Todo

- Implement `erase` functions with iterator parameter
- Have some ideas how to make it fast by not using `std::map`
