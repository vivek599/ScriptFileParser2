#pragma once

#include "ScriptNode.h"
#include "Tokenizer.h"


class ScriptParser
{
public:

	ScriptParser(const string filename);

	void Parse();


private:
	map<string, ScriptNode*>		m_Root;
	Tokenizer						m_Tokenizer;


	ScriptNode*						ParseObject();
	ScriptNode*						ParseString();
	ScriptNode*						ParseVec3();
	ScriptNode*						ParseBoolean();
	Vec3							ParseVec3Components(string value);
};

