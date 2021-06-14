#ifndef SCANNER_DEF_H
#define SCANNER_DEF_H

#include "src/global.h"

#include <string>
#include <memory>
#include <vector>
#include <iostream>


namespace subscheme {


#define ALL_TOKENS(V)             \
  V(Add, add)                     \
  V(Sub, sub)                     \
  V(Concat, concat)               \
  V(LeftParen, leftparen)         \
  V(RightParen, rightparen)       \
  V(IntLiteral, intliteral)       \
  V(StringLiteral, stringliteral) \
  V(Invalid, invalid)

class Token {
 public:
  static constexpr const char* KEYWORD_ADD = "add";
  static constexpr const char* KEYWORD_SUB = "sub";
  static constexpr const char* KEYWORD_CON = "concat";

  enum TokenType {
    Add,
    Sub,
    Concat,
    LeftParen,
    RightParen,
    IntLiteral,
    StringLiteral,
    Invalid
  };
  static std::string TokenTypeToString(TokenType t);

  explicit Token(TokenType type) : type_(type) {}
  Token(TokenType type, int num) :
      type_(type), num_(num) {}
  Token(TokenType type, std::string&& str) :
      type_(type), str_(str) {}
  
  Token(const Token& token) {}

  ~Token() {}

  TokenType type() const {
    return type_;
  }

#define IS_TOKEN_TYPE(n1, n2)   \
  bool is_##n2() const {        \
    return type_ == n1;         \
  }

  ALL_TOKENS(IS_TOKEN_TYPE);
#undef IS_TOKEN_TYPE

  std::string str() const {
    DCHECK(is_stringliteral());
    return str_;
  }

  int number() const {
    DCHECK(is_intliteral());
    return num_;
  }

  void Print(std::ostream& out = std::cout) const;

 private:
  TokenType type_;
  union {
    int num_;
    std::string str_;
  };
};

class Scanner {
 public:
  Scanner(const char* input) :
    source_(input),
    cursor_(input),
    current_charactor_(input[0]) {}
  
  void Scan(std::vector<std::shared_ptr<Token> >& tokens);

 private:
  void Init() {
    cursor_ = source_;
    current_charactor_ = source_[0];
  }

  Token* Next();
  std::string ScanString(bool is_plain_text);
  bool ScanKeyword(Token::TokenType type);
  int ScanNumber();
  void Advance();

  const char* source_;
  const char* cursor_;

  char current_charactor_;
};


} // namespace subscheme
#endif // PARSER_DEF_H
