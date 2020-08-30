#pragma once
#include "CdataStore.h"
#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include "stdafx.h"

class PacketFramework
{
public:
	static const void printDataStore(CDataStore* data)
	{
		byte* buffer;
		buffer = (byte*)data->m_buffer;
		for (int i = 0; i < data->m_size; i++)
		{
			std::cout << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << int(buffer[i]) << " ";
		}
		std::cout << std::endl;
	}
	static const void fillDataStore(std::string str, int start, CDataStore* data)
	{
		std::stringstream converter;
		std::string word;
		std::istringstream ss;
		ss.str(str);
		int count = 0;
		while (ss >> word)
		{
			if (count >= start)
			{
				byte temp = (BYTE)std::stoul(word, nullptr, 16);
				*data << temp;
			}
			count++;
		}
		std::cout << "SENT: "; printDataStore(data);
	}
};