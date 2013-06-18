let syscall-0 function
[int64 id]
[
	let result [asm int64 syscall {%%%}={ax},{ax}%%% id]
]
[[int64 result]]

let syscall-1 function
[int64 id int64 arg1]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di}%%% id arg1]
]
[[int64 result]]

let syscall-2 function
[int64 id int64 arg1 int64 arg2]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di},{si}%%% id arg1 arg2]
]
[[int64 result]]

let syscall-3 function
[int64 id int64 arg1 int64 arg2 int64 arg3]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di},{si},{dx}%%% id arg1 arg2 arg3]
]
[[int64 result]]

let syscall-4 function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di},{si},{dx},{cx}%%% id arg1 arg2 arg3 arg4]
]
[[int64 result]]

let syscall-5 function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di},{si},{dx},{cx},{r8}%%% id arg1 arg2 arg3 arg4 arg5]
]
[[int64 result]]

let syscall-6 function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5 int64 arg6]
[
	let result [asm int64 syscall {%%%}={ax},{ax},{di},{si},{dx},{cx},{r8},{r9}%%% id arg1 arg2 arg3 arg4 arg5 arg6]
]
[[int64 result]]

let exit_linux function
[int64 code]
[
	let nothing [syscall-1 cint64 #d60 code]
]
[[;nothing]]

let exit_osx function
[int64 code]
[
	let nothing [syscall-1 cint64 #h2000001 code]
]
[[;nothing]]

let linux function
[]
[]
[[int1 cint1 #0]]

let exit function
[int64 code]
[
	let linux_l osx [if [linux]]
	let result [join 
		[exit_linux code; linux_l]
		[exit_osx code; osx]
	]
]
[[; result]]

let write-linux function
[int64 file-descriptor ptr int8 data int64 size]
[
]
[[]]

let write-osx function
[int64 file-descriptor ptr int8 data int64 size]
[
	let nothing [syscall-3 cint64 #h2000004 file-descriptor [ptrtoint data int64] size]
]
[[;nothing]]

let write function
[int64 file-descriptor ptr int8 data int64 size]
[
	let linux_l osx [if [linux]]
	let result [join 
		[write-linux file-descriptor data size; linux_l]
		[write-osx file-descriptor data size; osx]
	]
]
[[;result]]

let write-test function
[int64 fd]
[
	let text [alloca array int8 #13]
	let stored [store ascii 
{%}Hello world!
% text]
	let result [write fd [bitcast text ptr int8] cint64 #13; stored]
]
[[;result]]

let open-osx function
[ptr int8 path int64 flags int64 mode]
[
	let fd [syscall-3 cint64 #h2000005 [ptrtoint path int64] flags mode]
]
[[int64 fd]]

let open-linux function
[ptr int8 path int64 flags int64 mode]
[
	let fd [syscall-3 cint64 #h2000005 [ptrtoint path int64] flags mode]
]
[[int64 fd]]

let open function
[ptr int8 path int64 flags int64 mode]
[
	let linux_l osx [if [linux]]
	let fd [join
		[open-osx path flags mode; osx]
		[open-linux path flags mode; linux_l]
	]
]
[[int64 fd]]

let close-osx function
[int64 fd]
[
	let result [syscall-1 cint64 #h2000006 fd]
]
[[int64 result]]

let close-linux function
[int64 fd]
[
	let result [syscall-1 cint64 #h2000006 fd]
]
[[int64 result]]

let close function
[int64 fd]
[
	let linux_l osx [if [linux]]
	let result [join
		[close-osx fd; osx]
		[close-linux fd; linux_l]
	]
]
[[int64 result]]

let mmap-osx function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let result [ptrfromint [syscall-6 cint64 #h20000c5 [ptrtoint addr int64] len prot flags fd pos] ptr int8]
]
[[ptr int8 result]]

let mmap-linux function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let result [ptrfromint [syscall-6 cint64 #h20000c5 [ptrtoint addr int64] len prot flags fd pos] ptr int8]
]
[[ptr int8 result]]

let mmap function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let linux_l osx [if [linux]]
	let result [join
		[mmap-osx addr len prot flags fd pos; osx]
		[mmap-linux addr len prot flags fd pos; linux_l]
	]
]
[[ptr int8 result]]

let entry function
[]
[
	let text [alloca array int8 #26]
	let stored [store ascii /Users/clemahieu/test.txt:a00 text]
	let fd [open [bitcast text ptr int8] cint64 #h602 cint64 #0; stored]
	let write_l [write-test fd]
	let close_l [close fd; write_l]
	let mem [mmap [ptrfromint cint64 #0 ptr int8] cint64 #h100000 cint64 #3 cint64 #h1002 cint64 #0 cint64 #0]
	let result [exit cint64 #0; mem close_l]
]
[[; result]]
