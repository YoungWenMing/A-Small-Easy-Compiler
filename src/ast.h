#ifndef AST_DEF_H
#define AST_DEF_H

#include <memory>
#include <iostream>
#include <vector>

#include "src/global.h"

namespace subscheme {

class Token;

enum ASTType {
  AST_Literal,
  AST_CallExpr,
  AST_Program,
  AST_Invalid
};

class ASTNode {
 public:
  virtual ASTType node_type() const { return AST_Invalid;}
  virtual ~ASTNode() {}

  virtual void print(std::ostream& os = std::cout,
                     int line_space = 0) {}
};

class Program : public ASTNode {
 public:
  Program() {}
  ASTType node_type() const override {
    return AST_Program;
  }
  void print(std::ostream& os = std::cout,
             int line_space = 0) override;
  void add_statement(ASTNode* stmt) {
    stmts_.push_back(stmt);
  }
  const std::vector<ASTNode* >& get_statements() const {
    return stmts_;
  }

 private:
  std::vector<ASTNode* > stmts_;
};

class CallExpr : public ASTNode {
 public:
  enum CallExprType {
    CallExpr_Add,
    CallExpr_Sub,
    CallExpr_Concat
  };

  CallExpr(std::shared_ptr<Token> token, 
           ASTNode* left, ASTNode* right) :
      token_(token),
      left_(left),
      right_(right) {}
  
  ~CallExpr() {}
  
  ASTType node_type() const override {
    return AST_CallExpr;
  }

  inline CallExprType type() const;

  const ASTNode* left_side() const {
    return left_;
  }

  const ASTNode* right_side() const {
    return right_;
  }

  void print(std::ostream& os = std::cout,
             int line_space = 0) override;

 private:
  std::shared_ptr<Token> token_;
  ASTNode* left_;
  ASTNode* right_;

};

class LiteralExpr : public ASTNode {
 public:
  enum LiteralType {
    Literal_Num,
    Literal_String,
    Literal_Unknown
  };
  LiteralExpr(std::shared_ptr<Token> token) :
      token_(token) {}
  
  void print(std::ostream& os = std::cout,
             int line_space = 0) override;

  ASTType node_type() const override {
    return AST_Literal;
  }
  ~LiteralExpr() {}

  inline LiteralType type() const;

  inline std::string as_string() const;

  inline int as_number() const;

 private:
  std::shared_ptr<Token> token_;
};

} // namespace subscheme

#endif // AST_DEF_H