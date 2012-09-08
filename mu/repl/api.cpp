#include <mu/repl/api.h>

#include <mu/script/parser_scope_node.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/string_extension.h>
#include <mu/script/astring_extension.h>
#include <mu/script/integer_extension.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/identity_operation.h>
#include <mu/script/loads_operation.h>
#include <mu/script/loadb_operation.h>
#include <mu/script/print_operation.h>
#include <mu/repl/quit/operation.h>

#include <gc_cpp.h>

auto mu::repl::api::core (mu::repl::repl & repl_a) -> mu::script::parser_scope::node *
{
    auto result (new (GC) mu::script::parser_scope::node);
    auto & extensions (*result->extensions);
    auto & map (result->injected);
	extensions.add <mu::script::string::extension> (mu::string (U"`"));
	extensions.add <mu::script::astring::extension>(mu::string (U"a`"));
	extensions.add <mu::script::integer::extension> (mu::string (U"#"));
    extensions (mu::string (U"if"), new (GC) mu::script::tokens::keyword_if);
    map [mu::string (U"~")] = new (GC) mu::script::identity::operation;
    map [mu::string (U"loadb")] = new (GC) mu::script::loadb::operation;
    map [mu::string (U"loads")] = new (GC) mu::script::loads::operation;
    map [mu::string (U"print")] = new (GC) mu::script::print::operation;
    map [mu::string (U"quit")] = new (GC) mu::repl::quit::operation (repl_a);
	return result;
}