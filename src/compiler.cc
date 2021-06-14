#include "src/compiler.h"
#include "src/code-generator.h"
#include "src/scanner.h"
#include "src/parser.h"
#include "src/ast.h"

#include <vector>
#include <memory>

namespace subscheme {

void Compiler::compile(Function* func, std::string& source) {
	// step 1: produce tokens by scanner
	Scanner scanner(source.c_str());
	std::vector<std::shared_ptr<Token> > tokens;
	scanner.Scan(tokens);

	// step 2: build Abstract Syntax Tree by parser
	Parser parser(tokens);
	ASTNode* prog = parser.ParseProgram();

	// step 3: generate bytecodes by code-generator
	BytecodeGenerator gen(func);
	gen.Visit(prog);

	// at last, we got a integrated function.
}

} // namespace subscheme
