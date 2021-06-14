#ifndef COMPILER_H
#define COMPILER_H

#include <string>

namespace subscheme {

class Function;

class Compiler {
 public:
	static void compile(Function* func, std::string& source);
};

} // namespace subscheme

#endif // COMPILER_H