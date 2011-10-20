#* Swap 32-bit
	Dependency graph:
	|byte0     ||byte1     ||byte2     ||byte3     |
	|result_list                                   |
	|result                                        |#*
value extract collect list = result;
extract byte0 = value 'd0 'd7;
extract byte1 = value 'd8 'd15;
extract byte2 = value 'd16 'd23;
extract byte3 = value 'd24 'd31;
list result_list = byte3 byte2 byte1 byte0;
collect result = result_list;
#;


#* extract 32-bit using shift and mask
	Dependency graph:
	|shifted_value|
	|result       |#*
value and mask count shift_right = result;
shift_right shifted_value = value count;
and result = shifted_value mask;
#;


#* Shrink full mask#*
full_mask shift_right count = result;
shift_right result = full_mask count;
#;


#* Create a mask of 'count' bits#*
one sign_extend count = result;
sign_extend result = one count;
#;
