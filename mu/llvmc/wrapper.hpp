#pragma once

#include <mu/llvmc/ast.hpp>

namespace llvm
{
    class Type;
    class IntegerType;
    class Value;
    class LLVMContext;
}
namespace mu
{
    namespace llvmc
    {
        namespace wrapper
        {
            class type : public mu::llvmc::ast::node
            {
            public:
                virtual llvm::Type * real_type ();
            };
            class structure_type : public mu::llvmc::wrapper::type
            {
            public:
                structure_type (llvm::LLVMContext & context_a);
                llvm::LLVMContext & context;
            };
            class group_type : public mu::llvmc::wrapper::structure_type
            {
            public:
                mu::vector <mu::llvmc::wrapper::type *> elements;
                llvm::Type * real_type () override;                
            };
            class set_type : public mu::llvmc::wrapper::structure_type
            {
            public:
                mu::vector <mu::llvmc::wrapper::type *> elements;
                llvm::Type * real_type () override;
            };
            class integer_type : public mu::llvmc::wrapper::type
            {
            public:
                integer_type (llvm::IntegerType * type_a);
                llvm::Type * real_type () override;
                llvm::IntegerType * type_m;
            };
            class branch_type : public mu::llvmc::wrapper::structure_type
            {
            public:
                mu::llvmc::wrapper::integer_type * selector;
                mu::vector <mu::llvmc::wrapper::set_type *> elements;
                llvm::Type * real_type () override;
            };
            class function_type : public mu::llvmc::wrapper::type
            {
            public:
                mu::vector <mu::llvmc::wrapper::type *> parameters;
                mu::llvmc::wrapper::branch_type result;
            };
            class value : public mu::llvmc::ast::node
            {
            public:
                value (llvm::Value * value_a);
                llvm::Value * value_m;
                mu::llvmc::wrapper::type * type;
            };
            class function : public mu::llvmc::wrapper::value
            {
            public:
                llvm::Function * function_m;
                mu::llvmc::wrapper::function_type * type;
            };
        }
    }
}