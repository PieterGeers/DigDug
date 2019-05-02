#pragma once
#include "Structs.h"
#include "Connection.h"

class Node
{
public:
	Node(MVector2_INT pos) : m_Position(pos){}
	~Node() = default;

	const MVector2_INT& GetPosition() const { return m_Position; }
	bool IsWalkable() const { return m_IsWalkable; }
	void SetWalkable(bool state) { m_IsWalkable = state; }
	void AddConnection(const std::shared_ptr<Node>& t);
	std::vector<std::shared_ptr<Connection>> GetConnection() const { return m_Connection; }
	void ResetCost();

private:
	MVector2_INT m_Position;
	bool m_IsWalkable = false;
	std::vector<std::shared_ptr<Connection>> m_Connection;
};

