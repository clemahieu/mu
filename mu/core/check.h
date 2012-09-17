#pragma once

#include <vector>
#include <typeinfo>

#include <mu/core/context.h>

namespace mu
{
    namespace core
    {
        class node;
        namespace errors
        {
            class error_target;
        }
        void size_fail (mu::core::errors::error_target & errors_a, size_t expected, size_t actual);
        void type_fail (mu::core::errors::error_target & errors_a, std::type_info const & expected, mu::core::node * actual, size_t position);
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
            check_count <T...> check_l ;
            auto result (check_l ());
            return result;
        }
        template <typename ...U>
        class check_types;
        template <>
        class check_types <>
        {
        public:
            bool operator () (mu::core::context & nodes_a, size_t index)
            {
                return true;
            }
        };
        template <typename T, typename ...U>
        class check_types <T, U...>
        {
        public:
            bool operator () (mu::core::context & nodes_a, size_t index)
            {
                auto node (nodes_a.parameters (index));
                bool result (dynamic_cast <T *> (node) != nullptr);
                if (result)
                {
                    result = check_types <U...> () (nodes_a, index + 1);
                }
                else
                {
                    type_fail (nodes_a.errors, typeid (T), node, index);
                }
                return result;
            }
        };
        template <typename ...T>
        bool check (mu::core::context & nodes_a)
        {
            auto count_l (count <T...> ());
            bool result (nodes_a.parameters_size () == count_l);
            if (result)
            {
                result = check_types <T...> () (nodes_a, 0);
            }
            else
            {
                size_fail (nodes_a.errors, count_l, nodes_a.parameters_size ());
            }
            return result;
        }
    }
}