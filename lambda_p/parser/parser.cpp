#include <lambda_p/parser/parser.h>

#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/parser/begin.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/statement.h>
#include <lambda_p/parser/data.h>
#include <lambda_p/parser/finished.h>
#include <lambda_p/parser/association.h>
#include <lambda_p/parser/position_set.h>
#include <lambda_p/parser/target_set.h>
#include <lambda_p/parser/data_factory.h>

#include <boost/bind.hpp>

#include <map>

lambda_p::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a)
	: target (target_a)
{
	keywords.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p::parser::state_factory> (new lambda_p::parser::data_factory)));
	reset ();
}

lambda_p::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a)
	: target (target_a),
	injected_parameters (injected_parameters_a)
{
	keywords.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p::parser::state_factory> (new lambda_p::parser::data_factory)));
	reset ();
}

lambda_p::parser::parser::parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a, std::vector <std::wstring> & injected_returns_a)
	: target (target_a),
	injected_parameters (injected_parameters_a),
	injected_returns (injected_returns_a)
{
	keywords.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p::parser::state_factory> (new lambda_p::parser::data_factory)));
	reset ();
}

void lambda_p::parser::parser::operator () (lambda_p::tokens::token * token)
{
	auto state_l (state.top ());
	state_l->parse (token);
}

void lambda_p::parser::parser::reset ()
{
	while (!state.empty ())
	{
		state.pop ();
	}
    state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::finished (*this)));
	state.push (boost::shared_ptr <lambda_p::parser::state> (new lambda_p::parser::begin (*this)));
}

boost::shared_ptr <lambda_p::parser::error> lambda_p::parser::parser::error ()
{
	boost::shared_ptr <lambda_p::parser::error> result;
	if (!state.empty ())
	{
		result = boost::dynamic_pointer_cast <lambda_p::parser::error> (state.top ());
	}
	return result;
}

std::wstring lambda_p::parser::parser::token_type_name (lambda_p::tokens::token * token)
{
	std::wstring result;
	size_t token_id (token->token_id ());
	switch (token_id)
	{
	case lambda_p::tokens::token_id_complex_identifier:
		result.append (L"complex_identifier");
		break;
	case lambda_p::tokens::token_id_identifier:
		result.append (L"identifier");
		break;
	case lambda_p::tokens::token_id_routine_end:
		result.append (L"routine_end");
		break;
	case lambda_p::tokens::token_id_data:
		result.append (L"data");
		break;
	case lambda_p::tokens::token_id_divider:
		result.append (L"divider");
		break;
	case lambda_p::tokens::token_id_stream_end:
		result.append (L"stream_end");
		break;
	default:
		result.append (L"Unknown");
		assert (false);
	}

	return result;
}