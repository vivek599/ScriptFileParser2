#include "ScriptParser.h"

ScriptParser::ScriptParser(const string filename) : m_Tokenizer(filename)
{

}

void ScriptParser::Parse()
{
	string key = "";

	while (m_Tokenizer.HasMoreTokens())
	{
		Token token = m_Tokenizer.GetToken();

		if (token.value == "MODEL")
		{
			m_Tokenizer.GetToken();
			string key = "";
			Token nextToken = m_Tokenizer.GetToken();
			key = nextToken.value;

			nextToken = m_Tokenizer.GetToken();
			switch (nextToken.type)
			{
			case TOKEN::CURLY_OPEN:
			{
				ScriptNode* parsedObject = ParseObject();
				m_Root[key] = parsedObject;
				break;
			}
			break;

			case TOKEN::STRING:
			{
				m_Tokenizer.RollBackToken();
				ScriptNode* parsedString = ParseString();

				break;
			}
			break;

			case TOKEN::NUMBER:
			{

			}
			break;

			case TOKEN::BOOLEAN:
			{

			}
			break;
			}



		}

		


	}

}

ScriptNode* ScriptParser::ParseObject()
{
	ScriptNode* node = new ScriptNode();

	ScriptObject* object = new ScriptObject();

	bool hasCompleted = false;

	while (!hasCompleted)
	{
		if (m_Tokenizer.HasMoreTokens())
		{
			Token nextToken = m_Tokenizer.GetToken();
			if (nextToken.type == TOKEN::CURLY_CLOSE)
			{
				hasCompleted = true;
				break;
			}

			string key = nextToken.value;

			m_Tokenizer.GetToken();

			nextToken = m_Tokenizer.GetToken();

			switch (nextToken.type)
			{
				case TOKEN::STRING:
				{
					m_Tokenizer.RollBackToken();
					(*object)[key] = ParseString();
					break;
				}
				break;

				case TOKEN::VEC3:
				{
					m_Tokenizer.RollBackToken();
					(*object)[key] = ParseVec3();
					break;
				}
				break;

				case TOKEN::CURLY_OPEN:
				{
					(*object)[key] = ParseObject();
				}
				break;

				case TOKEN::BOOLEAN:
				{
					m_Tokenizer.RollBackToken();
					(*object)[key] = ParseBoolean();
				}
				break;
			}

			nextToken = m_Tokenizer.GetToken();
			if (nextToken.type == TOKEN::CURLY_CLOSE)
			{
				hasCompleted = true;
				break;
			}
		}
	}

	node->SetObject(object);

	return node;
}

ScriptNode* ScriptParser::ParseString()
{
	ScriptNode* node = new ScriptNode();
	Token token = m_Tokenizer.GetToken();
	string* sValue = new string(token.value);
	node->SetString(sValue);
	return node;
}

ScriptNode* ScriptParser::ParseVec3()
{
	ScriptNode* node = new ScriptNode();
	Token nextToken = m_Tokenizer.GetToken();
	string value = nextToken.value;

	Vec3 vValue = ParseVec3Components(value);

	node->SetVec3(vValue);

	return node;
}

ScriptNode* ScriptParser::ParseBoolean()
{
	ScriptNode* node = new ScriptNode();
	Token nextToken = m_Tokenizer.GetToken();
	node->SetBoolean(nextToken.value == "True" ? true : false);
	return node;
}

Vec3 ScriptParser::ParseVec3Components(string value)
{
	float vals[3];

	stringstream ss(value);
	int i = 0;
	while (ss.good())
	{
		string str;
		getline(ss, str, ',');
		vals[i] = stof(str);
		i++;
	}

	return { vals[0], vals[1], vals[2] };
}
