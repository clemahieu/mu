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
            class scoped : public mu::llvmc::ast::node
            {
            public:
                virtual mu::llvmc::availability::node * availability () = 0;
            };
            class base : public mu::llvmc::ast::scoped
            {
            public:
                base (mu::llvmc::availability::node * availability_a);
                mu::llvmc::availability::node * availability () override;
                mu::llvmc::availability::node * availability_m;
            };
            class argument : public mu::llvmc::ast::base
            {
            public:
                argument (mu::llvmc::wrapper::type * type_a, mu::llvmc::availability::node * availability_a);
                mu::llvmc::wrapper::type * type;
            };
            class result : public mu::llvmc::ast::scoped
            {
            public:
                result (mu::llvmc::wrapper::type * type_a);
                mu::llvmc::availability::node * availability () override;
                mu::llvmc::wrapper::type * type;
                mu::llvmc::ast::scoped * value;
            };
            class expression : public mu::llvmc::ast::base
            {
            public:
                expression (mu::llvmc::availability::node * availability_a);
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class value : public mu::llvmc::ast::base
            {
            public:
                value (mu::llvmc::availability::node * availability_a);
            };
            class function : public mu::llvmc::ast::base
            {
            public:
                function (mu::llvmc::availability::module * availability_a);
                mu::llvmc::availability::function * entry;
                mu::string name;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::vector <mu::llvmc::ast::node *>> results;
                mu::vector <mu::llvmc::ast::expression *> roots;
            };
            class module : public mu::llvmc::ast::base
            {
            public:
                module ();
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
            class instruction : public mu::llvmc::ast::base
            {
            public:
                instruction (mu::llvmc::availability::module * availability_a, mu::llvmc::ast::instruction_type type_a);
                mu::llvmc::ast::instruction_type type;
            };
        }
    }
}