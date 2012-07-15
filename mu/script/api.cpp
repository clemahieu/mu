#include <mu/script/api.h>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/extension.h>
#include <mu/script/astring/extension.h>
#include <mu/script/integer/extension.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/identity/operation.h>
#include <mu/script/identity/operation.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/ast/read_from_file.h>
#include <mu/script/ast/merge.h>
#include <mu/script/astring/truncate.h>
#include <mu/script/bool_c/create.h>
#include <mu/script/bool_c/equal.h>
#include <mu/script/chain/operation.h>
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
#include <mu/script/ast/extension.h>
#include <mu/script/closure/create_single.h>

#include <gc_cpp.h>

mu::script::extensions::node * mu::script::api::core ()
{
	auto result (new (GC) mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"~")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::identity::operation);
	result->extensions->extensions_m [std::wstring (L"`")] = new (GC) mu::script::string::extension;
	result->extensions->extensions_m [std::wstring (L"`a")] = new (GC) mu::script::astring::extension;
	result->extensions->extensions_m [std::wstring (L"#")] = new (GC) mu::script::integer::extension;
	result->extensions->extensions_m [std::wstring (L".ast")] = new (GC) mu::script::ast::extension;
	result->extensions->extensions_m [std::wstring (L".apply")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::closure::create_single);
	return result;
}

mu::script::extensions::node * mu::script::api::full ()
{
	auto result (new (GC) mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"identity")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::identity::operation);
	result->extensions->extensions_m [std::wstring (L"ast/read_from_file")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::ast::read_from_file);
	result->extensions->extensions_m [std::wstring (L"ast/merge")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::ast::merge);
	result->extensions->extensions_m [std::wstring (L"astring/truncate")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::astring::truncate);
	result->extensions->extensions_m [std::wstring (L"bool_c/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::bool_c::create);
	result->extensions->extensions_m [std::wstring (L"bool_c/equal")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::bool_c::equal);
	result->extensions->extensions_m [std::wstring (L"chain/operation")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::chain::operation);
	result->extensions->extensions_m [std::wstring (L"extensions/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::extensions::create);
	result->extensions->extensions_m [std::wstring (L"extensions/merge_package")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::extensions::merge_package);
	result->extensions->extensions_m [std::wstring (L"integer/equal")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::integer::equal);
	result->extensions->extensions_m [std::wstring (L"integer/subtract")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::integer::subtract);
	result->extensions->extensions_m [std::wstring (L"print/operation")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::print::operation);
	result->extensions->extensions_m [std::wstring (L"package/add")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::package::add);
	result->extensions->extensions_m [std::wstring (L"package/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::package::create);
	result->extensions->extensions_m [std::wstring (L"package/get")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::package::get);
	result->extensions->extensions_m [std::wstring (L"package/remove")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::package::remove);
	result->extensions->extensions_m [std::wstring (L"times/operation")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::times::operation);
	return result;
}