#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

enum class TOKEN
{
	CURLY_OPEN,
	CURLY_CLOSE,
	VEC3,
	COLON,
	STRING,
	NUMBER,
	COMMA,
	SEMICOLON,
	BOOLEAN
};

struct Token
{
	string value;
	TOKEN type;
};

class Tokenizer
{
public:
	Tokenizer(string fileName);
	~Tokenizer();

	char	GetWithoutWhiteSpace();
	Token	GetToken();
	bool	HasMoreTokens();
	void	RollBackToken();


private:

	fstream			m_File;
	size_t          m_PrevPos;



};

