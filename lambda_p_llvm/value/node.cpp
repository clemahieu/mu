#include "node.h"

lambda_p_llvm::value::node::node (llvm::Value * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a)
	: value_m (value_a),
	type (type_a)
{
}

llvm::Value * lambda_p_llvm::value::node::value ()
{
	return value_m;
}