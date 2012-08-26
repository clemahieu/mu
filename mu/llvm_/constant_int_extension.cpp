#include <mu/llvm_/constant_int_extension.h>

#include <mu/io/tokens_implementor.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/integer_extension.h>
#include <mu/llvm_/value_node.h>
#include <mu/script/integer_node.h>
#include <mu/script/closure_single.h>
#include <mu/llvm_/constant_int_create.h>
#include <mu/llvm_/apint_node.h>
#include <mu/llvm_/context_node.h>
#include <mu/io/keywording_keywording.h>
#include <mu/io/keywording_error.h>

#include <sstream>

#include <gc_cpp.h>

mu::llvm_::constant_int::extension::extension (mu::io::keywording::keywording & keywording_a, mu::llvm_::context::node * context_a):
context (context_a),
keywording (keywording_a),
have_keyword (false),
have_bits (false)
{
}

void mu::llvm_::constant_int::extension::operator () (mu::io::tokens::token * token_a)
{
    if (!have_keyword)
    {
        have_keyword = true;
    }
    else
    {
        if (!have_bits)
        {
            have_bits = true;
            auto bits_identifier (dynamic_cast <mu::io::tokens::identifier *> (token_a));
            if (bits_identifier != nullptr)
            {
                std::wstring characters (bits_identifier->string.begin (), bits_identifier->string.end ());
                auto bits_l (mu::script::integer::core_d (keywording.errors, characters));
				if (bits_l != nullptr)
				{
                    bits = bits_l->value;
                }
                else
                {
                    keywording.state.push (new (GC) mu::io::keywording::error);
					mu::stringstream message;
					message << L"Unable to parse bits number: ";
					message << bits_identifier->string;
					keywording.errors (message.str ());
                }
            }
        }
        else
        {
			auto number_identifier (dynamic_cast <mu::io::tokens::identifier *> (token_a));
			if (number_identifier != nullptr)
			{
                auto number (mu::script::integer::core (keywording.errors, number_identifier->string));
                if (number != nullptr)
                {
                    auto node (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_int::create));
                    node->closed.push_back (context);
                    node->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, bits)));
                    node->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (bits, number->value)));
                    keywording.state.pop ();
                    keywording (new (GC) mu::io::tokens::left_square (token_a->context));
                    keywording (new (GC) mu::io::tokens::value (token_a->context, node));
                    keywording (new (GC) mu::io::tokens::right_square (token_a->context));
                }
            }
            else
            {
                mu::stringstream message;
                message << L"Unable to parse number: ";
                message << number_identifier->string;
                keywording.state.push (new (GC) mu::io::keywording::error);
            }
        }
    }
}