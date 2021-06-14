#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "src/ast.h"

namespace subscheme {

template <class SubClass>
class AstVisitor {
 public:
	void Visit(ASTNode* node) {
		impl()->Visit(node);
	}
	virtual ~AstVisitor() {}
	
 private:
	SubClass* impl() {
		return static_cast<SubClass*>(this);
	}
};

} // namespace subscheme
#endif // AST_VISITOR_H