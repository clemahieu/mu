#include <mu/script/runtime/call.h>

#include <mu/script/runtime/node.h>
#include <mu/script/operation.h>
#include <mu/core/errors/error_context.h>
#include <mu/script/runtime/frame.h>
#include <mu/core/routine.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/context.h>
#include <mu/script/runtime/trace.h>

#include <boost/make_shared.hpp>

#include <sstream>

mu::script::runtime::call::call (size_t results_a)
	: results (results_a)
{
}

mu::script::runtime::call::call (size_t results_a, mu::core::context context_a)
	: context (context_a),
	results (results_a)
{
}

void mu::script::runtime::call::operator () (mu::script::context & context_a, mu::script::runtime::frame & frame_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> arguments_l;
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
	{
		(*(*i)) (context_a.errors, frame_a, arguments_l);
	}
	if (arguments_l.size () > 0)
	{
		auto operation (boost::dynamic_pointer_cast <mu::script::operation> (arguments_l [0]));
		if (operation.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> results_l;
            std::vector <boost::shared_ptr <mu::core::node>> segment (arguments_l.begin () + 1, arguments_l.end () + 0);
			auto ctx (mu::script::context (context_a, segment, results_l));
            (*operation) (ctx);
			std::vector <boost::shared_ptr <mu::core::node>> & target (frame_a.nodes [results]);
			assert (target.empty () && L"Destination has already been assigned");
			target.assign (results_l.begin (), results_l.end ());
		}
		else
		{
			std::wstringstream message;
			message << L"First argument to call is not an operation: ";
			message << arguments_l [0]->name ();
			context_a (message.str ());
		}
	}
	else
	{
		context_a (L"Call has no arguments");
	}
}