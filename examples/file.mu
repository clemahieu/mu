let size-t int-t # 64
let iptr int-t # 64

let syscall-0 function
[int-t # 64 id]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax}% id]
]
[[int-t # 64 result]]

let syscall-1 function
[int-t # 64 id int-t # 64 arg1]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di}% id arg1]
]
[[int-t # 64 result]]

let syscall-2 function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si}% id arg1 arg2]
]
[[int-t # 64 result]]

let syscall-3 function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx}% id arg1 arg2 arg3]
]
[[int-t # 64 result]]

let syscall-4-osx function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{cx}% id arg1 arg2 arg3 arg4]
]
[[int-t # 64 result]]

let syscall-5-osx function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4 int-t # 64 arg5]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{cx},{r8}% id arg1 arg2 arg3 arg4 arg5]
]
[[int-t # 64 result]]

let syscall-6-osx function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4 int-t # 64 arg5 int-t # 64 arg6]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{cx},{r8},{r9}% id arg1 arg2 arg3 arg4 arg5 arg6]
]
[[int-t # 64 result]]

let syscall-4-linux function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{r10}% id arg1 arg2 arg3 arg4]
]
[[int-t # 64 result]]

let syscall-5-linux function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4 int-t # 64 arg5]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{r10},{r8}% id arg1 arg2 arg3 arg4 arg5]
]
[[int-t # 64 result]]

let syscall-6-linux function
[int-t # 64 id int-t # 64 arg1 int-t # 64 arg2 int-t # 64 arg3 int-t # 64 arg4 int-t # 64 arg5 int-t # 64 arg6]
[
	let result [asm int-t # 64 syscall {%}={ax},{ax},{di},{si},{dx},{r10},{r8},{r9}% id arg1 arg2 arg3 arg4 arg5 arg6]
]
[[int-t # 64 result]]

let exit-osx-system-code # h2000001
let write-osx-system-code # h2000004
let open-osx-system-code # h2000005
let close-osx-system-code # h2000006
let mmap-osx-system-code # h20000c5

let write-linux-system-code # h1
let open-linux-system-code # h2
let mmap-linux-system-code # h9
let exit-linux-system-code # h3c

let O_RDWR-linux # o2
let O_CREAT-linux # o100

let PROT_READ-linux # h1
let PROT_WRITE-linux # h2
let PROT_EXEC-linux # h4
let PROT_NONE-linux # h0

let MAP_SHARED-linux # h1
let MAP_PRIVATE-linux # h2
let MAP_ANONYMOUS-linux # h20
let no-fd-linux # hffffffffffffffff

let exit_linux function
[int-t # 64 code]
[
	let nothing [syscall-1 exit-linux-system-code code]
]
[[;nothing]]

let exit_osx function
[int-t # 64 code]
[
	let nothing [syscall-1 exit-osx-system-code code]
]
[[;nothing]]

let platform function
[]
[
	let linux osx [if # 0]
]
[[unit linux][unit osx]]

let exit function
[int-t # 64 code]
[
	let linux osx [platform]
	let result join [
		[[exit_linux code; linux]]
		[[exit_osx code; osx]]]
]
[[; result]]

let write-linux function
[int-t # 64 file-descriptor ptr int-t # 8 data int-t # 64 size]
[
	let nothing [syscall-3 write-linux-system-code file-descriptor [ptrtoint data int-t # 64] size]
]
[[;nothing]]

let write-osx function
[int-t # 64 file-descriptor ptr int-t # 8 data int-t # 64 size]
[
	let nothing [syscall-3 write-osx-system-code file-descriptor [ptrtoint data int-t # 64] size]
]
[[;nothing]]

let write function
[int-t # 64 file-descriptor ptr int-t # 8 data int-t # 64 size]
[
	let linux osx [platform]
	let result join [
		[[write-linux file-descriptor data size; linux]]
		[[write-osx file-descriptor data size; osx]]]
]
[[;result]]

let write-test-string global ascii {%}Hello world!
%

let write-string function
[int-t # 64 fd ` astring type str]
[
	let result [write fd [` astring data str] [` astring size str]]
]
[[;result]]

let write-test function
[int-t # 64 fd]
[
	let initial [` astring new-set [bitcast write-test-string ptr int-t # 8] # 13]
	let full [` astring append initial initial]
	let result [write-string fd full]
]
[[;result]]

let open-osx function
[ptr int-t # 8 path int-t # 64 flags int-t # 64 mode]
[
	let fd [syscall-3 open-osx-system-code [ptrtoint path int-t # 64] flags mode]
]
[[int-t # 64 fd]]

let open-linux function
[ptr int-t # 8 path int-t # 64 flags int-t # 64 mode]
[
	let fd [syscall-3 open-linux-system-code [ptrtoint path int-t # 64] flags mode]
]
[[int-t # 64 fd]]

let open function
[ptr int-t # 8 path int-t # 64 flags int-t # 64 mode]
[
	let linux osx [platform]
	let fd join [
		[[open-osx path flags mode; osx]]
		[[open-linux path flags mode; linux]]]
]
[[int-t # 64 fd]]

let close-osx function
[int-t # 64 fd]
[
	let result [syscall-1 close-osx-system-code fd]
]
[[int-t # 64 result]]

let close-linux function
[int-t # 64 fd]
[
	let result [syscall-1 close-osx-system-code fd]
]
[[int-t # 64 result]]

let close function
[int-t # 64 fd]
[
	let linux osx [platform]
	let result join [
		[[close-osx fd; osx]]
		[[close-linux fd; linux]]]
]
[[int-t # 64 result]]

let mmap-osx function
[ptr int-t # 8 addr int-t # 64 len int-t # 64 prot int-t # 64 flags int-t # 64 fd int-t # 64 pos]
[
	let result [ptrfromint [syscall-6-osx mmap-osx-system-code [ptrtoint addr int-t # 64] len prot flags fd pos] ptr int-t # 8]
]
[[ptr int-t # 8 result]]

let mmap-linux function
[ptr int-t # 8 addr int-t # 64 len int-t # 64 prot int-t # 64 flags int-t # 64 fd int-t # 64 pos]
[
	let result [ptrfromint [syscall-6-linux mmap-linux-system-code [ptrtoint addr int-t # 64] len prot flags fd pos] ptr int-t # 8]
]
[[ptr int-t # 8 result]]

let mmap function
[ptr int-t # 8 addr int-t # 64 len int-t # 64 prot int-t # 64 flags int-t # 64 fd int-t # 64 pos]
[
	let linux osx [platform]
	let result join [
		[[mmap-osx addr len prot flags fd pos; osx]]
		[[mmap-linux addr len prot flags fd pos; linux]]]
]
[[ptr int-t # 8 result]]

let generic_mul template [type]
[
	function
	[type left type right]
	[
		let result [mul left right]
	]
	[[type result]]
]

let mul64 [generic_mul int-t # 64]
let mul32 [generic_mul int-t # 32]

let umax function
[int-t # 64 left int-t # 64 right]
[
	let result [select [icmp iugt left right] left right]
]
[[int-t # 64 result]]

let umin function
[int-t # 64 left int-t # 64 right]
[
	let result [select [icmp iult left right] left right]
]
[[int-t # 64 result]]

let lalloc-base global null ptr int-t # 8
let lalloc-available global [int-c int-t # 64 # h0]

let lalloc-slab-size [int-c int-t # 64 # h100000]

let lalloc-slab function
[]
[
	let mem [mmap 
		[ptrfromint [int-c int-t # 64 # 0] ptr int-t # 8] 
		lalloc-slab-size
		[or PROT_READ-linux PROT_WRITE-linux] 
		[or MAP_PRIVATE-linux MAP_ANONYMOUS-linux] 
		no-fd-linux 
		# 0]
]
[[ptr int-t # 8 mem]]

let lalloc function
[int-t # 64 amount]
[
	let current-available [load lalloc-available]
	let enough not-enough [if [icmp iuge current-available amount]]	
	let result available join [
		[[lalloc-slab; not-enough] lalloc-slab-size]
		[[load lalloc-base; enough] current-available]]
	let store1 [store [getelementptr result amount] lalloc-base]
	let store2 [store [sub available amount] lalloc-available]
]
[[ptr int-t # 8 result; store1 store2]]

let lfree function
[ptr int-t # 8 data]
[
]
[[;data]]

let file-name-osx global ascii /Users/clemahieu/test.txt:a00
let linux-file-name global ascii /home/colin/mu_build/test.txt:a00

let sizeof template [sizeof-type]
[
	[sub [ptrtoint [getelementptr let base null ptr sizeof-type [int-c int-t # 32 # 1]] int-t # 64] [ptrtoint [getelementptr base [int-c int-t # 32 # 0]] int-t # 64]]
]

let memcopy function
[ptr int-t # 8 source ptr int-t # 8 destination int-t # 64 size]
[
	let end [ptrtoint [getelementptr source size] int-t # 64]
	let complete loop
	[source destination]
	[source_l destination_l]
	[
		let done not-done [if [icmp ieq [ptrtoint source_l int-t # 64] end]]
		let stored [store [load source_l; not-done] destination_l]
	]
	[[[getelementptr source_l [int-c int-t # 64 # 1]] [getelementptr destination_l [int-c int-t # 64 # 1]]; stored][; done]]
]
[[; complete]]

let mcopy template [element-type]
[
	function [ptr element-type begin ptr element-type end ptr element-type destination]
	[
		let next [int-c int-t # 64 # 1]
		let complete loop
		[begin destination]
		[source-l destination-l]
		[
			let done not-done [if [icmp iuge [ptrtoint source-l iptr] [ptrtoint end iptr]]]
			let stored [store [load source-l; not-done] destination-l]
		]
		[[[getelementptr source-l next] [getelementptr destination-l next]; stored] [; done]]
	]
	[[; complete]]
]

let vector-template template [template-type]
[
	module [
		let type struct [data ptr template-type
			size size-t]
	
		let data-set function
		[ptr type vector ptr template-type data-a]
		[
			let result [store data-a [getelementptr vector [int-c int-t # 32 # 0] ` type data]]
		]
		[[; result]]
		
		let data-get function
		[ptr type vector]
		[
			let result [load [getelementptr vector [int-c int-t # 32 # 0] ` type data]]
		]
		[[ptr template-type result]]
	
		let size-set function
		[ptr type vector size-t size-a]
		[
			let result [store size-a [getelementptr vector [int-c int-t # 32 # 0] ` type size]]
		]
		[[; result]]
		
		let size-get function
		[ptr type vector]
		[
			let result [load [getelementptr vector [int-c int-t # 32 # 0] ` type size]]
		]
		[[size-t result]]
	
		let new-set function
		[ptr template-type data-a int-t # 64 size-a]
		[
			let result [bitcast [lalloc [sizeof type]] ptr type]
			let data [data-set result data-a]
			let size [size-set result size-a]
		]
		[[ptr type result; data size]]
	
		let new function
		[]
		[
			let result [new-set null ptr template-type # 0]
		]
		[[ptr type result]]
	]
]

let string-template template [element-type]
[
	module
	[
		let type struct [data ptr element-type 
			size size-t]
			
		let empty function
		[type string-a]
		[
			let result [icmp ieq [extractvalue string-a ` type size] [int-c size-t # 0]] 
		]
		[[int-t # 1 result]]

		let size function
		[type string-a]
		[
			let result [extractvalue string-a ` type size]
		]
		[[size-t result]]

		let data function
		[type string-a]
		[
			let result [extractvalue string-a ` type data]
		]
		[[ptr element-type result]]

		let append function
		[type string-a type other-a]
		[
			let string-size [size string-a]
			let other-size [size other-a]
			let new-size [add string-size other-size]
			let new-data [lalloc new-size]
			let copied1 [[mcopy element-type] let string-data [data string-a] [getelementptr string-data string-size] [bitcast new-data ptr element-type]]
			let copied2 [[mcopy element-type] let begin [data other-a] [getelementptr begin other-size] [getelementptr [bitcast new-data ptr element-type] string-size]]
			let result [new-set [bitcast new-data ptr element-type] new-size]
			let freed [lfree [bitcast string-data ptr int-t # 8]; copied1]
		]
		[[type result; copied2 freed]]

		let new-set function
		[ptr element-type data-a size-t size-a]
		[
			let result [insertvalue [insertvalue undefined type data-a [int-c int-t # 32 # 0]] size-a [int-c int-t # 32 # 1]]
		]
		[[type result]]

		let new function
		[]
		[
			let result [new-set [bitcast [lalloc [int-c size-t # 0]] ptr element-type] # 0]
		]
		[[type result]]
	]
]

let string [string-template int-t # 32]
let astring [string-template int-t # 8]

let vector<int64> [vector-template int-t # 64]
let vector<int32> [vector-template int-t # 32]

entrypoint let entry function
[]
[
	:(let stored [store ascii  let text [alloca array int-t # 8 #26]]
	let stored [store ascii  let text [alloca array int-t # 8 #30]]
	let fd [open [bitcast file-name-osx ptr int-t # 8] # h602 # o600]
	let fd [open [bitcast file-name-linux ptr int-t # 8] [or O_RDWR-linux O_CREAT-linux] # o600]
	let write_l [write-test fd]
	let close_l [close fd; write_l]:)
	let vector [` vector<int64> new]
	let hello [write-test # 1]
	let alloc1 [lalloc # 100]
	let alloc2 [lalloc # 1000]
	let result [exit # 0; hello alloc1 alloc2]
]
[[; result vector]]
