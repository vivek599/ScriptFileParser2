#pragma once


#include <vector>
#include <map>
#include <string>

using namespace std;

class ScriptNode;


struct Vec3
{
	float x, y, z;
};

struct Object
{
	string	ModelFileName;
	string	TextureFileName;
	string	NormalFileName;
	bool	bMovable;
	Vec3	Position;
	Vec3	Rotation;
	Vec3	Scale;
};

using ScriptObject = map<string, ScriptNode*>;

class ScriptNode
{
	enum class Type { OBJECT, STRING, VEC3, BOOLEAN };

	union Values
	{
		ScriptObject* object;
		string* str;
		Vec3 vec3Value;
		bool bValue;
	} m_Values;

	Type m_Type;

public:
	ScriptNode();
	ScriptNode(Type t);
	~ScriptNode();


	void SetObject(ScriptObject* object);
	void SetString(string* sValue);
	void SetVec3(Vec3 vValue);
	void SetBoolean(bool bValue);
};

