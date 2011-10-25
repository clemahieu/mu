environment
 `file_stream
 `routine_builder
 `package_create
 `package_add
;
 file_stream
 routine_builder
 package_create
 package_add
;
package_create ; routines;
file_stream `examples/test.lp; file;
routine_builder file; routine;
package_add routines routine `test; ;
package_add environment routines `routines; ;
environment `routines; routines_back;
routines_back `test; test_back;
:;