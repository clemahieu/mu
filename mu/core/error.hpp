#pragma once

#include <iostream>

namespace mu
{
    namespace core
    {
        enum class error_type
        {
            unknown,
            unknown_control_character,
            terminator_token_too_long,
            end_of_stream_inside_complex_identifier,
            non_hex_character,
            end_of_stream_inside_region_comment,
            expecting_type_in_parameters,
            unknown_expression_subclass,
            no_value_at_index,
            value_has_only_one_element,
            expecting_one_value,
            node_is_not_a_value,
            expecting_a_type,
            result_branch_is_not_distinct,
            expecting_a_function,
            expecting_a_module,
            expecting_a_target,
            unit_cannot_be_target_of_call,
            expecting_first_argument_to_be_call_target,
            expecting_a_call_target,
            cycle_in_expressions,
            argument_type_does_not_match_parameter_type,
            argument_to_function_is_not_a_value,
            pointer_does_not_point_to_a_function,
            only_function_pointers_can_be_target_of_call,
            join_arguments_must_be_values,
            branches_are_not_disjoint,
            joining_types_are_different,
            must_be_joining_at_least_two_values,
            if_instruction_expects_one_bit_integer,
            if_instruction_expects_integer_type_value,
            if_instruction_expects_a_value_argument,
            if_instruction_expects_one_argument,
            add_arguments_must_have_same_bit_width,
            add_arguments_must_be_integers,
            add_arguments_must_be_values,
            add_expects_two_arguments,
            arguments_are_disjoint,
            expecting_function,
            expecting_function_or_end_of_stream,
            function_name_already_used,
            expecting_identifier,
            expecting_function_name,
            parsing_parameters_expecting_left_square,
            unable_to_use_identifier,
            parsing_parameters_expecting_identifier,
            expecting_a_parameter_name,
            expecting_type_or_right_square,
            expecting_expression,
            expecting_left_square,
            expecting_identifier_or_right_square,
            expecting_result_reference,
            expecting_right_square,
            bit_width_too_wide,
            unable_to_convert_number_to_unsigned_integer,
            expecting_argument_or_right_square,
            expecting_name,
            expecting_identifier_or_left_square,
            unknown_token_in_let_statement,
            expecting_expression_or_right_square,
            expecting_loop_body,
            expecting_result_set_or_right_square,
            expecting_loop_results,
            already_parsing_predicates,
            unresolved_symbols,
            incorrect_number_of_arguments,
            expecting_a_number,
            error_converting_string_to_number,
            store_expects_two_arguments,
            store_arguments_must_be_values,
            store_right_argument_pointer_type,
            store_right_pointed_type_doesnt_match_left,
            load_expects_one_argument,
            load_argument_must_be_values,
            load_argument_pointer_type,
            mismatch_number_of_arguments_number_of_parameters,
            loop_argument_must_be_value,
            loop_result_must_be_value,
			loop_not_enough_branches,
			icmp_expects_predicate_two_arguments,
			icmp_first_argument_predicate,
			icmp_left_argument_value,
			icmp_right_argument_value,
			icmp_arguments_integers,
			icmp_arguments_same_type,
			branch_analyzer_leaves_exist,
			branch_analyzer_ancestor_exists,
			branch_analyzer_already_ancestor,
			branch_analyzer_disjoint,
			branch_analyzer_intersection_exists
        };
        class error
        {
        public:
            virtual ~error ();
            virtual void output (std::ostream & out) = 0;
            std::string string ();
            virtual mu::core::error_type type () = 0;
        };
    }
}