#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "class_structures.hpp"
#include "CdataStore.h"
#include "stdafx.h"


typedef void(__cdecl* tSelectUnit)(int64 guid);
//typedef void(__thiscall* SendPacket)(int curConnection, CDataStore* data);
typedef BOOL(__thiscall* ClickToMove)(GameObject* me, int moveType, int* interactGuid, Vec3* clickPos, float precision);
typedef int(*ToggleAutorun)();

class Hacks
{
private:
	Base* wow_base;
	ObjectManager* objManager;
	Statics* statics = 0x0;
	float oldWallvalue = 0;
public:
	Hacks();
	void listGameObjects();
	GameObject* getLocalPlayer();
	GameObject* getObjectFromGuid(int guid);
	int getCurrentConnection() { return wow_base->currentConnection; }
	void printLocalPlayer();
	void teleport(Vec3 position);
	void toggleWallclimb();
	void setMovementSpeed(float speed);
	void sendCustomPacket(CDataStore* data);
	void sendSpellPacket(int id);
	void sendSpellPacket(int spell, int guid);
	ToggleAutorun func_toggleAutorun = (ToggleAutorun)(0x513D50);
	ClickToMove func_c2m = (ClickToMove)(0x611130);
	void __cdecl hooked_SendPacket(int curConnection, CDataStore* data);
	void activateHooks();
	void detachHooks();
	void togglePrintPackets();
	bool getPrintingPackets();
};

class Core
{
private:
	void input();
	void handleCommands(std::string command);
	
public:
	Hacks* hacks;
	void update();
	Core();
	void init();
	bool shouldExit = false;
	static void debugPrint(std::string str);
	static void print(std::string str);
	static void errorPrint(std::string str);
};