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
#include <cassert>

#include "../source/undirected_graph.h"
#include "../source/undirected_pair.h"
#include "../source/graph_search_iterator.h"

int run_test() {
	typedef undirected_graph<std::string, size_t, double, undirected_pair<size_t>> graph_type;
	graph_type graph;

	const int n = 1000;

	std::vector<std::string> strings;
	strings.reserve(n);

	std::cout << "Inserting " << std::to_string(n) << " values... ";
	for(int i = 0; i < n; i++) {
		std::string string(std::to_string(std::sqrt(i)));
		strings.push_back(string);
		graph.insert_vertex(i, string);
	}
	std::cout << "ok. " << std::endl;

	std::cout << "Checking inserted values... ";
	for(int i = 0; i < n; i++) {
		assert(graph.at_vertex(i).compare(strings.at(i)) == 0);
	}
	std::cout << "ok." << std::endl;

	return 0;
}

int main()
{
	return run_test();
}
