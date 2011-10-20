environment
 file_stream
 routine_builder
 malloc
 llvm
 list
=
 'file_stream
 'routine_builder
 'malloc
 'llvm
 'list
;
llvm
 type
 generator
=
 'type
 'generator
;
file_stream file = 'examples/malloc_function.lp;
routine_builder routine = file;
type return_type = 'getInt8PtrTy;
type argument_type = 'getInt64Ty;
list arguments = malloc argument_type;
generator function = routine return_type arguments;
#;