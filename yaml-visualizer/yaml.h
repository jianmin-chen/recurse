#ifndef YAML_H
#define YAML_H

#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

enum TOKENS
{
  VALUE,
  STRING,
  COLON,
  DASH,
  END
};

std::string tokenToString(TOKENS type);

class Token
{
public:
  TOKENS type;
  std::string value;
  std::string content;

  Token(TOKENS type, std::string value, std::string content);

  friend std::ostream &operator<<(std::ostream &os, const Token &token)
  {
    os << "{ \"type\": \"" << tokenToString(token.type) << "\", \"value\": \"" << token.value << "\" }";
    return os;
  }
};

class Lexer
{
public:
  std::vector<Token> tokens;
  std::string yaml;

  void tokenize(std::string yaml);

private:
  int current = 0;

  void newToken(TOKENS type, std::string value, std::string content);

  char peek();
  char peekNext();

  char advance(char match)
  {
    if (current + 1 >= yaml.length())
      return '\0';
    else if (peek() == match)
      return yaml[current++];
    return '\0';
  }

  bool identifier(char chr)
  {
    if (isalpha(chr) || chr == '_' || chr == ' ')
      return true;
    return false;
  }

  void scanToken()
  {
    char curr = advance(peek());
    std::cout << curr << std::endl;
    switch (curr)
    {
    case ':':
      newToken(COLON, std::string(1, curr), NULL);
    case '-':
      newToken(DASH, std::string("-"), std::string("-"));
    case '#':
      // Comment
      while (peek() != '\n')
        current++;
    case ' ':
    case '\n':
      break;
    default:
      if (identifier(curr))
      {
        // // Generic value
        // std::string value(1, curr);
        // while (identifier(peek()))
        //   value.push_back(advance(peek()));
        // newToken(VALUE, value, value);
        std::cout << curr << std::endl;
      }
    }
  }
};

class YAML
{
public:
  std::string yaml;
  Lexer lexer;

  YAML(const char *path)
  {
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      // Open file
      file.open(path);
      std::stringstream fileStream;

      fileStream << file.rdbuf();

      file.close();

      yaml = fileStream.str();
    }
    catch (std::ifstream::failure e)
    {
      std::cout << "Error: Unable to open file at " << path << std::endl;
    }
  }

  void process()
  {
    // Start by running through lexer
    lexer.tokenize(yaml);
  }
};

#endif