#include "MiniginPCH.h"
#include "Connection.h"

Connection::Connection(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node>& targetNode)
	:m_pStartNode(startNode)
	, m_pTargetNode(targetNode)
{
}