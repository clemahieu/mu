#include <mu/llvmc/analyzer.hpp>

#include <mu/core/error_string.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <boost/lexical_cast.hpp>

#include <gc_cpp.h>

mu::llvmc::module_result mu::llvmc::analyzer::analyze (mu::llvmc::ast::node * module_a)
{
	mu::llvmc::analyzer_module analyzer_l;
	auto result (analyzer_l.analyze (module_a));
	return result;
}

mu::llvmc::analyzer_module::analyzer_module () :
module (new (GC) mu::llvmc::skeleton::module),
result_m ({nullptr, nullptr})
{
}

mu::llvmc::analyzer_function::analyzer_function (mu::llvmc::analyzer_module & module_a) :
result_m ({nullptr, nullptr}),
module (module_a)
{
}

void mu::llvmc::analyzer_function::process_parameters (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
	for (auto k (function_a->parameters.begin ()), l (function_a->parameters.end ()); k != l && result_m.error == nullptr; ++k)
	{
		auto type_l (process_type ((*k)->type));
		if (type_l != nullptr)
		{
			auto parameter_s (new (GC) mu::llvmc::skeleton::parameter (function_s->entry, type_l));
			already_generated [*k] = parameter_s;
			function_s->parameters.push_back (parameter_s);
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_type_in_parameters);
		}
	}
}

bool mu::llvmc::analyzer_function::process_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	auto result (false);
	auto existing (already_generated.find (node_a));
	if (existing == already_generated.end ())
	{
		auto existing_multi (already_generated_multi.find (node_a));
		if (existing_multi == already_generated_multi.end ())
		{
			auto existing_function (module.functions.find (node_a));
			if (existing_function == module.functions.end ())
			{
				auto definite_expression (dynamic_cast<mu::llvmc::ast::definite_expression *> (node_a));
				if (definite_expression != nullptr)
				{
					result = process_definite_expression (definite_expression);
				}
				else
				{
					auto value_node (dynamic_cast<mu::llvmc::ast::value *> (node_a));
					if (value_node != nullptr)
					{
						already_generated [node_a] = value_node->node_m;
					}
					else
					{
						auto element_node (dynamic_cast<mu::llvmc::ast::element *> (node_a));
						if (element_node != nullptr)
						{
							process_element (element_node);
						}
						else
						{
							auto function_node (dynamic_cast<mu::llvmc::ast::function *> (node_a));
							if (function_node != nullptr)
							{
								analyzer_function analyzer (*this);
								analyzer.analyze (function_node);
								already_generated [node_a] = analyzer.result_m.function;
								result_m.error = analyzer.result_m.error;
							}
							else
							{
								auto unit_node (dynamic_cast<mu::llvmc::ast::unit *> (node_a));
								if (unit_node != nullptr)
								{
									already_generated [node_a] = new (GC) mu::llvmc::skeleton::unit_value (module.module->global);
								}
								else
								{
									auto set (dynamic_cast<mu::llvmc::ast::set_expression *> (node_a));
									if (set != nullptr)
									{
										mu::vector <mu::llvmc::skeleton::node *> values;
										for (auto i : set->items)
										{
											auto multi (process_node (i));
											if (multi)
											{
												auto & values_l (already_generated_multi [i]);
												values.insert (values.end (), values_l.begin (), values_l.end ());
											}
											else
											{
												values.push_back (already_generated [i]);
											}
										}
										switch (values.size ())
										{
											case 1:
												already_generated [node_a] = values [0];
												break;
											default:
												result = true;
												already_generated_multi [node_a] = values;
												break;
										}
									}
									else
									{
										auto integer_type (dynamic_cast<mu::llvmc::ast::integer_type *> (node_a));
										if (integer_type != nullptr)
										{
											process_integer_type (integer_type);
										}
										else
										{
											auto pointer_type (dynamic_cast<mu::llvmc::ast::pointer_type *> (node_a));
											if (pointer_type != nullptr)
											{
												process_pointer_type (pointer_type);
											}
											else
											{
												auto constant_int (dynamic_cast<mu::llvmc::ast::constant_int *> (node_a));
												if (constant_int != nullptr)
												{
													process_constant_int (constant_int);
												}
												else
												{
													auto loop (dynamic_cast<mu::llvmc::ast::loop *> (node_a));
													if (loop != nullptr)
													{
														result = process_loop (loop);
													}
													else
													{
														assert (false);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else
			{
				already_generated [node_a] = existing_function->second;
			}
		}
		else
		{
			result = true;
		}
	}
	assert (result_m.error != nullptr || !result || (result && already_generated_multi.find (node_a) != already_generated_multi.end ()));
	assert (result_m.error != nullptr || !!result || (!result && already_generated.find (node_a) != already_generated.end ()));
	return result;
}

bool mu::llvmc::analyzer_function::process_loop (mu::llvmc::ast::loop * loop_a)
{
	auto result (false);
	auto loop_s (new (GC) mu::llvmc::skeleton::loop);
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
	size_t predicate_offset (~0);
	process_call_values (loop_a->arguments, loop_a->argument_predicate_offset, loop_s->arguments, most_specific_branch, predicate_offset);
	if (result_m.error == nullptr)
	{
		if (loop_s->arguments.size () == loop_a->parameters.size ())
		{
			auto loop_entry_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
			auto i (loop_a->parameters.begin ());
			auto j (loop_a->parameters.end ());
			auto k (loop_s->arguments.begin ());
			for (; i != j; ++i, ++k)
			{
				auto argument (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
				if (argument != nullptr)
				{
					auto new_parameter (new (GC) mu::llvmc::skeleton::loop_parameter (loop_entry_branch, static_cast<mu::llvmc::skeleton::value *> (*k)->type ()));
					loop_s->parameters.push_back (new_parameter);
					already_generated [*i] = new_parameter;
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Loop argument must be a value", mu::core::error_type::loop_argument_must_be_value);
				}
			}
			loop_a->for_each_results (
				[&]
				(mu::llvmc::ast::expression * expression_a, size_t)
				{
					auto multi (process_node (expression_a));
					if (multi)
					{
						for (auto i : already_generated_multi [expression_a])
						{
							auto value (dynamic_cast<mu::llvmc::skeleton::value *> (i));
							if (value != nullptr)
							{
								loop_s->results.push_back (value);
							}
							else
							{
								result_m.error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
							}
						}
					}
					else
					{
						auto value (dynamic_cast<mu::llvmc::skeleton::value *> (already_generated [expression_a]));
						if (value != nullptr)
						{
							loop_s->results.push_back (value);
						}
						else
						{
							result_m.error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
						}
					}
				},
				[&]
				(mu::llvmc::ast::expression * expression_a, size_t)
				{
					auto multi (process_node (expression_a));
					if (multi)
					{
						for (auto i : already_generated_multi [expression_a])
						{
							auto value (dynamic_cast<mu::llvmc::skeleton::value *> (i));
							if (value != nullptr)
							{
								loop_s->results.push_back (value);
							}
							else
							{
								result_m.error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
							}
						}
					}
					else
					{
						auto value (dynamic_cast<mu::llvmc::skeleton::value *> (already_generated [expression_a]));
						if (value != nullptr)
						{
							loop_s->results.push_back (value);
						}
						else
						{
							result_m.error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
						}
					}
				},
				[&]
				(mu::llvmc::ast::node * node_a, size_t)
				{
					loop_s->predicate_offsets.push_back (loop_s->results.size ());
				},
				[&]
				(mu::llvmc::ast::node * node_a, size_t)
				{
					loop_s->branch_ends.push_back (loop_s->results.size ());
				},
				[&]
				()
				{
					return result_m.error == nullptr;
				});
				assert (loop_s->predicate_offsets.size () == loop_s->branch_ends.size ());
				if (loop_s->branch_ends.size () >= 2)
				{
					bool feedback_branch (true);
					loop_s->for_each_branch (
						[&]
						(size_t begin, size_t end)
						{
							if (!feedback_branch)
							{						
								auto branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
								auto branch_size (end - begin);
								switch (branch_size)
								{
									case 0:
									{
										already_generated [loop_a] = new (GC) mu::llvmc::skeleton::loop_element_unit (branch, loop_s, begin);
										break;
									}
									case 1:
									{
										already_generated [loop_a] = new (GC) mu::llvmc::skeleton::loop_element_value (branch, loop_s, begin);
										break;
									}
									default:
									{
										result = true;
										auto & target (already_generated_multi [loop_a]);
										for (size_t k (begin), l (end); k != l && result_m.error == nullptr; ++k)
										{
											target.push_back (new (GC) mu::llvmc::skeleton::loop_element_value (branch, loop_s, k));
										}
										break;
									}
								}		
								feedback_branch = false;
							}
						});
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Loop must have a feedback branch and at least one exit branch", mu::core::error_type::loop_not_enough_branches);
				}
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Number of arguments does not match number of parameters", mu::core::error_type::mismatch_number_of_arguments_number_of_parameters);
		}
	}
	return result;
}

mu::llvmc::skeleton::number::number (uint64_t value_a) :
value (value_a)
{
}

mu::llvmc::skeleton::number * mu::llvmc::analyzer_function::process_number (mu::llvmc::ast::number * number_a)
{
	mu::llvmc::skeleton::number * result (nullptr);
	try
	{
		std::string data_l (number_a->number_m.begin (), number_a->number_m.end ());
		unsigned int value (boost::lexical_cast <unsigned int> (data_l));
		result = new (GC) mu::llvmc::skeleton::number (value);
	}
	catch (boost::bad_lexical_cast)
	{
		result_m.error = new (GC) mu::core::error_string (U"Unable to convert string to number", mu::core::error_type::error_converting_string_to_number);
	}
	return result;
}

void mu::llvmc::analyzer_function::process_constant_int (mu::llvmc::ast::constant_int * constant_a)
{
	try
	{
		std::string data_l (constant_a->bits.begin (), constant_a->bits.end ());
		unsigned int bits (boost::lexical_cast <unsigned int> (data_l));
		if (bits <= 1024)
		{
			auto number (dynamic_cast<mu::llvmc::ast::number *> (constant_a->number));
			if (number != nullptr)
			{
				auto number_l (process_number (number));
				if (number_l != nullptr)
				{
					already_generated [constant_a] = new (GC) mu::llvmc::skeleton::constant_integer (module.module->global, bits, number_l->value);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Expecting a number", mu::core::error_type::expecting_a_number);
			}
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		result_m.error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer);
	}
}

void mu::llvmc::analyzer_function::process_element (mu::llvmc::ast::element * element_a)
{
	auto multi (process_node (element_a->node));
	if (result_m.error == nullptr)
	{
		if (multi)
		{
			auto existing (already_generated_multi.find (element_a->node));
			if (existing->second.size () > element_a->index)
			{
				already_generated [element_a] = existing->second [element_a->index];
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"No value at index", mu::core::error_type::no_value_at_index);
			}
		}
		else
		{
			if (element_a->index == 0)
			{
				already_generated [element_a] = already_generated [element_a->node];
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Value has only one element", mu::core::error_type::value_has_only_one_element);
			}
		}
	}
}

void mu::llvmc::analyzer_function::process_single_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	auto multi (process_node (node_a));
	if (multi)
	{
		result_m.error = new (GC) mu::core::error_string (U"Expecting 1 value", mu::core::error_type::expecting_one_value);
	}
}

mu::llvmc::skeleton::value * mu::llvmc::analyzer_function::process_value (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	mu::llvmc::skeleton::value * result (nullptr);
	process_single_node (node_a);
	if (result_m.error == nullptr)
	{
		result = dynamic_cast<mu::llvmc::skeleton::value *> (already_generated [node_a]);
		if (result == nullptr)
		{
			result_m.error = new (GC) mu::core::error_string (U"Node is not value", mu::core::error_type::node_is_not_a_value);
		}
	}
	return result;
}

mu::llvmc::skeleton::type * mu::llvmc::analyzer_function::process_type (mu::llvmc::ast::node * node_a)
{
	mu::llvmc::skeleton::type * result (nullptr);
	process_single_node (node_a);
	if (result_m.error == nullptr)
	{
		auto node_l (already_generated [node_a]);
		result = dynamic_cast<mu::llvmc::skeleton::type *> (node_l);
	}
	return result;
}

void mu::llvmc::analyzer_function::process_pointer_type (mu::llvmc::ast::pointer_type * type_a)
{
	auto pointed_type (process_type (type_a->pointed_type));
	if (pointed_type != nullptr)
	{
		already_generated [type_a] = new (GC) mu::llvmc::skeleton::pointer_type (pointed_type);
	}
}

void mu::llvmc::analyzer_function::process_integer_type (mu::llvmc::ast::integer_type * type_a)
{
	try
	{
		std::string data_l (type_a->bits.begin (), type_a->bits.end ());
		unsigned int bits (boost::lexical_cast <unsigned int> (data_l));
		if (bits <= 1024)
		{
			already_generated [type_a] = new (GC) mu::llvmc::skeleton::integer_type (bits);
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		result_m.error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer);
	}
}

void mu::llvmc::analyzer_function::process_results (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
	mu::set <mu::llvmc::skeleton::branch *> result_branches;
	auto most_specific_branch (module.module->global);
	function_a->for_each_results (
			[&]
			(mu::llvmc::ast::result * result_a, size_t index_a)
			{
				auto type (process_type (result_a->written_type));
				if (type != nullptr)
				{
					auto value (process_value (result_a->value));
					if (value != nullptr)
					{
						function_s->results.push_back (new (GC) mu::llvmc::skeleton::result (type, value));
								calculate_most_specific (most_specific_branch, value->branch);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type);
				}
				assert (most_specific_branch != nullptr || result_m.error != nullptr);
			},
	[&]
	(mu::llvmc::ast::expression * result_a, size_t)
	{
		auto multi (process_node (result_a));
		if (result_m.error == nullptr)
		{
			if (multi)
			{
				for (auto i : already_generated_multi [result_a])
				{
					assert (dynamic_cast<mu::llvmc::skeleton::value *> (i) != nullptr);
							function_s->results.push_back (i);
							calculate_most_specific (most_specific_branch, static_cast<mu::llvmc::skeleton::value *> (i)->branch);
				}
			}
			else
			{
				assert (dynamic_cast<mu::llvmc::skeleton::value *> (already_generated [result_a]) != nullptr);
						auto value (static_cast<mu::llvmc::skeleton::value *> (already_generated [result_a]));
						function_s->results.push_back (value);
						calculate_most_specific (most_specific_branch, value->branch);
			}
		}
		assert (most_specific_branch != nullptr || result_m.error != nullptr);
	},
	[&]
	(mu::llvmc::ast::node *, size_t)
	{
		function_s->predicate_offsets.push_back (function_s->results.size ());
	},
	[&]
	(mu::llvmc::ast::node *, size_t)
	{
		auto existing (result_branches.find (most_specific_branch));
		if (existing == result_branches.end ())
		{
			result_branches.insert (most_specific_branch);
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Result branch is not distinct", mu::core::error_type::result_branch_is_not_distinct);
		}
		most_specific_branch = module.module->global;
				function_s->branch_ends.push_back (function_s->results.size ());
	},
	[&]
	()
	{
		return result_m.error == nullptr;
	}
	);
}

mu::llvmc::function_result mu::llvmc::analyzer_function::analyze (mu::llvmc::ast::node * function_a)
{
	auto function_l (dynamic_cast<mu::llvmc::ast::function *> (function_a));
	if (function_l != nullptr)
	{
		assert (function_l->branch_ends.size () == function_l->predicate_offsets.size ());
		auto function_s (new (GC) mu::llvmc::skeleton::function (module.module->global));
		module.module->functions [function_l->name] = function_s;
		module.functions [function_a] = function_s;
		process_parameters (function_l, function_s);
		process_results (function_l, function_s);
		result_m.function = function_s;
	}
	else
	{
		result_m.error = new (GC) mu::core::error_string (U"Expecting a function", mu::core::error_type::expecting_a_function);
	}
	return result_m;
}

mu::llvmc::module_result mu::llvmc::analyzer_module::analyze (mu::llvmc::ast::node * module_a)
{
	auto module_s (module);
	auto module_l (dynamic_cast<mu::llvmc::ast::module *> (module_a));
	if (module_l != nullptr)
	{
		for (auto i (module_l->functions.begin ()), j (module_l->functions.end ()); i != j && result_m.error == nullptr; ++i)
		{
			auto existing (functions.find (*i));
			if (existing == functions.end ())
			{
				analyzer_function analyzer (*this);
				analyzer.analyze (*i);
				result_m.error = analyzer.result_m.error;
			}
		}
	}
	else
	{
		result_m.error = new (GC) mu::core::error_string (U"Expecting a module", mu::core::error_type::expecting_a_module);
	}
	if (result_m.error == nullptr)
	{
		result_m.module = module_s;
	}
	return result_m;
}

bool mu::llvmc::analyzer_function::process_definite_expression (mu::llvmc::ast::definite_expression * expression_a)
{
	auto result (false);
	auto existing (current_expression_generation.find (expression_a));
	if (existing == current_expression_generation.end ())
	{
		current_expression_generation.insert (expression_a);
		if (!expression_a->arguments.empty ())
		{
			auto multi (process_node (expression_a->arguments [0]));
			if (result_m.error == nullptr)
			{
				mu::llvmc::skeleton::node * target;
				if (multi)
				{
					auto & generated = already_generated_multi [expression_a->arguments [0]];
					if (!generated.empty ())
					{
						target = generated [0];
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Expecting target", mu::core::error_type::expecting_a_target);
					}
				}
				else
				{
					target = already_generated [expression_a->arguments [0]];
				}
				if (result_m.error == nullptr)
				{
					auto value (dynamic_cast<mu::llvmc::skeleton::value *> (target));
					if (value != nullptr)
					{
						result = process_value_call (expression_a);
					}
					else
					{
						auto marker (dynamic_cast<mu::llvmc::skeleton::marker *> (target));
						if (marker != nullptr)
						{
							result = process_marker (expression_a);
						}
						else
						{
							auto join (dynamic_cast<mu::llvmc::skeleton::join *> (target));
							if (join != nullptr)
							{
								result = process_join (expression_a);
							}
							else
							{
								result_m.error = new (GC) mu::core::error_string (U"Expecting first argument to be call target", mu::core::error_type::expecting_first_argument_to_be_call_target);
							}
						}
					}
				}
			}
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Expecting a call target", mu::core::error_type::expecting_a_call_target);
		}
	}
	else
	{
		result_m.error = new (GC) mu::core::error_string (U"Cycle in expressions", mu::core::error_type::cycle_in_expressions);
	}
	current_expression_generation.erase (expression_a);
	assert (current_expression_generation.find (expression_a) == current_expression_generation.end ());
	assert (result_m.error != nullptr || !result || (result && already_generated_multi.find (expression_a) != already_generated_multi.end ()));
	assert (result_m.error != nullptr || !!result || (!result && already_generated.find (expression_a) != already_generated.end ()));
	return result;
}

bool mu::llvmc::analyzer_function::process_value_call (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
	auto result (false);
	auto target (static_cast<mu::llvmc::skeleton::value *> (arguments [0]));
	auto type_l (target->type ());
	auto pointer_type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (type_l));
	if (pointer_type != nullptr)
	{
		auto function_type (dynamic_cast<mu::llvmc::skeleton::function_type *> (pointer_type->pointed_type));
		if (function_type != nullptr)
		{
			assert (predicate_offset <= arguments.size ());
			auto k (arguments.begin () + 1);
			auto l (arguments.begin () + predicate_offset);
			size_t i (0);
			size_t j (function_type->function->parameters.size ());
			for (; i != j && k != l && result_m.error == nullptr; ++i, ++k)
			{
				auto argument_value (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
				if (argument_value != nullptr)
				{
					if ((*argument_value->type ()) != *function_type->function->parameters [i]->type ())
					{
						result_m.error = new (GC) mu::core::error_string (U"Argument type does not match parameter type", mu::core::error_type::argument_type_does_not_match_parameter_type);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Argument to function is not a value", mu::core::error_type::argument_to_function_is_not_a_value);
				}
			}
			if (result_m.error == nullptr)
			{
				if ((i == j) == (k == l))
				{
					if (!arguments.empty ())
					{
						auto call (new (GC) mu::llvmc::skeleton::function_call (function_type->function, most_specific_branch, arguments, predicate_offset));
						mu::vector <mu::llvmc::skeleton::node *> returned_results;
						auto branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
						auto empty (true);
						function_type->function->for_each_results (
							[&]
							(mu::llvmc::skeleton::node * node_a, size_t index_a)
							{
								returned_results.push_back (new (GC) mu::llvmc::skeleton::call_element_value (branch, call, index_a));
								empty = false;
							},
							mu::llvmc::skeleton::function::empty_node,
							[&]
							(mu::llvmc::skeleton::node * node_a, size_t index_a)
							{
								if (empty)
								{
									returned_results.push_back (new (GC) mu::llvmc::skeleton::call_element_unit (branch, call, index_a));
								}
							},
							[&]
							(mu::llvmc::skeleton::node * node_a, size_t)
							{
								branch = new (GC) mu::llvmc::skeleton::branch (most_specific_branch);
								empty = true;
							}
						);
						assert (!returned_results.empty ());
						if (returned_results.size () == 1)
						{
							already_generated [expression_a] = returned_results [0];
						}
						else
						{
							result = true;
							auto & target (already_generated_multi [expression_a]);
							target.insert (target.end (), returned_results.begin (), returned_results.end ());
						}
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Incorrect number of arguments", mu::core::error_type::incorrect_number_of_arguments);
				}
			}
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Pointer does not point to a function", mu::core::error_type::pointer_does_not_point_to_a_function);
		}
	}
	else
	{
		result_m.error = new (GC) mu::core::error_string (U"Only function pointers can be the target of a call", mu::core::error_type::only_function_pointers_can_be_target_of_call);
	}
	current_expression_generation.erase (expression_a);
	return result;
}

bool mu::llvmc::analyzer_function::process_join (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::value *> arguments;
	for (auto i (expression_a->arguments.begin () + 1), j (expression_a->arguments.end ()); i != j && result_m.error == nullptr; ++i)
	{
		auto multi (process_node (*i));
		if (result_m.error == nullptr)
		{
			if (multi)
			{
				auto & values (already_generated_multi [*i]);
				for (auto k (values.begin ()), l (values.end ()); k != l; ++k)
				{
					auto value (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
					if (value != nullptr)
					{
						arguments.push_back (value);
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Join arguments must be values", mu::core::error_type::join_arguments_must_be_values);
					}
				}
			}
			else
			{
				auto value (dynamic_cast<mu::llvmc::skeleton::value *> (already_generated [*i]));
				if (value != nullptr)
				{
					arguments.push_back (value);
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Join arguments must be values", mu::core::error_type::join_arguments_must_be_values);
				}
			}
		}
	}
	mu::set <mu::llvmc::skeleton::branch *> marked_branches;
	mu::set <mu::llvmc::skeleton::branch *> joined_branches;
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j && result_m.error == nullptr; ++i)
	{
		auto value (*i);
		auto existing_marked (marked_branches.find (value->branch));
		if (existing_marked == marked_branches.end ())
		{
			for (auto k (value->branch); k != nullptr && result_m.error == nullptr; k = k->parent)
			{
				auto existing_joined (joined_branches.find (k));
				if (existing_joined == joined_branches.end ())
				{
					marked_branches.insert (k);
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Branches are not distinct", mu::core::error_type::branches_are_not_disjoint);
				}
			}
			joined_branches.insert (value->branch);
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Branches are not disjoint", mu::core::error_type::branches_are_not_disjoint);
		}
	}
	if (result_m.error == nullptr)
	{
		if (arguments.size () > 1)
		{
			auto least_specific_branch (arguments [0]->branch);
			auto type (arguments [0]->type ());
			for (auto i (arguments.begin () + 1), j (arguments.end ()); i != j; ++i)
			{
				least_specific_branch = least_specific_branch->least_specific ((*i)->branch);
				auto other_type ((*i)->type ());
				if (*type != *other_type)
				{
					result_m.error = new (GC) mu::core::error_string (U"Joining types are different", mu::core::error_type::joining_types_are_different);
				}
			}
			if (result_m.error == nullptr)
			{
				auto parent (least_specific_branch->parent);
				assert (parent != module.module->global);
				already_generated [expression_a] = new (GC) mu::llvmc::skeleton::join_value (parent, arguments);
			}
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Must be joining at least two values", mu::core::error_type::must_be_joining_at_least_two_values);
		}
	}
	return false;
}

void mu::llvmc::analyzer_function::calculate_most_specific (mu::llvmc::skeleton::branch * & first, mu::llvmc::skeleton::branch * test)
{
	assert (first != nullptr);
	assert (test != nullptr);
	auto first_l (first->most_specific (test));
	if (first_l == nullptr)
	{
		result_m.error = new (GC) mu::core::error_string (U"Arguments are disjoint", mu::core::error_type::arguments_are_disjoint);
	}
	else
	{
		first = first_l;
	}
}

void mu::llvmc::analyzer_function::process_call_values (mu::vector <mu::llvmc::ast::node *> const & arguments, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::llvmc::skeleton::branch * & most_specific_branch, size_t & predicate_position_a)
{
	size_t predicate_position_l (~0);
	mu::llvmc::ast::for_each_argument (
			arguments,
			predicate_offset,
			[&]
			(mu::llvmc::ast::node * node_a, size_t index)
			{
				auto result (process_node (node_a));
				if (result_m.error == nullptr)
				{
					if (result)
					{
						auto & nodes (already_generated_multi [node_a]);
						for (auto k (nodes.begin ()), l (nodes.end ()); k != l && result_m.error == nullptr; ++k)
						{
							auto node (*k);
									auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
							if (value != nullptr)
							{
								calculate_most_specific (most_specific_branch, value->branch);
							}
							arguments_a.push_back (node);
						}
					}
					else
					{
						auto node (already_generated [node_a]);
								auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
						if (value != nullptr)
						{
							calculate_most_specific (most_specific_branch, value->branch);
						}
						arguments_a.push_back (node);
					}
				}
			},
	[&]
	(mu::llvmc::ast::node * node_a, size_t index)
	{
		auto result (process_node (node_a));
		if (result_m.error == nullptr)
		{
			if (result)
			{
				auto & nodes (already_generated_multi [node_a]);
				for (auto k (nodes.begin ()), l (nodes.end ()); k != l && result_m.error == nullptr; ++k)
				{
					auto node (*k);
							auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
					if (value != nullptr)
					{
						calculate_most_specific (most_specific_branch, value->branch);
					}
					arguments_a.push_back (node);
				}
			}
			else
			{
				auto node (already_generated [node_a]);
						auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
				if (value != nullptr)
				{
					calculate_most_specific (most_specific_branch, value->branch);
				}
				arguments_a.push_back (node);
			}
		}
	},
	[&]
	(mu::llvmc::ast::node * node_a, size_t index)
	{
		predicate_position_l = arguments_a.size ();
	},
	[&]
	()
	{
		return result_m.error == nullptr;
	}
	);
	if (predicate_position_l == ~0)
	{
		predicate_position_l = arguments_a.size ();
	}
	predicate_position_a = predicate_position_l;
}

bool mu::llvmc::analyzer_function::process_marker (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
	auto marker (static_cast<mu::llvmc::skeleton::marker *> (arguments [0]));
	auto result (false);
	switch (marker->type)
	{
		case mu::llvmc::instruction_type::if_i:
		{
			if (arguments.size () == 2 || (arguments.size () > 2 && expression_a->predicate_position == 2))
			{
				auto predicate (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
				if (predicate != nullptr)
				{
					auto integer_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (predicate->type ()));
					if (integer_type != nullptr)
					{
						if (integer_type->bits == 1)
						{
							result = true;
							auto false_const (new (GC) mu::llvmc::skeleton::constant_integer (module.module->global, 1, 0));
							auto true_const (new (GC) mu::llvmc::skeleton::constant_integer (module.module->global, 1, 1));
							arguments.push_back (false_const);
							arguments.push_back (true_const);
							auto switch_i (new (GC) mu::llvmc::skeleton::switch_i (most_specific_branch, arguments));
							auto true_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
							auto false_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
							auto true_element (new (GC) mu::llvmc::skeleton::switch_element (true_branch, switch_i, true_const));
							auto false_element (new (GC) mu::llvmc::skeleton::switch_element (false_branch, switch_i, false_const));
							auto & values (already_generated_multi [expression_a]);
							values.push_back (true_element);
							values.push_back (false_element);
						}
						else
						{
							result_m.error = new (GC) mu::core::error_string (U"If instruction expects 1 bit integer", mu::core::error_type::if_instruction_expects_one_bit_integer);
						}
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"If instruction expects an integer type value", mu::core::error_type::if_instruction_expects_integer_type_value);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"If instruction expects a value argument", mu::core::error_type::if_instruction_expects_a_value_argument);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"If instruction expects one argument", mu::core::error_type::if_instruction_expects_one_argument);
			}
			break;
		}
		case mu::llvmc::instruction_type::add:
		{
			if (predicate_offset == 3)
			{
				auto left (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
				if (left != nullptr)
				{
					auto right (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [2]));
					if (right != nullptr)
					{
						auto left_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (left->type ()));
						if (left_type != nullptr)
						{
							auto right_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (right->type ()));
							if (right_type != nullptr)
							{
								if (*left_type == *right_type)
								{
									already_generated [expression_a] = new (GC) mu::llvmc::skeleton::instruction (most_specific_branch, arguments, predicate_offset);
								}
								else
								{
									result_m.error = new (GC) mu::core::error_string (U"Add left and right arguments must be same width", mu::core::error_type::add_arguments_must_have_same_bit_width);
								}
							}
							else
							{
								result_m.error = new (GC) mu::core::error_string (U"Add right argument must be an integer type", mu::core::error_type::add_arguments_must_be_integers);
							}
						}
						else
						{
							result_m.error = new (GC) mu::core::error_string (U"Add left argument must be an integer type", mu::core::error_type::add_arguments_must_be_integers);
						}
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Add right argument must be a value", mu::core::error_type::add_arguments_must_be_values);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Add left argument must be a value", mu::core::error_type::add_arguments_must_be_values);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Add instruction expects two arguments", mu::core::error_type::add_expects_two_arguments);
			}
			break;
		}
		case mu::llvmc::instruction_type::store:
		{
			if (predicate_offset == 3)
			{
				auto left (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
				if (left != nullptr)
				{
					auto right (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [2]));
					if (right != nullptr)
					{
						auto right_type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (right->type ()));
						if (right_type != nullptr)
						{
							if (*right_type->pointed_type == *left->type ())
							{
								already_generated [expression_a] = new (GC) mu::llvmc::skeleton::instruction (most_specific_branch, arguments, predicate_offset);
							}
							else
							{
								result_m.error = new (GC) mu::core::error_string (U"Type pointed to by store right argument does not match type of left argument", mu::core::error_type::store_right_pointed_type_doesnt_match_left);
							}
						}
						else
						{
							result_m.error = new (GC) mu::core::error_string (U"Store right argument must be a pointer type", mu::core::error_type::store_right_argument_pointer_type);
						}
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Store right argument must be a value", mu::core::error_type::store_arguments_must_be_values);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Store left argument must be a value", mu::core::error_type::store_arguments_must_be_values);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Store instruction expects two arguments", mu::core::error_type::store_expects_two_arguments);
			}
			break;
		}
		case mu::llvmc::instruction_type::load:
		{
			if (predicate_offset == 2)
			{
				auto source (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
				if (source != nullptr)
				{
					auto type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (source->type ()));
					if (type != nullptr)
					{
						already_generated [expression_a] = new (GC) mu::llvmc::skeleton::instruction (most_specific_branch, arguments, predicate_offset);
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Load argument must be a pointer type", mu::core::error_type::load_argument_pointer_type);
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Load argument must be a value", mu::core::error_type::load_argument_must_be_values);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Load instruction expects two arguments", mu::core::error_type::load_expects_one_argument);
			}
			break;
		}
		default:
			assert (false);
			break;
	}
	assert (result_m.error != nullptr || !result || (result && already_generated_multi.find (expression_a) != already_generated_multi.end ()));
	assert (result_m.error != nullptr || !!result || (!result && already_generated.find (expression_a) != already_generated.end ()));
	return result;
}