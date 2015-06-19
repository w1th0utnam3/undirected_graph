/*
	Main testing file for the undirected_graph
    Copyright (C) 2015  Fabian Löschner

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include <string>

#include "../source/undirected_graph.h"
#include "../source/undirected_pair.h"
#include "../source/graph_search_iterator.h"

int main()
{
	typedef undirected_graph<std::string, size_t, double, undirected_pair<size_t>> graph_type;
	graph_type graph;
	std::string string1("Hello World!");
	std::string string2("Testing some graphing.");
	std::string string3("Another node.");

	std::cout << "-Initial fill-" << std::endl;
	graph.insert_vertex(1, string1);
	graph.insert_vertex(2, string2);
	graph.insert_vertex(3, string3);

	for(auto it = graph.begin_vertices(); it != graph.end_vertices(); ++it) {
		std::cout << "Node " << it->first
				 << "with value: " << it->second << std::endl;
	}

	graph.insert_edge(1, 2, 44.12);
	graph.insert_edge(2, 3, 22.34);
	graph.insert_edge(3, 1, -111.21);

	for(auto it = graph.begin_edges(); it != graph.end_edges(); ++it) {
		std::cout << "Connection " << it->first.a << " to " << it->first.b << " with value: " << it->second << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "-BTS-" << std::endl;
	breadth_first_iterator<graph_type> bts(graph, graph.begin_vertices());
	while(!bts.end()) {
		auto it = bts.next();
		std::cout << it->first << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "-Erase vertex 2-" << std::endl;
	graph.erase_vertex(2);

	for(auto it = graph.begin_edges(); it != graph.end_edges(); ++it) {
		std::cout << " Connection " << it->first.a << " to " << it->first.b << " with value: " << it->second << std::endl;
	}

	graph.insert_vertex(4, string2);
	graph.insert_edge(1,4, 3521);
	graph.insert_edge(3,4, 787435);

	std::cout << "" << std::endl;
	std::cout << "-Add edges-" << std::endl;
	for(auto it = graph.begin_edges(); it != graph.end_edges(); ++it) {
		std::cout << "Connection " << it->first.a << " to " << it->first.b << " with value: " << it->second << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "-Erase edge 4,1-" << std::endl;
	graph.erase_edge(graph_type::make_edge_id(4,1));

	for(auto it = graph.begin_edges(); it != graph.end_edges(); ++it) {
		std::cout << " Connection " << it->first.a << " to " << it->first.b << " with value: " << it->second << std::endl;
	}

	std::cout << "" << std::endl;
	std::cout << "-Value at edge 1,3-" << std::endl;
	std::cout << graph.at_edge(graph_type::make_edge_id(1,3)) << std::endl;

	return 0;
}
