environment
 `llvm.constant_int
 `malloc
 `llvm.cast_inst
 `llvm.type
 `context
 `llvm.store_inst
 `llvm.load_inst
 `memcpy
 `wprintf
 `llvm.call_inst
 `list
;
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
;
constant_int `10 `42 `64; number;
constant_int `10 `8 `64; number_size;
list number_size; malloc_args;
call_inst malloc malloc_args; first_value;
llvm:type `getInt64PtrTy; 64bit_type;
cast_inst first_value 64bit_type; first_value_cast;
store_inst first_value_cast number; ;
call_inst malloc malloc_args; second_value;
constant_int `10 `0 `32; alignment;
constant_int `10 `0 `1; volatile; 
list second_value first_value number_size alignment volatile; memcpy_args;
call_inst memcpy memcpy_args; memcpy_done;
cast_inst second_value 64bit_type; second_value_cast;
load_inst second_value_cast; second_value_load;
wprintf second_value_load; ;
:;
