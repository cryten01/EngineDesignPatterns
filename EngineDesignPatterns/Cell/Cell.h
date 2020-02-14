//#pragma once
//
//#include <vector>
//#include <iostream>
//
//
//struct NodeData 
//{
//	int type;
//	int value;
//	bool active;
//};
//
//class Node
//{
//public:
//	Node() = default;
//	virtual ~Node() = default;
//
//	virtual void Connect(Node& node)
//	{
//		Connections.push_back(&node);
//	}
//
//	virtual void Send(NodeData data)
//	{
//		for (auto connection : Connections)
//		{
//			connection->OnReceive(data);
//		}
//	}
//
//	virtual void OnReceive(NodeData data) = 0;
//
//public:
//	std::vector<Node*> Connections;
//	NodeData Data;
//};
//
//
//
//class TransformNode : public Node
//{
//public:
//	 TransformNode() = default;
//	~TransformNode() = default;
//
//	/**
//	 *	Behavior based on incoming data
//	 */
//	void OnReceive(NodeData data) override
//	{
//		if (data.type == 0)
//			std::cout << "TransformNode received message with active : " << data.active << std::endl;
//
//		Send(data);
//	};
//
//
//	void ModifyPosition() 
//	{
//	
//	}
//};
//
//
//class MaterialNode : public Node
//{
//public:
//	 MaterialNode() = default;
//	~MaterialNode() = default;
//
//	void OnReceive(NodeData data) override
//	{
//		std::cout << "MaterialNode received message with value : " << data.value << std::endl;
//	};
//};
