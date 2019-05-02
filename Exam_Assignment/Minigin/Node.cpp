#include "MiniginPCH.h"
#include "Node.h"

void Node::AddConnection(const std::shared_ptr<Node>& t)
{
	const std::shared_ptr<Connection> c = std::make_shared<Connection>(std::make_shared<Node>(*this), t);
	m_Connection.push_back(c);
}

void Node::ResetCost()
{
	for (auto pC : m_Connection)
		pC->ResetCosts();
}
