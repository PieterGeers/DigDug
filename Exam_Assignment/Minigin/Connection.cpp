#include "MiniginPCH.h"
#include "Connection.h"
#include "Node.h"

Connection::Connection(Node* startNode, Node* targetNode)
	:m_pStartNode(startNode)
	,m_pTargetNode(targetNode)
{
}