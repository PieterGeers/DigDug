#pragma once
#include "Structs.h"

class Connection;
class Node
{
public:
	Node(MVector2_INT pos) : m_Position(pos){}
	~Node();

	const MVector2_INT& GetPosition() const { return m_Position; }
	bool IsWalkable() const { return m_IsWalkable; }
	void SetWalkable(bool state) { m_IsWalkable = state; }
	void AddConnection(Node* t);
	std::vector<Connection*> GetConnection() const { return m_Connection; }
	void ResetCost();

private:
	MVector2_INT m_Position;
	bool m_IsWalkable = false;
	std::vector<Connection*> m_Connection;
};

