#include "src/value.h"
#include <iomanip>

namespace subscheme {

void Value::print(std::ostream& os, size_t line_space) const {
	const char* type_str = nullptr;
	if (type_ == Val_Num) 	type_str = "Val_Num";
	else 										type_str = "Val_String";
	os << std::setw(line_space) << std::setfill(' ') << " "
		 << "Value: [ " << std::setw(10) << std::setfill(' ') << type_str
		 << ", content: ";
	
	if (type_ == Val_Num) {
		os << std::setw(10) << std::setfill(' ') << num_;
	} else {
		os << std::setw(10) << std::setfill(' ')
			 << (str_->size() > 7 ?
			 		(str_->substr(0, 7) + "...").c_str() : str_->c_str());
	}
	os << " ]" << std::endl;

}


} // namespace subscheme