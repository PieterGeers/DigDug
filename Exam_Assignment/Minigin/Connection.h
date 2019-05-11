#pragma once

class Node;
class Connection
{
public:
	Connection(Node* startNode, Node* targetNode);
	~Connection() = default;

	void SetGCost(float g) { m_GCost = g; }
	float GetGCost() const { return m_GCost; }
	void SetHCost(float h) { m_HCost = h; }
	float GetHCost() const { return m_HCost; }
	float GetFCost() const { return m_GCost + m_HCost; }
	void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }

	Node* GetStartNode() const { return m_pStartNode; }
	void SetStartNode(Node* pStartNode) { m_pStartNode = pStartNode; }
	Node* GetEndNode() const { return m_pTargetNode; }
	void SetEndNode(Node* pEndNode) { m_pTargetNode = pEndNode; }
	Connection* GetHeadConnection() const { return m_pHeadConnection; }
	void SetHeadConnection(Connection* pC) { m_pHeadConnection = pC; }


private:
	Node* m_pStartNode = nullptr;
	Node* m_pTargetNode = nullptr;
	Connection* m_pHeadConnection = nullptr;
	float m_GCost = 0.0f;
	float m_HCost = 0.0f;
	float m_FCost = 0.0f;

};

