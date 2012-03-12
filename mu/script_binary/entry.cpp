#include <boost/cstdint.hpp>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/script/identity/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/ast/read_from_file.h>
#include <mu/script/ast/merge.h>
#include <mu/script/astring/truncate.h>
#include <mu/script/bool_c/create.h>
#include <mu/script/bool_c/equal.h>
#include <mu/script/chain/operation.h>
#include <mu/script/cluster/get_named.h>
#include <mu/script/extensions/create.h>
#include <mu/script/extensions/merge_package.h>
#include <mu/script/integer/equal.h>
#include <mu/script/integer/subtract.h>
#include <mu/script/print/operation.h>
#include <mu/script/package/add.h>
#include <mu/script/package/create.h>
#include <mu/script/package/get.h>
#include <mu/script/package/remove.h>
#include <mu/script/times/operation.h>
#include <mu/script/string/extension.h>
#include <mu/script/astring/extension.h>
#include <mu/script/integer/extension.h>
#include <mu/script/debugging/flat_mapping.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

extern "C"
#ifdef _WIN32
	__declspec (dllexport)
#endif
boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

extern "C"
#ifdef _WIN32
	__declspec (dllexport)
#endif
void extensions (mu::script::extensions::node ** extensions, mu::script::debugging::mapping ** debug_info_a)
{
	auto result (new mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"identity")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	result->extensions->extensions_m [std::wstring (L"ast/read_from_file")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::ast::read_from_file> ());
	result->extensions->extensions_m [std::wstring (L"ast/merge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::ast::merge> ());
	result->extensions->extensions_m [std::wstring (L"astring/truncate")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::astring::truncate> ());
	result->extensions->extensions_m [std::wstring (L"bool_c/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::bool_c::create> ());
	result->extensions->extensions_m [std::wstring (L"bool_c/equal")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::bool_c::equal> ());
	result->extensions->extensions_m [std::wstring (L"chain/operation")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::chain::operation> ());
	result->extensions->extensions_m [std::wstring (L"cluster/get_named")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::cluster::get_named> ());
	result->extensions->extensions_m [std::wstring (L"extensions/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::create> ());
	result->extensions->extensions_m [std::wstring (L"extensions/merge_package")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::extensions::merge_package> ());
	result->extensions->extensions_m [std::wstring (L"integer/equal")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::integer::equal> ());
	result->extensions->extensions_m [std::wstring (L"integer/subtract")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::integer::subtract> ());
	result->extensions->extensions_m [std::wstring (L"print/operation")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::print::operation> ());
	result->extensions->extensions_m [std::wstring (L"package/add")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::add> ());
	result->extensions->extensions_m [std::wstring (L"package/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::create> ());
	result->extensions->extensions_m [std::wstring (L"package/get")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::get> ());
	result->extensions->extensions_m [std::wstring (L"package/remove")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::package::remove> ());
	result->extensions->extensions_m [std::wstring (L"times/operation")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::times::operation> ());
	*extensions = result;
	auto debug_info (new mu::script::debugging::flat_mapping);
	*debug_info_a = debug_info;
}