#include <mu/llvm_/constant_string/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/closure/single.h>
#include <mu/llvm_/constant_string/create.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/value.h>
#include <mu/io/keywording/keywording.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/left_square.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

mu::llvm_::constant_string::extension::extension (mu::io::keywording::keywording & keywording_a, mu::llvm_::module::node * module_a)
	: module (module_a),
    keywording (keywording_a),
    have_keyword (false)
{
}

void mu::llvm_::constant_string::extension::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    if (!have_keyword)
    {
        have_keyword = true;
    }
    else
    {
		auto identifier (dynamic_cast <mu::io::tokens::identifier *> (token_a));
		if (identifier != nullptr)
		{
			auto node (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_string::create ()));
			node->closed.push_back (new (GC) mu::llvm_::context::node (&module->module->getContext ()));
			node->closed.push_back (module);
			node->closed.push_back (new (GC) mu::script::string::node (identifier->string));
            keywording.state.pop ();
            keywording (new (GC) mu::io::tokens::left_square, context_a);
            keywording (new (GC) mu::io::tokens::value (node), context_a);
            keywording (new (GC) mu::io::tokens::right_square, context_a);
		}
		else
		{
			keywording.errors (U"Constant_string extension requires its argument to be an identifer");
		}
	}
}