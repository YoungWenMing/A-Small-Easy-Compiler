#include <iostream>

#include "src/global.h"
#include "src/scanner.h"
#include "src/parser.h"
#include "src/ast.h"
#include "src/code-generator.h"
#include "src/compiler.h"

#include <iomanip>

void print_tokens(std::vector<std::shared_ptr<subscheme::Token> >& tokens) {
  std::cout << "Tokens: [\n";
  for (std::shared_ptr<subscheme::Token> t : tokens) {
    std::cout << "    ";
    t->Print(std::cout);
    std::cout << "\n";
  }
  std::cout << "]\n";
}

void scan_source(const char* src) {
  subscheme::Scanner scanner(src);
  std::vector<std::shared_ptr<subscheme::Token> > tokens;
  scanner.Scan(tokens);
  print_tokens(tokens);
}

void test_astnode_print() {
  std::shared_ptr<subscheme::Token> t1
      = std::make_shared<subscheme::Token>(subscheme::Token::IntLiteral, 10);
  std::shared_ptr<subscheme::Token> t2
      = std::make_shared<subscheme::Token>(subscheme::Token::StringLiteral, "aiya");
  std::shared_ptr<subscheme::Token> c0
      = std::make_shared<subscheme::Token>(subscheme::Token::Add);
  
  subscheme::LiteralExpr* left = new subscheme::LiteralExpr(t1);
  subscheme::LiteralExpr* right = new subscheme::LiteralExpr(t2);
  subscheme::CallExpr ca(c0, left, right);

  ca.print(std::cout);
  
  // subscheme::LiteralExpr left(std::shared_ptr<subscheme::Token>(&t1));
  // subscheme::LiteralExpr right(std::shared_ptr<subscheme::Token>(&t1));
  // subscheme::CallExpr call(std::shared_ptr<subscheme::Token>(&c0), &left, &right);
}

void PrintAstOfSource(const char* src) {
  subscheme::Scanner scanner(src);
  std::vector<std::shared_ptr<subscheme::Token> > tokens;
  scanner.Scan(tokens);
  print_tokens(tokens);
  subscheme::Parser parser(tokens);

  subscheme::ASTNode* prog = parser.ParseProgram();
  prog->print(std::cout);
}

void test_generated_function(const char* source) {
  std::string src(source);
  subscheme::Function func;
  subscheme::Compiler::compile(&func, src);

  func.print(std::cout, 0);
}

int main() {
  std::cout << "hello world" << std::endl;

  // const char* source = "(add 2 (sub 4 5))";
  // scan_source(source);

  // source = "(concat \"hello\" (concat \" yes\" \" god\"))";
  // scan_source(source);

  // source = "(add 1  (concat 3 \"hello\"))";
  // scan_source(source);

  // // test_astnode_print();
  // PrintAstOfSource("(add 2 (sub 4 5))");
  // PrintAstOfSource("( add 2 3)");
  // PrintAstOfSource("( add (sub 5 6) 6)");
  // PrintAstOfSource("( add (sub 5 6) (concat \" yes \"  \" oh\"))");
  int t = 0x00000010;
  int k = 0x0000000a;
  unsigned short ins = static_cast<unsigned short>((t << 8) | k);
  printf("%d\n", static_cast<int>(ins));

  // subscheme::Instruction inss = subscheme::Instruction::NewLdConst(1);
  // inss.print(std::cout);
  // printf("%d\n", (int)sizeof(inss));

  // subscheme::Value val(10);
  // val.print(std::cout, 2);

  // subscheme::Value v(0xf0032);
  // v.print(std::cout);

  // std::string s("gogogo");
  // subscheme::Value v0(s);
  // v0.print(std::cout);

  // std::string s0("gogokinit");
  // subscheme::Value v1(s0);
  // v1.print(std::cout);

  test_generated_function("(add 2 3)");
  test_generated_function("(concat \"hello\" \"world\")");
  test_generated_function("(add (add 3 4) (sub 9 3))");

}
