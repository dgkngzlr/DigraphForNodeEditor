#include <iostream>
#include <string>
#include "digraph.h"
#include "nodes.h"

int main() {

	Digraph<INode*> graph;

	// Scalar Block 1
	ScalarFloat scalar_node_1("Scalar", 10.0f);
	OutputFloatNode output_float_1("OutputFloat");
	int nid1 = graph.AddNode(&scalar_node_1);
	int nid2 = graph.AddNode(&output_float_1);
	int eid1 = graph.AddEdge(nid1, nid2);
	// Scalar Block 2
	ScalarFloat scalar_node_2("Scalar", 20.0f);
	OutputFloatNode output_float_2("OutputFloat");
	int nid3 = graph.AddNode(&scalar_node_2);
	int nid4 = graph.AddNode(&output_float_2);
	int eid2 = graph.AddEdge(nid3, nid4);
	// Scalar Block 3
	ScalarFloat scalar_node_3("Scalar", 30.0f);
	OutputFloatNode output_float_3("OutputFloat");
	int nid5 = graph.AddNode(&scalar_node_3);
	int nid6 = graph.AddNode(&output_float_3);
	int eid3 = graph.AddEdge(nid5, nid6);
	// Scalar Block 4
	ScalarFloat scalar_node_4("Scalar", 40.0f);
	OutputFloatNode output_float_4("OutputFloat");
	int nid7 = graph.AddNode(&scalar_node_4);
	int nid8 = graph.AddNode(&output_float_4);
	int eid4 = graph.AddEdge(nid7, nid8);
	// Add Block 1
	InputFloatNode input_float_1("AddInput1");
	InputFloatNode input_float_2("AddInput2");
	AddFloat add_float_1("AddFloat");
	OutputFloatNode output_float_5("OutputFloat");
	int nid9 = graph.AddNode(&input_float_1);
	int nid10 = graph.AddNode(&input_float_2);
	int nid11 = graph.AddNode(&add_float_1);
	int nid12 = graph.AddNode(&output_float_5);
	int eid5 = graph.AddEdge(nid9, nid11);
	int eid6 = graph.AddEdge(nid10, nid11);
	int eid7 = graph.AddEdge(nid11, nid12);
	// Add Block 2
	InputFloatNode input_float_3("AddInput1");
	InputFloatNode input_float_4("AddInput2");
	AddFloat add_float_2("AddFloat");
	OutputFloatNode output_float_6("OutputFloat");
	int nid13 = graph.AddNode(&input_float_3);
	int nid14 = graph.AddNode(&input_float_4);
	int nid15 = graph.AddNode(&add_float_2);
	int nid16 = graph.AddNode(&output_float_6);
	int eid8 = graph.AddEdge(nid13, nid15);
	int eid9 = graph.AddEdge(nid14, nid15);
	int eid10 = graph.AddEdge(nid15, nid16);
	// Add Block 3
	InputFloatNode input_float_5("AddInput1");
	InputFloatNode input_float_6("AddInput2");
	AddFloat add_float_3("AddFloat");
	OutputFloatNode output_float_7("OutputFloat");
	int nid17 = graph.AddNode(&input_float_5);
	int nid18 = graph.AddNode(&input_float_6);
	int nid19 = graph.AddNode(&add_float_3);
	int nid20 = graph.AddNode(&output_float_7);
	int eid11 = graph.AddEdge(nid17, nid19);
	int eid12 = graph.AddEdge(nid18, nid19);
	int eid13 = graph.AddEdge(nid19, nid20);
	// Display Block 1
	InputFloatNode input_float_8("InputFloat");
	DisplayFloat display_float_1("DisplayFloat");
	int nid21 = graph.AddNode(&input_float_8);
	int nid22 = graph.AddNode(&display_float_1);
	int eid14 = graph.AddEdge(nid21, nid22);

	int eid15 = graph.AddEdge(nid2, nid9);
	int eid16 = graph.AddEdge(nid4, nid10);
	int eid17 = graph.AddEdge(nid6, nid13);
	int eid18 = graph.AddEdge(nid8, nid14);
	int eid19 = graph.AddEdge(nid12, nid17);
	int eid20 = graph.AddEdge(nid16, nid18);
	int eid22 = graph.AddEdge(nid20, nid21);

	// Forward propagate
	std::vector<int> top_order = graph.Topsort();
	for (const auto& id : top_order) {
		std::vector<int> neighbors_id = graph.Neighbors(id);
		std::vector<INode*> neighbors;
		for (const auto& elem : neighbors_id) {
			neighbors.push_back(graph.Get(elem));
		}
		graph.Get(id)->Propagate(neighbors);
	}
	return 0;
}