#ifndef   EXCEPTION_DEF_H
#define   EXCEPTION_DEF_H

#include <stdexcept>

class CompileError : public std::runtime_error {
 public:
  explicit CompileError(const std::string& s) :
    std::runtime_error(s) {}
};

#endif // EXCEPTION_DEF_H