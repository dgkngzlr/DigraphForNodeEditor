#include "nodes.h"

#include <assert.h>

#include <iostream>

void ScalarInt::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::OutputInt) {
			((OutputIntNode*)node)->Value = Value;
		}
	}
}

void ScalarFloat::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::OutputFloat) {
			((OutputFloatNode*)node)->Value = Value;
		}
	}
}

void DisplayInt::Propagate(const std::vector<INode*>& neighbors) {
	assert(neighbors.size() == 0);
	std::cout << "[DISPLAY_SINK]\t" << Value << std::endl;
}

void DisplayFloat::Propagate(const std::vector<INode*>& neighbors) {
	assert(neighbors.size() == 0);
	std::cout << "[DISPLAY_SINK]\t" << Value << std::endl;
}

void InputIntNode::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::Operational) {
			OperationType operation = ((IOperationNode*)node)->Operation;

			switch (operation)
			{
			case OperationType::DisplayInt:
				((DisplayInt*)node)->Value = Value;
				break;
			case OperationType::AddInt:
				if (Label == "AddInput1") {
					((AddInt*)node)->Value1 = Value;
				}
				else if (Label == "AddInput2") {
					((AddInt*)node)->Value2 = Value;
				}
				break;
			default:
				break;
			}
		}
	}
}

void InputFloatNode::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::Operational) {
			OperationType operation = ((IOperationNode*)node)->Operation;

			switch (operation)
			{
			case OperationType::DisplayFloat:
				((DisplayFloat*)node)->Value = Value;
				break;
			case OperationType::AddFloat:
				if (Label == "AddInput1") {
					((AddFloat*)node)->Value1 = Value;
				}
				else if (Label == "AddInput2") {
					((AddFloat*)node)->Value2 = Value;
				}
				break;
			default:
				break;
			}
		}
	}
}

void OutputIntNode::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::InputInt) {
			((InputIntNode*)node)->Value = Value;
		}
	}
}

void OutputFloatNode::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::InputFloat) {
			((InputFloatNode*)node)->Value = Value;
		}
	}
}

void AddInt::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::OutputInt) {
			((OutputFloatNode*)node)->Value = Value1 + Value2;
		}
	}
}

void AddFloat::Propagate(const std::vector<INode*>& neighbors) {
	for (const auto& node : neighbors) {
		if (node->Type == NodeType::OutputFloat) {
			((OutputFloatNode*)node)->Value = Value1 + Value2;
		}
	}
}
