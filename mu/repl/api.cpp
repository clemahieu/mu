#include <mu/repl/api.h>

#include <mu/script/parser_scope_node.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/string_extension.h>
#include <mu/script/astring_extension.h>
#include <mu/script/integer_extension.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/identity.h>
#include <mu/script/loads_operation.h>
#include <mu/script/loadb_operation.h>
#include <mu/script/print_operation.h>
#include <mu/repl/quit/operation.h>
#include <mu/script/string_concatenate.h>
#include <mu/script/string_equal.h>
#include <mu/script/file_open.h>
#include <mu/script/file_close.h>
#include <mu/script/file_path_from_string.h>

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
    map [mu::string (U"~")] = new (GC) mu::script::identity;
    map [mu::string (U"close")] = new (GC) mu::script::file::close;
    map [mu::string (U"concat")] = new (GC) mu::script::string::concatenate;
    map [mu::string (U"equal")] = new (GC) mu::script::string::equal;
    map [mu::string (U"loadb")] = new (GC) mu::script::loadb::operation;
    map [mu::string (U"loads")] = new (GC) mu::script::loads::operation;
    map [mu::string (U"open")] = new (GC) mu::script::file::open;
    map [mu::string (U"path")] = new (GC) mu::script::file::path_from_string;
    map [mu::string (U"print")] = new (GC) mu::script::print::operation;
    map [mu::string (U"quit")] = new (GC) mu::repl::quit::operation (repl_a);
	return result;
}