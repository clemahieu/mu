#include "icmp.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_script/string/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::icmp::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (check_size (errors_a, 3, parameters_a.size ()))
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters_a [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [1]));
		auto three (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [2]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				if (three.get () != nullptr)
				{
					llvm::ICmpInst::Predicate predicate (llvm::ICmpInst::Predicate::BAD_ICMP_PREDICATE);					
					std::wstring lower;
					std::transform (one->string.begin (), one->string.end (), lower.begin (), ::tolower);
					if (lower == std::wstring (L"eq"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_EQ;
					}
					else if (lower == std::wstring (L"ne"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_NE;
					}
					else if (lower == std::wstring (L"ugt"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_UGT;
					}
					else if (lower == std::wstring (L"uge"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_UGE;
					}
					else if (lower == std::wstring (L"ult"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_ULT;
					}
					else if (lower == std::wstring (L"ule"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_ULE;
					}
					else if (lower == std::wstring (L"sgt"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_SGT;
					}
					else if (lower == std::wstring (L"sge"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_SGE;
					}
					else if (lower == std::wstring (L"slt"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_SLT;
					}
					else if (lower == std::wstring (L"sle"))
					{
						predicate = llvm::ICmpInst::Predicate::ICMP_SLE;
					}
					if (predicate != llvm::ICmpInst::Predicate::BAD_ICMP_PREDICATE)
					{
						bool two_int (two->value ()->getType ()->isIntegerTy ());
						bool three_int (three->value ()->getType ()->isIntegerTy ());
						if (two_int && three_int)
						{
							size_t one_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
							size_t two_bits (three->value ()->getType ()->getPrimitiveSizeInBits ());
							if (one_bits == two_bits)
							{
								auto instruction (new llvm::ICmpInst (predicate, two->value (), three->value ()));
								context_a->getInstList ().push_back (instruction);
								results_a.push_back (boost::make_shared <lambda_p_llvm::value::node> (instruction));
							}
							else
							{
								std::wstringstream message;
								message << L"Bit widths don't match: ";
								message << one_bits;
								message << L" ";
								message << two_bits;
								(*errors_a) (message.str ());
							}
						}
						else
						{
							std::wstringstream message;
							message << L"Arguments are not integers: ";
							message << two_int;
							message << L" ";
							message << three_int;
							(*errors_a) (message.str ());
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Unknown predicate: ";
						message << lower;
						(*errors_a) (message.str ());
					}
				}
				else
				{
					invalid_type (errors_a, 2);
				}
			}
			else
			{
				invalid_type (errors_a, 1);
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}