environment
 `file_stream
 `routine_builder
 `malloc
 `llvm
 `list
;
 file_stream
 routine_builder
 malloc
 llvm
 list
;
llvm
 type
 generator
=
 'type
 'generator
;
file_stream file `examples/malloc_function.lp; ;
routine_builder file; routine;
type `getInt8PtrTy; return_type;
type `getInt64Ty; argument_type;
list malloc argument_type; arguments;
generator routine return_type arguments; function;
#;