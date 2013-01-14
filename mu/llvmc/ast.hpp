#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>

namespace mu
{
    namespace io
    {
        template <typename T>
        class stream;
        class token;
    }
    namespace llvmc
    {
        namespace availability
        {
            class node;
            class function;
            class module;
        }
        namespace wrapper
        {
            class type;
        }
        namespace ast
        {
            class node
            {
            public:
                virtual ~node ();
            };
            class argument : public mu::llvmc::ast::node
            {
            public:
                argument (mu::llvmc::wrapper::type * type_a);
                mu::llvmc::wrapper::type * type;
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::wrapper::type * written_type_a);
                mu::llvmc::wrapper::type * written_type;
                mu::llvmc::ast::node * value;
            };
            class expression : public mu::llvmc::ast::node
            {
            };
            class value : public mu::llvmc::ast::node
            {
            public:
            };
            class definite_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class if_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::llvmc::ast::expression * predicate;
                mu::vector <mu::llvmc::ast::expression *> true_roots;
                mu::vector <mu::llvmc::ast::expression *> false_roots;
            };
            class function : public mu::llvmc::ast::node
            {
            public:
                mu::llvmc::availability::function * entry;
                mu::string name;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::vector <mu::llvmc::ast::node *>> results;
                mu::vector <mu::llvmc::ast::expression *> roots;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                mu::vector <mu::llvmc::ast::function *> functions;
            };
            enum class instruction_type
            {
                add,
                and_i,
                ashr,
                bitcast,
                br,
                call,
                extractelement,
                extractvalue,
                fadd,
                fcmp,
                fdiv,
                fmul,
                fpext,
                fptoi,
                futosi,
                fptoui,
                fptrunc,
                frem,
                fsub,
                icmp,
                indirectbr,
                insertelement,
                insertvalue,
                inttoptr,
                invoke,
                landingpad,
                lshr,
                mul,
                or_i,
                phi,
                ptrtoint,
                resume,
                ret,
                sdiv,
                select,
                sext,
                shl,
                shufflevector,
                sitofp,
                srem,
                sub,
                switch_i,
                trunc,
                udiv,
                uitofp,
                unreachable,
                urem,
                vaarg,
                xor_i,
                zext
            };
            class instruction : public mu::llvmc::ast::node
            {
            public:
                instruction (mu::llvmc::ast::instruction_type type_a);
                mu::llvmc::ast::instruction_type type;
            };
        }
    }
}