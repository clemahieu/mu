#include <mu/llvm_/ccall.operation.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/value.node.h>
#include <mu/llvm_/integer_type.node.h>
#include <mu/llvm_/basic_block.node.h>
#include <mu/llvm_/instructions.call.h>
#include <mu/llvm_/basic_block.split_return.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <boost/make_shared.hpp>

mu::llvm_::ccall::operation::operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> call_a)
	: block (block_a),
	call (call_a)
{
}

void mu::llvm_::ccall::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 2)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [1]));
		auto three (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [2]));
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
								std::vector <boost::shared_ptr <mu::core::node>> a1;
								std::vector <boost::shared_ptr <mu::core::node>> r1;
								a1.push_back (two);
								for (auto i (parameters.begin () + 3), j (parameters.end () + 0); i != j; ++i)
								{
									a1.push_back (*i);
								}
								call->perform (errors_a, a1, r1);
								true_block->getInstList ().push_back (llvm::BranchInst::Create (end_block));
								block->block = false_block;
								std::vector <boost::shared_ptr <mu::core::node>> a2;
								std::vector <boost::shared_ptr <mu::core::node>> r2;
								a2.push_back (three);
								for (auto i (parameters.begin () + 3), j (parameters.end () + 0); i != j; ++i)
								{
									a2.push_back (*i);
								}
								call->perform (errors_a, a2, r2);
								false_block->getInstList ().push_back (llvm::BranchInst::Create (end_block));
								block->block = end_block;
								if (! (*errors_a) ())
								{
									for (auto i (r1.begin ()), j (r1.end ()), k (r2.begin ()), l (r2.end ()); i != j && k != l; ++i, ++k)
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
												results.push_back (boost::make_shared <mu::llvm_::value::node> (phi, i_value->type));
											}
											else
											{
												(*errors_a) (L"Branch types are not the same");
											}
										}
										else
										{
											(*errors_a) (L"Function returned a non-value");
										}										
									}
								}
							}
							else
							{
								(*errors_a) (L"First ccall argument must be one bit");
							}
						}
						else
						{
							(*errors_a) (L"First ccall argument must be an integer");
						}
					}
					else
					{
						(*errors_a) (L"Branch functions must be the same type");
					}
				}
				else
				{
					invalid_type (errors_a, parameters [2], 2);
				}
			}
			else
			{
				invalid_type (errors_a, parameters [1], 1);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		(*errors_a) (L"Ccall operation requires at least three arguments");
	}
}
