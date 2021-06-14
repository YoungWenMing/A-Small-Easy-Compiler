#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "src/global.h"
#include "src/ast-visitor.h"
#include "src/value.h"


typedef unsigned short bytecode;

namespace subscheme {

class Function;
class Value;

#define OP_LIST(V) 						\
	V(Op_Add, "Op_Add")					\
	V(Op_Sub, "Op_Sub")					\
	V(LdConst, "LdConst")				\
	V(LdAcc, "LdAcc")						\
	V(InValid, "InValid")

class Instruction {
 public:
	enum OpType {
#define ENUM_OPTYPE(n1, n2)					\
	n1,
	OP_LIST(ENUM_OPTYPE)
#undef ENUM_OPTYPE
	};

	static Instruction NewInstructionNoOprand(OpType type) {
		DCHECK(type != LdConst);
		return Instruction(type);
	}

	static Instruction NewLdConst(int index) {
		DCHECK(index >= 0 && index < 256);
		return Instruction(LdConst, index);
	}

	bytecode get_code() const {
		return bytecode_;
	}

	OpType op_type() const {
		return static_cast<OpType>((bytecode_ >> 8) & 0xff);
	}

	int oprand() const {
		return static_cast<int>(bytecode_ & 0xff);
	}

	void print(std::ostream& os = std::cout, int line_space = 0) const;

 private:
	bytecode bytecode_;
	Instruction(OpType type, int oprand = 0) {
		bytecode_ = static_cast<bytecode>((type << 8) | (oprand & 0xFF));
	}
};

class BytecodeGenerator : public AstVisitor<BytecodeGenerator> {
 public:
	BytecodeGenerator(Function* func) : func_(func) {}
	void Visit(const ASTNode* node);
	void VisitProgram(const Program* prog);
	void VisitCallExpr(const CallExpr* call);
	void VisitLiteralExpr(const LiteralExpr* literal);
 private:
	Function* func_;
};

class Function {
 public:
	Function() = default;
	~Function() {}
	int add_value(Value& val);
	void add_instruction(Instruction ins);
	Value run();

	const std::vector<Instruction>& instructions() const {
		return inss_;
	}

	void print(std::ostream& os = std::cout, size_t line_space = 0) const;
 private:
	std::vector<Value> const_vals;
	std::vector<Instruction> inss_;
};

} // namespace subscheme
#endif // CODE_GENERATOR_H