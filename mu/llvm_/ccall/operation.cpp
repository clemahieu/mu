#include <mu/llvm_/ccall/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/instructions/call.h>
#include <mu/llvm_/basic_block/split_return.h>
#include <mu/script/check.h>
#include <mu/script/integer/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

mu::llvm_::ccall::operation::operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> call_a)
	: block (block_a),
	call (call_a)
{
}

bool mu::llvm_::ccall::operation::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size () > 2)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters (0)));
		auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters (1)));
		auto three (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters (2)));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				if (three.get () != nullptr)
				{
					if (two->type->type () == three->type->type ())
					{
						auto bool_type (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node> (one->type));
						if (bool_type.get () != nullptr)
						{
							if (bool_type->integer_type ()->getBitWidth () == 1)
							{
								llvm::LLVMContext & context (bool_type->integer_type ()->getContext ());
								auto true_block (llvm::BasicBlock::Create (context, llvm::Twine (), block->block->getParent ()));
								auto false_block (llvm::BasicBlock::Create (context, llvm::Twine (), block->block->getParent ()));
								auto end_block (llvm::BasicBlock::Create (context, llvm::Twine (), block->block->getParent ()));
								block->block->getInstList ().push_back (llvm::BranchInst::Create (true_block, false_block, one->value ()));
								block->block = true_block;
								auto size (boost::make_shared <mu::script::integer::node> ());
								context_a.push (size);
								context_a.push (call);
								context_a.push (two);
								for (auto i (context_a.parameters_begin () + 3), j (context_a.parameters_end () + 0); i != j; ++i)
								{
									context_a.push (*i);
								}
								valid = context_a ();
								size->value = context_a.working_size ();
								true_block->getInstList ().push_back (llvm::BranchInst::Create (end_block));
								block->block = false_block;
								context_a.slide ();
								context_a.push (call);
								context_a.push (three);
								for (auto i (context_a.parameters_begin () + 3), j (context_a.parameters_end () + 0); i != j; ++i)
								{
									context_a.push (*i);
								}
								valid = valid & context_a ();
								context_a.slide ();
								false_block->getInstList ().push_back (llvm::BranchInst::Create (end_block));
								block->block = end_block;
								if (valid)
								{
									for (auto i (context_a.locals_begin ()), j (context_a.locals_begin () + size->value), k (context_a.locals_begin () + size->value), l (context_a.locals_end ()); i != j && k != l; ++i, ++k)
									{
										auto i_value (boost::dynamic_pointer_cast <mu::llvm_::value::node> (*i));
										auto k_value (boost::dynamic_pointer_cast <mu::llvm_::value::node> (*k));
										if (i_value.get () != nullptr && k_value.get () != nullptr)
										{
											auto i_type (i_value->type->type ());
											auto k_type (k_value->type->type ());
											if (i_type == k_type)
											{
												auto phi (llvm::PHINode::Create (i_type, 2));
												phi->addIncoming (i_value->value (), true_block);
												phi->addIncoming (k_value->value (), false_block);
												end_block->getInstList ().push_back (phi);
												context_a.push (boost::make_shared <mu::llvm_::value::node> (phi, i_value->type));
											}
											else
											{
												context_a.errors (L"Branch types are not the same");
												valid = false;
											}
										}
										else
										{
											context_a.errors (L"Function returned a non-value");
											valid = false;
										}										
									}
								}
							}
							else
							{
								context_a.errors (L"First ccall argument must be one bit");
								valid = false;
							}
						}
						else
						{
							context_a.errors (L"First ccall argument must be an integer");
							valid = false;
						}
					}
					else
					{
						context_a.errors (L"Branch functions must be the same type");
						valid = false;
					}
				}
				else
				{
					mu::script::invalid_type (context_a, context_a.parameters (2), typeid (mu::llvm_::value::node), 2);
					valid = false;
				}
			}
			else
			{
				mu::script::invalid_type (context_a, context_a.parameters (1), typeid (mu::llvm_::value::node), 1);
				valid = false;
			}
		}
		else
		{
			mu::script::invalid_type (context_a, context_a.parameters (0), typeid (mu::llvm_::value::node), 0);
			valid = false;
		}
	}
	else
	{
		context_a.errors (L"Ccall operation requires at least three arguments");
		valid = false;
	}
	return valid;
}