#include "builder.h"

#include <boost/bind.hpp>

#include <lambda_p_script/integer/extension.h>
#include <lambda_p_script/string/extension.h>
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
#include <lambda_p_script/integer/equal.h>
#include <lambda_p_script/integer/subtract.h>
#include <lambda_p_script/package/add.h>
#include <lambda_p_script/package/create.h>
#include <lambda_p_script/package/get.h>
#include <lambda_p_script/package/remove.h>
#include <lambda_p_script/times/operation.h>
#include <lambda_p_script/exec/operation.h>
#include <lambda_p_script/astring/extension.h>

lambda_p_script_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	synthesizer (boost::bind (&lambda_p_script_io::builder::operator (), this, _1)),
	analyzer (boost::bind (&lambda_p_script_io::synthesizer::operator (), &synthesizer, _1), errors, extensions ()),
	parser (boost::bind (&lambda_p_io::analyzer::analyzer::operator (), &analyzer, _1)),
	lexer (boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1))
{
	exec->extensions = &analyzer.extensions;
}

lambda_p_script_io::builder::builder (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions_a)
	: errors (new lambda_p::errors::error_list),
	synthesizer (boost::bind (&lambda_p_script_io::builder::operator (), this, _1)),
	analyzer (boost::bind (&lambda_p_script_io::synthesizer::operator (), &synthesizer, _1), errors, extensions_a),
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
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"=>"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::lambda)));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"#"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_script::integer::extension)));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_script::string::extension)));;
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"`a"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_script::astring::extension)));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".id"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".()"), boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::unit::operation)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/bool_c/create"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::bool_c::create)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/bool_c/equal"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::bool_c::equal)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".apply"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::apply)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".create"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::create)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"?"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::hole)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"if"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::hole)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/integer/equal"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::equal)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/integer/subtract"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::integer::subtract)))));
	exec = boost::shared_ptr <lambda_p_script::exec::operation> (new lambda_p_script::exec::operation);
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L".exec"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (exec))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/package/add"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::package::add)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/package/create"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::package::create)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/package/get"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::package::get)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/package/remove"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::package::remove)))));
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>>::value_type (std::wstring (L"script/times/operation"), boost::shared_ptr <lambda_p_io::analyzer::global> (new lambda_p_io::analyzer::global (boost::shared_ptr <lambda_p::node> (new lambda_p_script::times::operation)))));
	return result;
}
