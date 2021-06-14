#ifndef VALUE_DEF_H
#define VALUE_DEF_H

#include <string>
#include <iostream>

namespace subscheme {

class Value {
 public:
	enum ValueType {
		Val_Num,
		Val_String
	};
	
	Value(int num) : num_(num), type_(Val_Num) {}
	Value(std::string str) :
		str_(new std::string(str)), type_(Val_String) {}
	Value(const Value& val) {
		type_ = val.type_;
		if (val.type_ == Val_String) {
			str_ = new std::string(*(val.str_));
		} else {
			num_ = val.num_;
		}
	}
	~Value() {
		if (type_ == Val_String)	delete str_;
	}

	void print(std::ostream& os = std::cout, size_t line_space = 0) const;

	friend bool operator==(const Value& left, const Value& right) {
		if (left.type_ != right.type_)	return false;
		if (left.type_ == Val_Num)	return left.num_ == right.num_;
		return left.str_->compare(*(right.str_)) == 0;
	}

 private:
	union {
		int num_;
		std::string* str_;
	};
	ValueType type_;
};

} // namespace subscheme

#endif // VALUE_DEF_H
