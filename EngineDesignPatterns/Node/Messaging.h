#pragma once

#include "Node.h"
#include <memory>

#include "../DCS/DCS.h"


struct NMessagingData
{
	size_t m_ID;
	std::vector<std::shared_ptr<NDataContainer>> m_MessageQueue;	// Important for receiving data
	std::vector<std::shared_ptr<Node>> m_Connections;	// Important for sending data
};


class MessagingSystem
{
public:
	void Connect(std::shared_ptr<NMessagingData> node, std::vector<std::shared_ptr<NMessagingData>> m_Connections)
	{
		m_Connections.push_back(node);
	};


	void Detach(std::shared_ptr<NMessagingData> node, std::vector<std::shared_ptr<NMessagingData>> m_Connections)
	{
		for (size_t i = 0; i < m_Connections.size(); i++)
		{
			if (m_Connections.at(i)->m_ID == node->m_ID)
				m_Connections.erase(m_Connections.begin() + i);
		}
	}


	void Send(Data data, MessagingSystem& target)
	{
		target.Receive(data);
	}


	void Receive(Data data)
	{
		// Do x
	}
};