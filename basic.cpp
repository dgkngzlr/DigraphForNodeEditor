#include <iostream>
#include "digraph.h"

struct Foo {

	int A;

	explicit Foo(int a) : A(a) {}
};

int main() {
	
	Digraph<Foo> graph;

	Foo f1(1);
	Foo f2(2);
	Foo f3(3);

	int nid1 = graph.AddNode(f1);
	int nid2 = graph.AddNode(f2);
	int nid3 = graph.AddNode(f3);

	int eid1 = graph.AddEdge(nid1, nid2);
	int eid2 = graph.AddEdge(nid2, nid3);

	std::cout << &f1 << std::endl;
	std::cout << &(graph.Get(nid1)) << std::endl;
	std::cout << "=================" << std::endl;

	std::cout << &f2 << std::endl;
	std::cout << &(graph.Get(nid2)) << std::endl;
	std::cout << "=================" << std::endl;

	std::cout << &f3 << std::endl;
	std::cout << &(graph.Get(nid3)) << std::endl;
	std::cout << "=================" << std::endl;

	std::vector<int> v = graph.Topsort();
	std::cout << "Top Order : " << std::endl;
	for (auto& id : v) {
		std::cout << id << std::endl;
	}

	return 0;
}