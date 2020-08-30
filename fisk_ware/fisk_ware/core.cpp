#include "core.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "packets.hpp"

void initConsole()
{
	AllocConsole();
	freopen("conin$", "r+t", stdin);
	freopen("conout$", "w+t", stdout);
	freopen("conout$", "w+t", stderr);
}

void Core::print(std::string str)
{
	std::cout << str << std::endl;
}

void Core::debugPrint(std::string str)
{
	std::cout << "[DEBUG] " << str << std::endl;
}

void Core::errorPrint(std::string str)
{
	std::cout << "[ERROR] " << str << std::endl;
}

Core::Core()
{
	this->hacks = new Hacks();
	init();
}

void Core::input()
{
	std::cout << "[fisk_ware]: ";
	std::string inputLine = "";
	getline(std::cin, inputLine);
	if (!hacks->getPrintingPackets())
		handleCommands(inputLine);
	else
		hacks->togglePrintPackets();
}

void Core::handleCommands(std::string command)
{
	std::istringstream iss(command);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };
	if (command == ".detach")
	{
		Core::print("Exiting...");
		Sleep(100);
		this->shouldExit = true;
	}
	else if (command == ".listobjects")
	{
		hacks->listGameObjects();
	}
	else if (command == ".printlocal")
	{
		hacks->printLocalPlayer();
	}
	else if (command == ".gm")
	{
		hacks->teleport({ 16238.8f, 16262.46f,14.82752f });
	}
	else if (command.find(".go ") != std::string::npos)
	{
		if (tokens.size() < 4)
		{
			Core::errorPrint(".go format: \".go x y z (floats)\"");
		}
		else
		{
			float x = std::stof(tokens[1].c_str());
			float y = std::stof(tokens[2].c_str());
			float z = std::stof(tokens[3].c_str());
			hacks->teleport({ x,y,z });
		}
	}
	else if (command.find(".speed ") != std::string::npos)
	{
		if (tokens.size() < 2 || command.find("help") != std::string::npos)
		{
			Core::errorPrint(".speed format: \".speed value (float)\", walking speed: 7");
		}
		else
		{
			float speed = std::stof(tokens[1].c_str());
			hacks->setMovementSpeed(speed);
		}
	}
	else if (command == ".clear")
	{
		system("cls");
	}
	else if (command.find(".send ") != std::string::npos)
	{
		CDataStore* data = new CDataStore();
		PacketFramework::fillDataStore(command, 1, data);
		hacks->sendCustomPacket(data);
	}
	else if (command == ".hook")
	{
		hacks->activateHooks();
	}
	else if (command == ".printpackets")
	{
		hacks->togglePrintPackets();
	}
	else if (command.find(".cast ") != std::string::npos)
	{
		hacks->sendSpellPacket(std::stoi(tokens[1]));
	}
	else if (command.find(".casttarget ") != std::string::npos)
	{
		hacks->sendSpellPacket(std::stoi(tokens[1]),hacks->getLocalPlayer()->descriptors->targetGuid);
	}
	else if (command.find(".move ") != std::string::npos)
	{
		int interactguid = std::stoi(tokens[1]);
		int type = std::stoi(tokens[2]);
		Vec3 pos = { std::stof(tokens[3]),std::stof(tokens[4]),std::stof(tokens[5]) };
		hacks->func_c2m(hacks->getLocalPlayer(), type, &interactguid, &pos, std::stof(tokens[6].c_str()));
	}
	else if (command == ".wallclimb")
	{
		hacks->toggleWallclimb();
	}
	else
	{
		Core::print("Unknown command.");
	}
}

void Core::update()
{
	while (!shouldExit)
	{
		input();
		Sleep(5);
	}
}

void Core::init()
{
	initConsole();
	print("Succesfully injected.");
	//hacks->printLocalPlayer();
	//shacks.listGameObjects();
}