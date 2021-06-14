#ifndef AST_INL_DEF_H
#define AST_INL_DEF_H

#include "src/ast.h"
#include "src/scanner.h"

namespace subscheme {

CallExpr::CallExprType CallExpr::type() const {
  switch (token_->type()) {
    case Token::TokenType::Add:
      return CallExpr_Add;
    case Token::TokenType::Sub:
      return CallExpr_Sub;
    case Token::TokenType::Concat:
      return CallExpr_Concat;
    default:
      DCHECK(false);
  }
}

LiteralExpr::LiteralType LiteralExpr::type() const {
  switch(token_->type()) {
    case Token::IntLiteral:
      return Literal_Num;
    case Token::StringLiteral:
      return Literal_String;
    default:
      return Literal_Unknown;
  }
}

std::string LiteralExpr::as_string() const {
    DCHECK(type() == Literal_String);
    return token_->str();
}

int LiteralExpr::as_number() const {
    DCHECK(type() == Literal_Num);
    return token_->number();
}

} // namespace subscheme

#endif // AST_INL_DEF_H