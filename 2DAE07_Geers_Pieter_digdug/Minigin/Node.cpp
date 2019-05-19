#include "MiniginPCH.h"
#include "Node.h"
#include "Connection.h"

Node::~Node()
{
	for (auto c : m_Connection)
		delete c;
}

void Node::AddConnection(Node* t)
{
	Connection* c = new Connection(this, t);
	m_Connection.push_back(c);
}

void Node::ResetCost()
{
	for (auto pC : m_Connection)
		pC->ResetCosts();
}
