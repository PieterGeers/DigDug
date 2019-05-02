#pragma once

class Node;
class Connection
{
public:
	Connection(const std::shared_ptr<Node>& startNode, const std::shared_ptr<Node>& targetNode);
	~Connection() = default;

	void SetGCost(float g) { m_GCost = g; }
	float GetGCost() const { return m_GCost; }
	void SetHCost(float h) { m_HCost = h; }
	float GetHCost() const { return m_HCost; }
	float GetFCost() const { return m_GCost + m_HCost; }
	void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }

	std::shared_ptr<Node> GetStartNode() const { return m_pStartNode; }
	void SetStartNode(std::shared_ptr<Node> pStartNode) { m_pStartNode = pStartNode; }
	std::shared_ptr<Node> GetEndNode() const { return m_pTargetNode; }
	void SetEndNode(std::shared_ptr<Node> pEndNode) { m_pTargetNode = pEndNode; }
	std::shared_ptr<Connection> GetHeadConnection() const { return m_pHeadConnection; }
	void SetHeadConnection(std::shared_ptr<Connection> pC) { m_pHeadConnection = pC; }


private:
	std::shared_ptr<Node> m_pStartNode;
	std::shared_ptr<Node> m_pTargetNode;
	std::shared_ptr<Connection> m_pHeadConnection;
	float m_GCost = 0.0f;
	float m_HCost = 0.0f;
	float m_FCost = 0.0f;

};

