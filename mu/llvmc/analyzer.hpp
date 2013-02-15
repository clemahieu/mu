#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace core
    {
        class error;
    }
    namespace llvmc
    {
        namespace skeleton
        {
            class node;
            class module;
            class expression;
            class definite_expression;
            class function;
        }
        namespace ast
        {
            class node;
            class expression;
            class definite_expression;
            class function;
        }
        class module_result
        {
        public:
            mu::llvmc::skeleton::module * module;
            mu::core::error * error;
        };
        class analyzer_routine
        {
        public:
            analyzer_routine ();
            module_result analyze (mu::llvmc::ast::node * module_a);            
            mu::llvmc::module_result result;
            void process_parameters (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            void process_results (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            mu::llvmc::skeleton::node * process_node (mu::llvmc::ast::node * node_a);
            mu::llvmc::skeleton::definite_expression * process_definite_expression (mu::llvmc::ast::definite_expression * expression_a);
            mu::map <mu::llvmc::ast::node *, mu::llvmc::skeleton::node *> already_generated;
            mu::set <mu::llvmc::ast::expression *> current_expression_generation;
        };
        class analyzer
        {
        public:
            module_result analyze (mu::llvmc::ast::node * module_a);
        };
    }
}