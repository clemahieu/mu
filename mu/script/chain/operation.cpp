#include <mu/script/chain/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

bool mu::script::chain::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters (0)));
		if (one.get () != nullptr)
		{
			assert (false);
			//std::vector <boost::shared_ptr <mu::core::node>> arguments (context_a.parameters.begin () + 1, context_a.parameters.end ());
			//bool end (false);
			//while (!end)
			//{
			//	std::vector <boost::shared_ptr <mu::core::node>> results_l;
			//	auto ctx (mu::script::context (context_a, arguments, results_l));
			//	(*one) (ctx);
			//	if (results_l.size () > 0)
			//	{
			//		auto val (boost::dynamic_pointer_cast <mu::script::bool_c::node> (results_l [results_l.size () - 1]));
			//		if (val.get () != nullptr)
			//		{
			//			end = val->value;
			//			arguments.swap (results_l);
			//			arguments.resize (arguments.size () - 1);
			//		}
			//		else
			//		{
			//			end = true;
			//			context_a.errors (L"Last result must be a bool");
			//			result = false;
			//		}
			//	}
			//	else
			//	{
			//		end = true;
			//		context_a.errors (L"Chain operation must have at least one result");
			//		result = false;
			//	}
			//}
			//context_a.push (context_a.results.end (), arguments.begin (), arguments.end ());
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.parameters (0).get ()), typeid (mu::script::operation), 0);
			result = false;
		}
	}
	else
	{
		context_a.errors (L"Chain operation must have at least one argument");
		result = false;
	}
	return result;
}

std::wstring mu::script::chain::operation::name ()
{
	return std::wstring (L"mu::script::chain::operation");
}