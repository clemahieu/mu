let syscall-0 function
[int64 id]
[
	let result [asm int64 syscall {%}={ax},{ax}% id]
]
[[int64 result]]

let syscall-1 function
[int64 id int64 arg1]
[
	let result [asm int64 syscall {%}={ax},{ax},{di}% id arg1]
]
[[int64 result]]

let syscall-2 function
[int64 id int64 arg1 int64 arg2]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si}% id arg1 arg2]
]
[[int64 result]]

let syscall-3 function
[int64 id int64 arg1 int64 arg2 int64 arg3]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx}% id arg1 arg2 arg3]
]
[[int64 result]]

let syscall-4-osx function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{cx}% id arg1 arg2 arg3 arg4]
]
[[int64 result]]

let syscall-5-osx function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{cx},{r8}% id arg1 arg2 arg3 arg4 arg5]
]
[[int64 result]]

let syscall-6-osx function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5 int64 arg6]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{cx},{r8},{r9}% id arg1 arg2 arg3 arg4 arg5 arg6]
]
[[int64 result]]

let syscall-4-linux function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{r10}% id arg1 arg2 arg3 arg4]
]
[[int64 result]]

let syscall-5-linux function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{r10},{r8}% id arg1 arg2 arg3 arg4 arg5]
]
[[int64 result]]

let syscall-6-linux function
[int64 id int64 arg1 int64 arg2 int64 arg3 int64 arg4 int64 arg5 int64 arg6]
[
	let result [asm int64 syscall {%}={ax},{ax},{di},{si},{dx},{r10},{r8},{r9}% id arg1 arg2 arg3 arg4 arg5 arg6]
]
[[int64 result]]

let exit-osx-system-code cint64 #h2000001
let write-osx-system-code cint64 #h2000004
let open-osx-system-code cint64 #h2000005
let close-osx-system-code cint64 #h2000006
let mmap-osx-system-code cint64 #h20000c5

let write-linux-system-code cint64 #h1
let open-linux-system-code cint64 #h2
let mmap-linux-system-code cint64 #h9
let exit-linux-system-code cint64 #h3c

let O_RDWR-linux cint64 #o2
let O_CREAT-linux cint64 #o100

let PROT_READ-linux cint64 #h1
let PROT_WRITE-linux cint64 #h2
let PROT_EXEC-linux cint64 #h4
let PROT_NONE-linux cint64 #h0

let MAP_SHARED-linux cint64 #h1
let MAP_PRIVATE-linux cint64 #h2
let MAP_ANONYMOUS-linux cint64 #h20
let no-fd-linux cint64 #hffffffffffffffff

let exit_linux function
[int64 code]
[
	let nothing [syscall-1 exit-linux-system-code code]
]
[[;nothing]]

let exit_osx function
[int64 code]
[
	let nothing [syscall-1 exit-osx-system-code code]
]
[[;nothing]]

let platform function
[]
[
	let linux osx [if cint1 #1]
]
[[unit linux][unit osx]]

let exit function
[int64 code]
[
	let linux osx [platform]
	let result [join 
		[exit_linux code; linux]
		[exit_osx code; osx]
	]
]
[[; result]]

let write-linux function
[int64 file-descriptor ptr int8 data int64 size]
[
	let nothing [syscall-3 write-linux-system-code file-descriptor [ptrtoint data int64] size]
]
[[;nothing]]

let write-osx function
[int64 file-descriptor ptr int8 data int64 size]
[
	let nothing [syscall-3 write-osx-system-code file-descriptor [ptrtoint data int64] size]
]
[[;nothing]]

let write function
[int64 file-descriptor ptr int8 data int64 size]
[
	let linux osx [platform]
	let result [join 
		[write-linux file-descriptor data size; linux]
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
	let fd [syscall-3 open-osx-system-code [ptrtoint path int64] flags mode]
]
[[int64 fd]]

let open-linux function
[ptr int8 path int64 flags int64 mode]
[
	let fd [syscall-3 open-linux-system-code [ptrtoint path int64] flags mode]
]
[[int64 fd]]

let open function
[ptr int8 path int64 flags int64 mode]
[
	let linux osx [platform]
	let fd [join
		[open-osx path flags mode; osx]
		[open-linux path flags mode; linux]
	]
]
[[int64 fd]]

let close-osx function
[int64 fd]
[
	let result [syscall-1 close-osx-system-code fd]
]
[[int64 result]]

let close-linux function
[int64 fd]
[
	let result [syscall-1 close-osx-system-code fd]
]
[[int64 result]]

let close function
[int64 fd]
[
	let linux osx [platform]
	let result [join
		[close-osx fd; osx]
		[close-linux fd; linux]
	]
]
[[int64 result]]

let mmap-osx function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let result [ptrfromint [syscall-6-osx mmap-osx-system-code [ptrtoint addr int64] len prot flags fd pos] ptr int8]
]
[[ptr int8 result]]

let mmap-linux function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let result [ptrfromint [syscall-6-linux mmap-linux-system-code [ptrtoint addr int64] len prot flags fd pos] ptr int8]
]
[[ptr int8 result]]

let mmap function
[ptr int8 addr int64 len int64 prot int64 flags int64 fd int64 pos]
[
	let linux osx [platform]
	let result [join
		[mmap-osx addr len prot flags fd pos; osx]
		[mmap-linux addr len prot flags fd pos; linux]
	]
]
[[ptr int8 result]]

let entry function
[]
[
	:(let stored [store ascii /Users/clemahieu/test.txt:a00 let text [alloca array int8 #26]]:)
	let stored [store ascii /home/colin/mu_build/test.txt:a00 let text [alloca array int8 #30]]
	:(let fd [open [bitcast text ptr int8] cint64 #h602 cint64 #o600; stored]:)
	let fd [open [bitcast text ptr int8] [or O_RDWR-linux O_CREAT-linux] cint64 #o600; stored]
	let write_l [write-test fd]
	let close_l [close fd; write_l]
	let mem [mmap [ptrfromint cint64 #0 ptr int8] cint64 #h100000 [or PROT_READ-linux PROT_WRITE-linux] [or MAP_PRIVATE-linux MAP_ANONYMOUS-linux] no-fd-linux cint64 #0]
	let result [exit cint64 #0; mem close_l]
]
[[; result]]
