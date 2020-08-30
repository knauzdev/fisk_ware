#pragma once

/*
; We make them Global so that every function can access them and Constant so they cannot be changed by the program

;The first 2 are you create you manager from the baseaddress wow
Global Const $ClientConnection = 0x8BF1A8
Global Const $CurMgrOffset = 0x462C
;The next one is to get the address of your first object ONLY
Global Const $FirstObjectOffset = 0xB4
;To cycle through the object you need this offset
Global Const $NextObjectOffset = 0x3C
Global Const $PlayerGUID = 0xB8

;This next one is to find the objects type : 1 to 7
Global Const $GameObjTypeOffset = 0x14
;And this one is to find the objects GUID
Global Const $GameObjGUIDOffset = 0x30
*/
//Generated using ReClass 2013 Mod by CypherPresents

class GameObject;

struct Vec3 {
	float x;
	float y;
	float z;
};

class Descriptors
{
public:
	char filler0[0x40];
	int targetGuid;
};

class GameObject
{
public:
	char _0x0000[8];
	Descriptors* descriptors; //0x0008 
	char _0x000C[8];
	__int32 type; //0x0014 
	char _0x0018[24];
	__int32 guid; //0x0030 
	char _0x0034[8];
	GameObject* nextObject; //0x003C 
	char _0x0040[2424];
	Vec3 position; //0x09B8 
	char _0x09C4[112];
	float movementSpeed; //0x0A34 
	char _0x0A38[520];
};//Size=0x0C40

class ObjectManager
{
public:
	char filler0[0xAC];
	GameObject* firstObject;
};

class Base
{
public:
	//currentConnection 828114
	char filler1[0x741414];
	ObjectManager* objManager;
	char filler0[0xA18];
	int localGuid;
	char filler2[0xE62E0];
	int currentConnection;
};

class Statics
{
public:
	char filler[0x80DFFC];
	float wallClimb;
};

