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
                argument (mu::llvmc::ast::node * type_a);
                mu::llvmc::ast::node * type;
            };
            class loop_argument : public mu::llvmc::ast::node
            {
            public:
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::ast::node * written_type_a);
                mu::llvmc::ast::node * written_type;
                mu::llvmc::ast::node * value;
            };
            class expression : public mu::llvmc::ast::node
            {
            };
            class element : public mu::llvmc::ast::node
            {
            public:
                element (mu::llvmc::ast::node * node_a, size_t index_a);
                mu::llvmc::ast::node * node;
                size_t index;
            };
            class loop : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
                mu::vector <mu::vector <mu::llvmc::ast::node *>> results;
            };
            class definite_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class if_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::llvmc::ast::node * predicate;
                mu::vector <mu::llvmc::ast::node *> true_roots;
                mu::vector <mu::llvmc::ast::node *> false_roots;
            };
            class function : public mu::llvmc::ast::node
            {
            public:
                mu::llvmc::availability::function * entry;
                mu::string name;
                mu::vector <mu::llvmc::ast::argument *> parameters;
                mu::vector <mu::vector <mu::llvmc::ast::result *>> results;
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                mu::vector <mu::llvmc::ast::node *> functions;
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