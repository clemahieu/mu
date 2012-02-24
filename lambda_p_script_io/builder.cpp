#include "builder.h"

#include <boost/bind.hpp>

#include <lambda_p_script/integer/extension.h>
#include <lambda_p_script/string/extension.h>
#include <mu/io/analyzer/extensions/global.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/unit/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <lambda_p_script/closure/apply.h>
#include <lambda_p_script/closure/create.h>
#include <lambda_p_script/closure/create_single.h>
#include <lambda_p_script/closure/hole.h>
#include <lambda_p_script/bool_c/create.h>
#include <lambda_p_script/bool_c/equal.h>
#include <lambda_p_script/chain/operation.h>
#include <lambda_p_script_io/lambda.h>
#include <lambda_p_script_io/lambda_single.h>
#include <lambda_p_script/integer/equal.h>
#include <lambda_p_script/integer/subtract.h>
#include <lambda_p_script/package/add.h>
#include <lambda_p_script/package/create.h>
#include <lambda_p_script/package/get.h>
#include <lambda_p_script/package/remove.h>
#include <lambda_p_script/times/operation.h>
#include <lambda_p_script/exec/operation.h>
#include <lambda_p_script/astring/extension.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_script/closure/single.h>
#include <lambda_p_script/package/get_recursive.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <lambda_p_script/print/operation.h>
#include <mu/core/routine.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/ast/extension.h>
#include <lambda_p_llvm/analyzer/operation.h>
#include <lambda_p_llvm/synthesizer/operation.h>
#include <lambda_p_llvm/extension.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/cluster/get.h>
#include <lambda_p_script/closure/single.h>
#include <lambda_p_script/values/create.h>
#include <lambda_p_script/ast/read_from_file.h>
#include <lambda_p_llvm/module/merge.h>
#include <lambda_p_script/astring/truncate.h>

#include <boost/make_shared.hpp>

lambda_p_script_io::builder::builder ()
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&lambda_p_script_io::builder::operator(), this, _1), errors, lambda_p_script_io::extensions ()),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
	set_self ();
}

lambda_p_script_io::builder::builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: errors (new mu::core::errors::error_list),
	analyzer (boost::bind (&lambda_p_script_io::builder::operator(), this, _1), errors, extensions_a),
	parser (errors, boost::bind (&mu::io::analyzer::analyzer::input, &analyzer, _1)),
	lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2))
{
	set_self ();
}

void lambda_p_script_io::builder::set_self ()
{
	auto get (boost::make_shared <lambda_p_script::cluster::get> ());
	self = boost::make_shared <lambda_p_script::closure::single> (get);
	analyzer.extensions->extensions_m [L"."] = boost::make_shared <mu::io::analyzer::extensions::global> (self);
}

void lambda_p_script_io::builder::operator () (boost::shared_ptr <mu::core::cluster> cluster_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (cluster_a);
	synthesizer (errors, arguments, results);
	if (results.size () == 1)
	{
		auto result (boost::dynamic_pointer_cast <lambda_p_script::cluster::node> (results [0]));
		assert (result.get () != nullptr);		
		self->closed.push_back (results [0]);
		clusters.push_back (result);
		set_self ();
		fwprintf (stderr, L"");
	}
}

boost::shared_ptr <mu::io::analyzer::extensions::extensions> lambda_p_script_io::extensions ()
{
	auto result (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"=>"), boost::make_shared <lambda_p_script_io::lambda> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"->"), boost::make_shared <lambda_p_script_io::lambda_single> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"#"), boost::make_shared <lambda_p_script::integer::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"`"), boost::make_shared <lambda_p_script::string::extension> ()));;
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"{"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::values::create> ())));;
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"`a"), boost::make_shared <lambda_p_script::astring::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"~"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::identity::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".()"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::unit::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".synthesize"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script_io::synthesizer> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/ast/read_from_file"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::ast::read_from_file> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/astring/truncate"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::astring::truncate> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/bool_c/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::bool_c::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/bool_c/equal"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::bool_c::equal> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/chain/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::chain::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".apply"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::closure::create_single> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::closure::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".ast"), boost::make_shared <lambda_p_script::ast::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".llvm"), boost::make_shared <lambda_p_llvm::extension> ()));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"?"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::closure::hole> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"if"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::closure::hole> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/integer/equal"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::integer::equal> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/integer/subtract"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::integer::subtract> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L".exec"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::exec::operation> (result))));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/print/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::print::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/add"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::package::add> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::package::create> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/get"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::package::get> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/package/remove"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::package::remove> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"script/times/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_script::times::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/analyzer/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::analyzer::operation> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/merge"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::merge> ())));
	result->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::synthesizer::operation> ())));
	return result;
}
