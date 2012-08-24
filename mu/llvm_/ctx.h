#pragma once

#include <mu/core/types.h>
#include <mu/core/check.h>

namespace mu
{
    namespace core
    {
        class node;
        namespace errors
        {
            class error_target;
        }
    }
    namespace llvm_
    {
        namespace basic_block
        {
            class node;
        }
        namespace context
        {
            class node;
        }
        namespace function
        {
            class node;
        }
        namespace module
        {
            class node;
        }
        template <typename ...U>
        class check_count;
        template <>
        class check_count <>
        {
        public:
            size_t operator () ()
            {
                return 0;
            }
        };
        template <typename T, typename ...U>
        class check_count <T, U...>
        {
        public:
            size_t operator () ()
            {
                return 1 + check_count <U...> () ();
            }
        };
        template <typename ...T>
        size_t count ()
        {
            auto result ((check_count <T...> ()) ());
            return result;
        }
        template <typename ...U>
        class check_types;
        template <>
        class check_types <>
        {
        public:
            bool operator () (mu::vector <mu::core::node *> & working_a, mu::core::errors::error_target & errors_a, size_t index)
            {
                return true;
            }
        };
        template <typename T, typename ...U>
        class check_types <T, U...>
        {
        public:
            bool operator () (mu::vector <mu::core::node *> & working_a, mu::core::errors::error_target & errors_a, size_t index)
            {
                auto node (working_a [index]);
                bool result (dynamic_cast <T *> (node) != nullptr);
                if (result)
                {
                    result = check_types <U...> () (working_a, errors_a, index + 1);
                }
                else
                {
                    mu::core::type_fail (errors_a, typeid (T), node, index);
                }
                return result;
            }
        };
        class ctx
        {
        public:
            ctx (mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::llvm_::function::node * function_a, mu::llvm_::basic_block::node * block_a, mu::core::errors::error_target & errors_a);
            template <typename ...T>
            bool check ()
            {
                auto count_l (count <T...> ());
                bool result (working.size () == count_l);
                if (result)
                {
                    result = check_types <T...> () (working, errors, 0);
                }
                else
                {
                    mu::core::size_fail (errors, count_l, working.size ());
                }
                return result;
            }
            mu::vector <mu::core::node *> working;
            mu::llvm_::context::node * context;
            mu::llvm_::module::node * module;
            mu::llvm_::function::node * function;
            mu::llvm_::basic_block::node * block;
            mu::core::errors::error_target & errors;
        };
    }
}