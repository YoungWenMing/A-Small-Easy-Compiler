
#include "src/scanner.h"
#include "src/exception.h"

namespace subscheme {

std::string Token::TokenTypeToString(TokenType t) {
  switch (t) {
    case Add:
      return "Add";
    case Sub:
      return "Sub";
    case Concat:
      return "Concat";
    case LeftParen:
      return "LeftParen";
    case RightParen:
      return "RightParen";
    case IntLiteral:
      return "IntLiteral";
    case StringLiteral:
      return "StringLiteral";
    case Invalid:
      return "Invalid";
    default:
      return "Unknown";
  }
}

void Token::Print(std::ostream& out) const {
  out << "[ Token, type: ";
  switch (type_) {
    case Add:
      out << "Add ]";
      break;
    case Sub:
      out << "Sub ]";
      break;
    case Concat:
      out << "Concat ]";
      break;
    case LeftParen:
      out << "'(' ]";
      break;
    case RightParen:
      out << "')' ]";
      break;
    case IntLiteral:
      out << "IntLiteral, val: " << num_ << "]";
      break;
    case StringLiteral:
      out << "StringLiteral, val: \"" << str_ << "\"]";
      break;
    default:
      out << "Unknown ]";
      break;
  }
}

void Scanner::Scan(std::vector<std::shared_ptr<Token> >& tokens) {
  while(current_charactor_ != '\0' && current_charactor_ != EOF) {
    Token* token = Next();
    if (token != nullptr) {
      tokens.push_back(std::shared_ptr<Token>(token));
    }
    Advance();
  }
}

Token* Scanner::Next() {
  Token* token = nullptr;
  switch (current_charactor_) {
    case 'a':
      if (!ScanKeyword(Token::Add)) {
        throw CompileError("Compile Error: Expecting add with character 'a'");
      }
      token = new Token(Token::Add);
      break;
    case 's':
      // keyword sub
      if (!ScanKeyword(Token::Sub)) {
        throw CompileError("Compile Error: Expecting 'sub' with character 's'");
      }
      token = new Token(Token::Sub);
      break;
    case 'c':
      // keyword concat
      if (!ScanKeyword(Token::Concat)) {
        throw CompileError("Compile Error: Expecting 'concat' with character 'c'");
      }
      token = new Token(Token::Concat);
      break;
    case '(':
      // keyword left parenthesis
      token = new Token(Token::LeftParen);
      ++cursor_;
      break;
    case ')':
      token = new Token(Token::RightParen);
      ++cursor_;
      break;
    case '"': {
      std::string s = ScanString(true);
      token = new Token(Token::StringLiteral, std::move(s));
    }
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      int k = ScanNumber();
      token = new Token(Token::IntLiteral, k);
    }
      break;
    case ' ':
      ++cursor_;
      break;
    default:
      // type error
      throw CompileError("Compile Error: Unexpected character.");
      break;
  }
  return token;
}

bool is_valid_identifier_char(char c) {
  return  c == '_'
          || ('0' <= c && c <= '9')
          || ('A' <= c && c <= 'Z')
          || ('a' <= c && c <= 'z');
}

bool is_text_char(char c) {
  return 31 < c && c < 127;
}

std::string Scanner::ScanString(bool is_plain_text) {
  const char* cp = cursor_ + 1;
  char p = cp[0];
  std::string result;
  if (is_plain_text) {
    while (p != '"' && is_text_char(p)) {
      p = (++cp)[0];
    }
    if (p != '"') {
      throw CompileError("Compiler Error: missing '\"' to enclose a string literal");
    } else {
      ++cursor_;
    }
    // now cp point to the right quote
    result.insert(result.end(), cursor_, cp);
    // make cursor_ point to the charactor after the right quote
    cursor_ = cp + 1;
  } else {
    while (is_valid_identifier_char(p)) {
      p = (++cp)[0];
    }
    result.insert(result.begin(), cursor_, cp);
    cursor_ = cp;
  }
  return result;
}

bool Scanner::ScanKeyword(Token::TokenType type) {
  const char* keyword;
  switch (type) {
    case Token::Add:
      keyword = Token::KEYWORD_ADD;
      break;
    case Token::Sub:
      keyword = Token::KEYWORD_SUB;
      break;
    case Token::Concat:
      keyword = Token::KEYWORD_CON;
      break;
    default:
      return false;
  }
  std::string str = ScanString(false);
  if (str.size() == strlen(keyword)) {
    if (strcmp(str.c_str(), keyword) == 0) {
      // cursor_ += strlen(keyword);
      return true;
    }
  }
  return false;
}

int Scanner::ScanNumber() {
  const char* cp = cursor_ + 1;
  char p = cp[0];
  while (p >= '0' && p <= '9') {
    p = (++cp)[0];
  }
  std::string num_str(cursor_, cp);
  cursor_ = cp;
  try {
    int k = std::stoi(num_str);
    return k;
  } catch (const std::invalid_argument& ia) {
    throw CompileError("Compile Error: met invalid argument when parsing number");
  } catch (const std::out_of_range& oor) {
    throw CompileError("Compile Error: number is out of range when parsing number");
  }
}

void Scanner::Advance() {
  current_charactor_ = cursor_[0];
}

} // namespace subscheme
