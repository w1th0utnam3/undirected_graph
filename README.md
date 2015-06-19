# undirected_graph
A simple (probably incomplete) implementation of an undirected graph in c++ using the stl.

During my work on a group assignment I needed a graph container to store objects and their connections.
I knew that there is an implementation in the boost library but I wanted to play a little bit with
templates and see how far I can get with it.

The feature set of the container is limited but definitely enough for simple applications. Furhtermore the
graph might be not as efficient as possible because it uses `std::map` and `std::list` containers as its
underlying data structures. Again I didn't want to create a perfectly optimized implementation but to
learn and have fun coding. If you have ideas for improvements or find bugs, feel free to notfiy me about them!

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
