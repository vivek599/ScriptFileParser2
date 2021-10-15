#include "Tokenizer.h"

Tokenizer::Tokenizer(string fileName) : m_PrevPos(0)
{
	m_File.open(fileName, ios::in);
	if (!m_File.good())
	{
		cout << "File open error" << endl;
	}
}

Tokenizer::~Tokenizer()
{

}

char Tokenizer::GetWithoutWhiteSpace()
{
	char c = ' ';
	while ((c == ' ' || c == '\n' || c == '\t'))
	{
		m_File.get(c); 

		//if ((c == ' ' || c == '\n') && !m_File.good())
		//{ 
		//	throw logic_error("Ran out of tokens");
		//}
		//else 
		if (!m_File.good())
		{
			return c;
		}
	}

	return c;
}

Token Tokenizer::GetToken()
{
	// string buf;
	char c;
	if (m_File.eof())
	{
		cout << "Exhausted tokens" << endl;
	}

	m_PrevPos = m_File.tellg();

	c = GetWithoutWhiteSpace();

	//cout << c << endl;

	Token token;

	if (c == '"')
	{
		token.type = TOKEN::STRING;
		token.value = "";
		m_File.get(c);
		while (c != '"')
		{
			token.value += c;
			m_File.get(c);
		}
	}
	else if (c == ';')
	{
		token.type = TOKEN::SEMICOLON;
	}
	else if (c == '(')
	{
		token.type = TOKEN::VEC3;
		token.value = "";
		m_File.get(c);
		while (c != ')')
		{
			token.value += c;
			m_File.get(c);
		}
	}
	else if (c == '{')
	{
		token.type = TOKEN::CURLY_OPEN;
	}
	else if (c == '}')
	{
		token.type = TOKEN::CURLY_CLOSE;
	}
	else if (c == '-' || (c >= '0' && c <= '9'))
	{
		//Check if string is numeric
		token.type = TOKEN::NUMBER;
		token.value = "";
		token.value += c;
		streampos prevCharPos = m_File.tellg();
		while ((c == '-') || (c >= '0' && c <= '9') || c == '.')
		{
			prevCharPos = m_File.tellg();
			m_File.get(c);

			if (m_File.eof())
			{
				break;
			}
			else
			{
				if ((c == '-') || (c >= '0' && c <= '9') || (c == '.'))
				{
					token.value += c;
				}
				else
				{
					m_File.seekg(prevCharPos);
				}
			}
		}
	}
	else if (tolower(c) == 'f') 
	{
		token.type = TOKEN::BOOLEAN;
		token.value = "False";
		m_File.seekg(4, ios_base::cur);
	}
	else if (tolower(c) == 't')
	{
		token.type = TOKEN::BOOLEAN;
		token.value = "True";
		m_File.seekg(3, ios_base::cur);
	}
	else if (c == ':')
	{
		token.type = TOKEN::COLON;
	}
	else if (c == ',')
	{
		token.type = TOKEN::COMMA;
	}
	else if (c == ';')
	{
		token.type = TOKEN::SEMICOLON;
	}

	return token;
}

bool Tokenizer::HasMoreTokens()
{
	return !m_File.eof();
}

void Tokenizer::RollBackToken()
{
	if (m_File.eof())
	{
		m_File.clear();
	}
	m_File.seekg(m_PrevPos);
}
