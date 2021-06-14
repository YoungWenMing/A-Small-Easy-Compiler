#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include <vector>
#include <memory>


namespace subscheme {

class ASTNode;
class Token;

class Parser {
 public:
  Parser(std::vector<std::shared_ptr<Token> >& tokens):
    tokens_(tokens),
    current_index_(-1),
    current_token_(nullptr) {}
  
  ASTNode* ParseProgram();

 private:
  bool in_range() {
    return current_index_ < tokens_.size() - 1;
  }
  bool advance() {
    if (current_index_ == tokens_.size() - 1) return false;
    current_token_ = tokens_[++current_index_];
    return true;
  }
  ASTNode* ParseLiteralExpr();
  ASTNode* ParseCallExpr();
  ASTNode* ParseStatement();

  std::vector<std::shared_ptr<Token> >& tokens_;
  int current_index_;
  std::shared_ptr<Token> current_token_;

};

} // namespace subscheme
#endif // PARSER_DEF_H