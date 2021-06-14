#include "src/code-generator.h"
#include "src/ast-inl.h"

#include <iomanip>

namespace subscheme {


void Instruction::print(std::ostream& os, int line_space) const {
	os << std::setw(line_space) << std::setfill(' ') << " "
		 << std::hex 
	   << std::setw(2) << std::setfill('0') << op_type() << " "
		 << std::setw(2) << std::setfill('0') << oprand() << " ";
	switch(op_type()) {
#define PRINT_OPTYPE(n1, n2)												\
	case n1:																					\
		os << n2;																				\
	break;

	OP_LIST(PRINT_OPTYPE);
#undef PRINT_OPTYPE
	} 
	os << std::dec << std::endl;
}

void BytecodeGenerator::Visit(const ASTNode* node) {
	switch(node->node_type()) {
		case AST_Program:
			VisitProgram(static_cast<const Program*>(node));
			break;
		case AST_CallExpr:
			VisitCallExpr(static_cast<const CallExpr*>(node));
			break;
		case AST_Literal:
			VisitLiteralExpr(static_cast<const LiteralExpr*>(node));
			break;
		default:
			DCHECK(false);
	}
}

void BytecodeGenerator::VisitProgram(const Program* prog) {
	for (auto stmt : prog->get_statements()) {
		Visit(stmt);
	}
}

void BytecodeGenerator::VisitCallExpr(const CallExpr* call) {
	Visit(call->left_side());
	Visit(call->right_side());
	switch (call->type()) {
		case CallExpr::CallExpr_Concat:
		case CallExpr::CallExpr_Add:
			func_->add_instruction(
					Instruction::NewInstructionNoOprand(Instruction::Op_Add));
			break;
		case CallExpr::CallExpr_Sub:
			func_->add_instruction(
					Instruction::NewInstructionNoOprand(Instruction::Op_Sub));
			break;
		default:
			DCHECK(false);
	}
}

void BytecodeGenerator::VisitLiteralExpr(const LiteralExpr* literal) {
	switch(literal->type()) {
		case LiteralExpr::Literal_Num: {
			Value val(literal->as_number());
			int index = func_->add_value(val);
			Instruction ins = Instruction::NewLdConst(index);
			func_->add_instruction(ins);
		}
			break;
		case LiteralExpr::Literal_String: {
			Value val(literal->as_string());
			int index = func_->add_value(val);
			Instruction ins = Instruction::NewLdConst(index);
			func_->add_instruction(ins);
		}
			break;
		default:
			DCHECK(false);
	}
}

int Function::add_value(Value& val) {
	for (int i = 0; i < const_vals.size(); ++i) {
		if (val == const_vals[i]) {
			return i;
		}
	}
	const_vals.push_back(val);
	return const_vals.size() - 1;
}

void Function::add_instruction(Instruction ins) {
	inss_.push_back(ins);
}

void Function::print(std::ostream& os, size_t line_space) const {
	os << std::setw(line_space) << std::setfill(' ') << "Function: {\n"
	   << std::setw(line_space) << std::setfill(' ') << " " << "- BytecodeArray: [\n";
	for (int i = 0; i < inss_.size(); ++i) {
		inss_[i].print(os, line_space + 2);
	}
	os << std::setw(line_space) << std::setfill(' ') << " ]\n"
	   << std::setw(line_space) << std::setfill(' ') << " " << "- ConstValues: [\n";
	for (int i = 0; i < const_vals.size(); ++i) {
		const_vals[i].print(os, line_space + 2);
	}
	os << std::setw(line_space) << std::setfill(' ') << " ]\n";
	os << std::setw(line_space) << std::setfill(' ') << "}" << std::endl;
}

} // subscheme