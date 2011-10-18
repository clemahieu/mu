environment
 constant_int
 malloc
 cast_inst
 llvm:type
 context
 store_inst
 load_inst
 memcpy
 wprintf
 call_inst
 list
 =
 ' llvm.constant_int
 ' malloc
 ' llvm.cast_inst
 ' llvm.type
 ' context
 ' llvm.store_inst
 ' llvm.load_inst
 ' memcpy
 ' wprintf
 ' llvm.call_inst
 ' list
;
constant_int number = ' 10 ' 42 ' 64;
constant_int number_size = ' 10 ' 8 ' 64;
list malloc_args = number_size;
call_inst first_value = malloc malloc_args;
llvm:type 64bit_type = ' getInt64PtrTy;
cast_inst first_value_cast = first_value 64bit_type;
store_inst = first_value_cast number;
call_inst second_value = malloc malloc_args;
constant_int alignment = ' 10 ' 0 ' 32;
constant_int volatile = ' 10 ' 0 ' 1; 
list memcpy_args = second_value first_value number_size alignment volatile;
call_inst memcpy_done = memcpy memcpy_args;
cast_inst second_value_cast = second_value 64bit_type;
load_inst second_value_load = second_value_cast;
wprintf = second_value_load;
#;
