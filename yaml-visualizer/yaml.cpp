#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "yaml.h"

std::string tokenToString(TOKENS type)
{
  switch (type)
  {
  case VALUE:
    return "VALUE";
  case STRING:
    return "STRING";
  case COLON:
    return "COLON";
  case DASH:
    return "DASH";
  }
}

Token::Token(TOKENS type, std::string value, std::string content)
{
  this->type = type;
  this->value = value;
  this->content = content;
}

void Lexer::tokenize(std::string yaml)
{
  this->yaml = yaml;
  while (peek() != '\0')
    scanToken();
  newToken(END, "\0", "\0");
}

void Lexer::newToken(TOKENS type, std::string value, std::string content)
{
  tokens.push_back(Token(type, value, content));
}

char Lexer::peek()
{
  if (current + 1 >= yaml.length())
    return '\0';
  return yaml[current];
}

char Lexer::peekNext()
{
  if (current + 1 >= yaml.length())
    return '\0';
  return yaml[current + 1];
}

char Lexer::advance(char match)
{
  if (current + 1 >= yaml.length())
    return '\0';
  else if (peek() == match)
    return yaml[current++];
  return '\0';
}