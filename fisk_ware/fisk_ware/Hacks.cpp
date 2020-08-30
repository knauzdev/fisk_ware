#include "core.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iomanip>
#include "packets.hpp"

#include "Detours\detours.h"
#include "Detours\detver.h"
#pragma comment (lib, "detours.lib")
typedef void(__thiscall* SendPacket)(int curConnection, CDataStore* data);
SendPacket func_SendPacket = (SendPacket)0x5379A0;

bool printingPackets = false;

Hacks::Hacks()
{
	this->wow_base = (Base*)GetModuleHandle(NULL);
	this->objManager = wow_base->objManager;
}

void __fastcall hooked_SendPacket2(int curConnection,void* unknown, CDataStore* data)
{
	if (printingPackets)
	{
		PacketFramework::printDataStore(data);
	}
	func_SendPacket(curConnection, data);
}

void Hacks::activateHooks()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)func_SendPacket, hooked_SendPacket2);
	DetourAttach(&(PVOID&)func_SendPacket, hooked_SendPacket2);
	DetourTransactionCommit();
	Core::debugPrint("Hooked functions with detours!");
}

void Hacks::detachHooks()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)func_SendPacket, hooked_SendPacket2);
	DetourTransactionCommit();
}

void Hacks::sendCustomPacket(CDataStore* data)
{
	func_SendPacket(wow_base->currentConnection, data);
}

void Hacks::togglePrintPackets()
{
	printingPackets = !printingPackets;
}

bool Hacks::getPrintingPackets()
{
	return printingPackets;
}

void Hacks::listGameObjects()
{
	GameObject* curObj = wow_base->objManager->firstObject;
	int count = 1;
	std::cout << std::hex << "first address: " << (int)curObj;
	while (curObj->type <= 7 && curObj->type > 0)
	{
		std::cout << std::hex << "address: " << (int)curObj;
		std::cout << ", guid: " << std::to_string(curObj->guid);
		Core::print(", type: " + std::to_string(curObj->type) + ", x:" + std::to_string(curObj->position.x) + 
			", y: " + std::to_string(curObj->position.y) +
			", z: " + std::to_string(curObj->position.z));
		curObj = curObj->nextObject;
		count++;
	}
	Core::print("count: " + std::to_string(count));
}

void Hacks::printLocalPlayer()
{
	GameObject* pLocal = this->getLocalPlayer();
	if (pLocal == 0)
	{
		Core::print("Error: could not find local player");
	}
	else
	{
		Core::print("---Local Player info---");
		std::cout << std::hex << "Memory Address: " << (int)pLocal << std::endl;
		Core::print("GUID: " + std::to_string(pLocal->guid));
		Core::print("x: " + std::to_string(pLocal->position.x));
		Core::print("y: " + std::to_string(pLocal->position.y));
		Core::print("z: " + std::to_string(pLocal->position.z));
		Core::print("type: " + std::to_string(pLocal->type));
		Core::print("-----------------------");
	}
}

void Hacks::teleport(Vec3 position)
{
	GameObject* pLocal = this->getLocalPlayer();
	pLocal->position = position;
}

void Hacks::toggleWallclimb()
{
	this->oldWallvalue = statics->wallClimb;
	statics->wallClimb = -0.67f;
}

void Hacks::sendSpellPacket(int id)
{
	int currentConnection = 0xED4C008; //kan breaka?
	CDataStore data;
	unsigned int opcode = CMSG_CAST_SPELL;
	byte sak = 0x07;
	unsigned int guid = 0;
	data << opcode;
	data << id;
	data << (short)0;
	func_SendPacket(getCurrentConnection(), &data);
}

void Hacks::sendSpellPacket(int spell, int guid)
{
	int currentConnection = 0xED4C008; //kan breaka?
	
	for (byte i = 0; i < 10; i++)
	{
		CDataStore data;
		unsigned int opcode = CMSG_CAST_SPELL;
		byte sak = 0x07;
		data << opcode;
		data << spell;
		data << (byte)02;
		data << (byte)00;
		data << (byte)0xDF;
		data << guid;
		data << i;
		data << (short)0xF130;
		PacketFramework::printDataStore(&data);
		func_SendPacket(getCurrentConnection(), &data);
		Sleep(200);
	}
}

void Hacks::setMovementSpeed(float speed)
{
	this->getLocalPlayer()->movementSpeed = speed;
}

GameObject* Hacks::getLocalPlayer()
{
	return getObjectFromGuid(wow_base->localGuid);
}

GameObject* Hacks::getObjectFromGuid(int guid)
{
	ObjectManager* objManager = wow_base->objManager;
	GameObject* curObj = objManager->firstObject;
	while (curObj->type <= 7 && curObj->type > 0)
	{
		if (curObj->guid == wow_base->localGuid)
		{
			return curObj;
		}
		curObj = curObj->nextObject;
	}
	return 0;
}