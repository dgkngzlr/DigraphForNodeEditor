#pragma once
#include <assert.h>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

// Directed Acyclic Graph implementation
template<typename T>
class Digraph {
private:

	struct DigraphNode {

		int Id;
		std::vector<int> Neighbors;

		const T& Data;

		DigraphNode() : Data(T()) {}

		DigraphNode(int id, const T& data) : Id(id), Data(data) {}
	};

	struct DigraphEdge {

		int Id;
		int From;
		int To;

		DigraphEdge(int id, int from, int to) : Id(id), From(from), To(to) {}
	};

public:

	Digraph();

	int AddNode(const T& data);

	void DeleteNode(int node_id);

	int AddEdge(int from_node_id, int to_node_id);

	void DeleteEdge(int edge_id);

	std::vector<int> Topsort();

	std::vector<int> Neighbors(int node_id);

	const T& Get(int node_id);

private:

	int m_NextId = 0;
	std::unordered_map<int, DigraphNode> m_Nodes;
	std::unordered_map<int, DigraphEdge> m_Edges;
};

template<typename T>
inline Digraph<T>::Digraph() {

}

template<typename T>
inline int Digraph<T>::AddNode(const T& data) {
	DigraphNode node(m_NextId, data);
	m_Nodes.emplace(std::make_pair(m_NextId, node));
	m_NextId++;
	return node.Id;
}

template<typename T>
inline void Digraph<T>::DeleteNode(int node_id) {
	typename std::unordered_map<int, DigraphNode>::iterator node_iter = m_Nodes.find(node_id);

	if (node_iter != m_Nodes.end()) {
		
		// Delete it from neighbors list
		for (auto& pair : m_Nodes) {
			std::vector<int>::iterator i =
				std::find_if(pair.second.Neighbors.begin(), pair.second.Neighbors.end(), [node_id](auto& id) -> bool {
				return id == node_id;
				});
			if (i != pair.second.Neighbors.end()) {
				pair.second.Neighbors.erase(i);
			}
		}

		// Delete it from edges
		typename std::unordered_map<int, DigraphEdge>::iterator edge_iter =
			std::find_if(m_Edges.begin(), m_Edges.end(), [node_id](const std::pair<int, DigraphEdge>& pair) -> bool {
				return pair.second.From == node_id || pair.second.To == node_id;
				});

		while (edge_iter != m_Edges.end()) {
			m_Edges.erase(edge_iter);

		    edge_iter =
				std::find_if(m_Edges.begin(), m_Edges.end(), [node_id](const std::pair<int, DigraphEdge>& pair) -> bool {
				return pair.second.From == node_id || pair.second.To == node_id;
				});
		}
	
		// Delete itself
		m_Nodes.erase(node_iter);
	}
}

template<typename T>
inline int Digraph<T>::AddEdge(int from_node_id, int to_node_id) {
	
	typename std::unordered_map<int, DigraphNode>::iterator from_iter = m_Nodes.find(from_node_id);
	typename std::unordered_map<int, DigraphNode>::iterator to_iter = m_Nodes.find(to_node_id);

	if (from_iter != m_Nodes.end() && to_iter != m_Nodes.end()) {
		from_iter->second.Neighbors.push_back(to_node_id);

		int edge_id = m_NextId;
		int from_id = from_node_id;
		int to_id = to_node_id;

		DigraphEdge edge(edge_id, from_id, to_id);
		m_Edges.emplace(std::make_pair(m_NextId, edge));
		m_NextId++;

		return edge.Id;
	}

	// At least one of nodes does not exist
	assert("At least one of nodes does not exist" && false);
}

template<typename T>
inline void Digraph<T>::DeleteEdge(int edge_id) {

	typename std::unordered_map<int, DigraphEdge>::iterator edge_iter = m_Edges.find(edge_id);

	if (edge_iter != m_Edges.end()) {

		std::vector<int>& from_neighbors = m_Nodes[edge_iter->second.From].Neighbors;

		auto erased = std::find(from_neighbors.begin(), from_neighbors.end(), edge_iter->second.To);
		if (erased != from_neighbors.end()) {
			from_neighbors.erase(erased);
		}

		m_Edges.erase(edge_iter);
	}
}

template<typename T>
inline std::vector<int> Digraph<T>::Topsort() {

	std::vector<int> result;
	std::queue<int> nodes_with_no_incomig_edges;

	// Map to keep track of in-degrees for each node
	std::unordered_map<int, int> in_degree;

	// Calculate in-degrees for each node
	for (const auto& node_pair : m_Nodes) {
		int node_id = node_pair.first;
		in_degree[node_id] = 0;
	}

	for (const auto& edge_pair : m_Edges) {
		int to_node = edge_pair.second.To;
		in_degree[to_node]++;
	}

	// Enqueue nodes with in-degree of 0
	for (const auto& in_degree_pair : in_degree) {
		if (in_degree_pair.second == 0) {
			nodes_with_no_incomig_edges.push(in_degree_pair.first);
		}
	}

	while (!nodes_with_no_incomig_edges.empty()) {
		int current_node = nodes_with_no_incomig_edges.front();
		nodes_with_no_incomig_edges.pop();

		result.push_back(current_node);

		for (int neighbor : Neighbors(current_node)) {
			// Decrease the in-degree of the neighbor
			in_degree[neighbor]--;

			// If the in-degree becomes 0, enqueue the neighbor
			if (in_degree[neighbor] == 0) {
				nodes_with_no_incomig_edges.push(neighbor);
			}
		}
	}

	// If the result size is not equal to the number of nodes, there is a cycle
	if (result.size() != m_Nodes.size()) {
		
		assert("The graph contains a cycle" && false);
	}

	return result;
}

template<typename T>
inline std::vector<int> Digraph<T>::Neighbors(int node_id) {
	
	typename std::unordered_map<int, DigraphNode>::iterator node_iter = m_Nodes.find(node_id);

	if (node_iter != m_Nodes.end()) {
		return node_iter->second.Neighbors;
	}

	assert("Node does not exist" && false);
}

template<typename T>
inline const T& Digraph<T>::Get(int node_id) {
	typename std::unordered_map<int, DigraphNode>::iterator node_iter = m_Nodes.find(node_id);

	if (node_iter != m_Nodes.end()) {
		return std::ref(node_iter->second.Data);
	}

	assert("Node does not exist" && false);
}