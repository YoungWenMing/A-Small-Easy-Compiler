
#include "src/parser.h"

#include "src/exception.h"
#include "src/scanner.h"
#include "src/ast.h"

namespace subscheme {


ASTNode* Parser::ParseProgram() {
  Program* root = new Program;
  while (advance()) {
    if (current_token_->is_leftparen()) {
      root->add_statement(ParseStatement());
    } else {
      throw CompileError("Compile Error: expected ')'.");
    }
  }
  return root;
}

ASTNode* Parser::ParseLiteralExpr() {
  return new LiteralExpr(current_token_);
}

ASTNode* Parser::ParseCallExpr() {
  std::shared_ptr<Token> op_token = current_token_;
  if (advance()) {
    ASTNode* left = nullptr, *right = nullptr;
    if (current_token_->is_leftparen()) {
      left = ParseStatement();
    } else {
      left = ParseLiteralExpr();
    }

    if (advance()) {
      if (current_token_->is_leftparen()) {
        right = ParseStatement();
      } else {
        right = ParseLiteralExpr();
      }
      return new CallExpr(op_token, left, right);
    }
  }
  throw CompileError("Compile Error: unexpected ending.");
}

ASTNode* Parser::ParseStatement() {
  DCHECK(current_token_->is_leftparen());
  if (!advance()) {
    throw CompileError("Compile Error: two consecutive '('s is a syntax error.");
  }
  ASTNode* result = nullptr;
  switch(current_token_->type()) {
    case Token::Add:
    case Token::Sub:
    case Token::Concat:
      result = ParseCallExpr();
      break;
    case Token::IntLiteral:
    case Token::StringLiteral:
      result = ParseLiteralExpr();
      break;
    case Token::LeftParen:
      throw CompileError("Compile Error: two consecutive '('s is a syntax error.");
    default:
      result = new ASTNode();
  }
  if (!advance() || !current_token_->is_rightparen()) {
    throw CompileError("Compile Error: expecting ')' at the end of a statement.");
  }
  return result;
}

} // namespace subscheme
