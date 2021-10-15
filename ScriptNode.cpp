#include "ScriptNode.h"

ScriptNode::ScriptNode()
{

}

ScriptNode::ScriptNode(Type t)
{
	m_Type = t;
}

ScriptNode::~ScriptNode()
{

}

void ScriptNode::SetObject(ScriptObject* object)
{
	this->m_Values.object = object;
	m_Type = Type::OBJECT;
}

void ScriptNode::SetString(string* sValue)
{
	this->m_Values.str = sValue;
	m_Type = Type::STRING;
}

void ScriptNode::SetVec3(Vec3 vValue)
{
	this->m_Values.vec3Value = vValue;
	m_Type = Type::VEC3;
}

void ScriptNode::SetBoolean(bool bValue)
{
	this->m_Values.bValue = bValue;
	m_Type = Type::BOOLEAN;
}
