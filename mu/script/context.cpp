#include <mu/script/context.h>

mu::script::context::context (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::vector <boost::shared_ptr <mu::core::node>> & parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a, std::vector <boost::shared_ptr <mu::script::debugging::call_info>> & call_stack_a)
	: parameters (parameters_a),
	results (results_a),
	call_stack (call_stack_a),
	errors (errors_a)
{
}

mu::script::context::context (mu::script::context & context_a, std::vector <boost::shared_ptr <mu::core::node>> & parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
	: parameters (parameters_a),
	results (results_a),
	call_stack (context_a.call_stack),
	errors (context_a.errors)
{
}

void mu::script::context::operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a)
{
	(*errors) (error, context_a);
}

bool mu::script::context::operator () ()
{
	return (*errors) ();
}

void mu::script::context::operator () (std::wstring error)
{
	(*errors) (error);
}

void mu::script::context::operator () (wchar_t const * error)
{
	(*errors) (error);
}

void mu::script::context::print (std::wostream & target)
{
	errors->print (target);
}