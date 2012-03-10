#include <mu/script/runtime/frame.h>

mu::script::runtime::frame::frame (boost::shared_ptr <mu::core::node> parameters_a, size_t size)
	: parameters (parameters_a),
	nodes (size)
{
}