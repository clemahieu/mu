#include "builder.h"

#include <boost/bind.hpp>

#include <lambda_p_script/integer/extension.h>
#include <lambda_p_script/data/extension.h>

lambda_p_script_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	synthesizer (boost::bind (&lambda_p_script_io::builder::operator (), this, _1)),
	analyzer (boost::bind (&lambda_p_script_io::synthesizer::operator (), &synthesizer, _1), errors, extensions ()),
	parser (boost::bind (&lambda_p_io::analyzer::analyzer::operator (), &analyzer, _1)),
	lexer (boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1))
{
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
	return result;
}
