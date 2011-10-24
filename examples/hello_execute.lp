environment
 hello 
 file_stream
 routine_builder
 list
 instances
 apply
 =
 'hello
 'file_stream
 'routine_builder
 'list
 'instances
 'apply
;
file_stream file = 'examples/execute.lp;
routine_builder routine = file;
list argument_list = hello;
instances arguments = argument_list;
apply = routine arguments;
#;
