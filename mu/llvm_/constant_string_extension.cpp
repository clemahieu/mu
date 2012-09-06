#include <mu/llvm_/constant_string_extension.h>

#include <mu/io/tokens_implementor.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/script/closure_single.h>
#include <mu/llvm_/constant_string_create.h>
#include <mu/llvm_/module_node.h>
#include <mu/llvm_/context_node.h>
#include <mu/io/analyzer_analyzer.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::constant_string::extension::extension (mu::io::analyzer::analyzer & analyzer_a, mu::llvm_::module::node * module_a)
	: module (module_a),
    analyzer (analyzer_a),
    have_keyword (false)
{
}

void mu::llvm_::constant_string::extension::operator () (mu::io::tokens::token const & token_a)
{
    if (!have_keyword)
    {
        have_keyword = true;
    }
    else
    {
		auto identifier (dynamic_cast <mu::io::tokens::identifier const *> (&token_a));
		if (identifier != nullptr)
		{
			auto node (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_string::create ()));
			node->closed.push_back (new (GC) mu::llvm_::context::node (&module->module->getContext ()));
			node->closed.push_back (module);
			node->closed.push_back (new (GC) mu::script::string::node (identifier->string));
            analyzer.state.pop ();
            analyzer (mu::io::tokens::left_square (token_a.context));
            analyzer (mu::io::tokens::value (token_a.context, node));
            analyzer (mu::io::tokens::right_square (token_a.context));
		}
		else
		{
			analyzer.errors (U"Constant_string extension requires its argument to be an identifer");
		}
	}
}