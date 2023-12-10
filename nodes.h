#pragma once
#include <string>
#include <vector>

enum class NodeType {
	InputInt,
	InputFloat,
	Operational,
	OutputInt,
	OutputFloat
};

enum class OperationType {
	ScalarInt,
	ScalarFloat,
	AddInt,
	AddFloat,
	DisplayInt,
	DisplayFloat,
};

class INode {
public:
	std::string Label;
	NodeType Type;

	INode(std::string label, NodeType type) : Label(label), Type(type) {}

	virtual void Propagate(const std::vector<INode*>& neighbors) = 0;
};

class IOperationNode : public INode {
public:
	OperationType Operation;

	IOperationNode(std::string label, OperationType type) : INode(label, NodeType::Operational), Operation(type) {}

	virtual void Propagate(const std::vector<INode*>& neighbors) = 0;
};


class ScalarInt : public IOperationNode {
public:
	int Value = 0;

	ScalarInt(std::string label, int value) : IOperationNode(label, OperationType::ScalarInt), Value(value) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class ScalarFloat : public IOperationNode {
public:
	float Value = 0.0f;

	ScalarFloat(std::string label, float value) : IOperationNode(label, OperationType::ScalarFloat), Value(value) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class AddInt : public IOperationNode {
public:
	int Value1 = 0;
	int Value2 = 0;

	AddInt(std::string label) : IOperationNode(label, OperationType::AddInt) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class AddFloat : public IOperationNode {
public:
	float Value1 = 0.0f;
	float Value2 = 0.0f;

	AddFloat(std::string label) : IOperationNode(label, OperationType::AddFloat) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class DisplayInt : public IOperationNode {
public:
	int Value = 0;

	DisplayInt(std::string label) : IOperationNode(label, OperationType::DisplayInt) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class DisplayFloat : public IOperationNode {
public:
	float Value = 0.0f;

	DisplayFloat(std::string label) : IOperationNode(label, OperationType::DisplayFloat) {}

	virtual void Propagate(const std::vector<INode*>& neighbors);
};

class InputIntNode : public INode {
public:
	int Value = 0;

	InputIntNode(std::string label) : INode(label, NodeType::InputInt) {}

	void Propagate(const std::vector<INode*>& neighbors);
};

class InputFloatNode : public INode {
public:
	float Value = 0.0f;

	InputFloatNode(std::string label) : INode(label, NodeType::InputFloat) {}

	void Propagate(const std::vector<INode*>& neighbors);
};
class OutputIntNode : public INode {
public:
	int Value = 0;

	OutputIntNode(std::string label) : INode(label, NodeType::OutputInt) {}

	void Propagate(const std::vector<INode*>& neighbors);
};

class OutputFloatNode : public INode {
public:
	float Value = 0.0f;

	OutputFloatNode(std::string label) : INode(label, NodeType::OutputFloat) {}

	void Propagate(const std::vector<INode*>& neighbors);
};
