#include "builder.h"

#include <boost/bind.hpp>

#include <lambda_p_script/integer/extension.h>
#include <lambda_p_script/data/extension.h>
#include <lambda_p_io/analyzer/global.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/unit/operation.h>
#include <lambda_p_io/analyzer/global.h>
#include <lambda_p_script/closure/apply.h>
#include <lambda_p_script/closure/create.h>
#include <lambda_p_script/closure/hole.h>
#include <lambda_p_script/bool_c/create.h>
#include <lambda_p_script/bool_c/equal.h>
#include <lambda_p_io/lambda.h>

lambda_p_script_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	synthesizer (boost::bind (&lambda_p_script_io::builder::operator (), this, _1)),
	analyzer (boost::bind (&lambda_p_script_io::synthesizer::operator (), &synthesizer, _1), errors, extensions ()),
	parser (boost::bind (&lambda_p_io::analyzer::analyzer::operator (), &analyzer, _1)),
	lexer (boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1))
{
	analyzer.extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"=>"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::lambda)));
}

void lambda_p_script_io::builder::operator () (boost::shared_ptr <lambda_p_script::routine> routine_a)
{
	routines.push_back (routine_a);
}

std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> lambda_p_script_io::builder::extensions ()
{
	std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> result;
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"#"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_script::integer::extension)));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_script::data::extension)));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".id"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".()"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::unit::operation)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/bool_c/create"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::bool_c::create)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/bool_c/equal"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::bool_c::equal)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/closure/apply"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::apply)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/closure/create"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::create)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/closure/hole"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::hole)))));
	return result;
}
