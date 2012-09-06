#include <mu/script/debugging_trace_types.h>

#include <mu/script/context.h>
#include <mu/core/check.h>
#include <mu/script/values_operation.h>
#include <mu/script/string_node.h>
#include <mu/script/location.h>

bool mu::script::debugging::trace_types::operator () (mu::script::context & context_a)
{
	//auto valid (mu::core::check <mu::io::debugging::mapping> () (context_a));
	//if (valid)
	//{
	//	auto mapping (boost::static_pointer_cast <mu::io::debugging::mapping> (context_a.parameters (0)));
	//	auto result (boost::make_shared <mu::script::values::operation> ());
	//	size_t current_base_begin (context_a.base_begin);
	//	size_t current_base_end (context_a.base_end);
	//	size_t op_position (current_base_begin - 1);
	//	while (op_position < context_a.stack.size () && valid)
	//	{
	//		auto op (context_a.stack [op_position]);
	//		auto name_p (typeid (*op).name ());
	//		std::string name_a (name_p);
	//		std::wstring name (name_a.begin (), name_a.end ());
	//		auto existing (mapping->nodes.find (op));
	//		if (existing != mapping->nodes.end ())
	//		{
	//			name.push_back (U' ');
	//			name.append (existing->second->context.string ());
	//		}
	//		result->values.push_back (boost::make_shared <mu::script::string::node> (name));
	//		auto prev_begin (boost::dynamic_pointer_cast <mu::script::location> (context_a.stack [current_base_end - 2]));
	//		auto prev_end (boost::dynamic_pointer_cast <mu::script::location> (context_a.stack [current_base_end - 1]));
	//		valid = prev_begin != nullptr && prev_end != nullptr;
	//		if (valid)
	//		{
	//			current_base_begin = prev_begin->position;
	//			current_base_end = prev_end->position;
	//			op_position = current_base_begin - 1;
	//		}
	//	}
	//	context_a.push (result);
	//}
	//return valid;
	return false;
}