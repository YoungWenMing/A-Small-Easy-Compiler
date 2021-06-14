
#include <iomanip>

#include "src/ast-inl.h"

namespace subscheme {
 
void Program::print(std::ostream& os, int line_space) {
  for (int i = 0; i < stmts_.size(); ++i) {
    stmts_[i]->print(os, line_space);
  }
}

void CallExpr::print(std::ostream& os, int line_space) {
  os << std::setw(line_space) << ' ' << "*CallExpression: " << '\n'
     << std::setw(line_space) << ' ' << "  type: "
     << Token::TokenTypeToString(token_->type()) << '\n'
     << std::setw(line_space) << ' ' << "  left: \n";
  left_->print(os, line_space + 4);
  os << std::setw(line_space) << ' ' << "  right: \n";
  right_->print(os, line_space + 4);
}

void LiteralExpr::print(std::ostream& os, int line_space) {
  os << std::setw(line_space) << ' ' << "*LiteralExpression: " << '\n'
     << std::setw(line_space) << ' ' << "  type: "
     << Token::TokenTypeToString(token_->type()) << '\n';
  LiteralType t = type();
  if (t == Literal_String) {
    os << std::setw(line_space) << ' ' << "  value: " << as_string() << '\n';
  } else if (t == Literal_Num) {
    os << std::setw(line_space) << ' ' << "  value: " << as_number() << '\n';   
  }
}

} // namespace subscheme
