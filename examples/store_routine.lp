environment
 file_stream
 routine_builder
 package_create
 package_add
=
 'file_stream
 'routine_builder
 'package_create
 'package_add
;
package_create routines =;
file_stream file = 'examples/test.lp;
routine_builder routine = file;
package_add = routines routine 'test;
package_add = environment routines 'routines;
environment routines_back = 'routines;
routines_back test_back = 'test;

#;