function exit_linux
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$60, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function exit_osx
[int32 code]
[
	let nothing [asm unit {%%%}
		mov $$0x2000001, %rax
		mov $$0, %rdi
		syscall %%% {}]
]
[[;nothing]]

function linux
[]
[]
[[int1 cint1 #0]]

function exit
[int32 code]
[
	let linux_l osx [if [linux]]
	let result [join [exit_linux code; linux_l] [exit_osx code; osx]]
]
[[; result]]

function write-linux
[int64 file-descriptor ptr int8 data int64 size]
[
]
[[]]

function write-osx
[int64 file-descriptor ptr int8 data int64 size]
[
	let nothing [asm unit {%%%}
		mov $$0x2000004, %rax
		syscall
		%%% {%%%} {di},{si},{dx},~rax %%% file-descriptor data size]
]
[[;nothing]]

function write
[int64 file-descriptor ptr int8 data int64 size]
[
	let linux_l osx [if [linux]]
	let result [join [write-linux file-descriptor data size; linux_l] [write-osx file-descriptor data size; osx]]
]
[[;result]]

function write-test
[]
[
	let text [alloca array int8 #13]
	let stored [store carray int8 [cint8 #72 cint8 #101 cint8 #108 cint8 #108 cint8 #111 cint8 #32 cint8 #87 cint8 #111 cint8 #114 cint8 #108 cint8 #100 cint8 #33 cint8 #32] text]
	let result [write cint64 #1 [bitcast text ptr int8] cint64 #13; stored]
]
[[;result]]

function entry
[]
[
	let write_l [write-test]
	let result [exit cint32 #0; write_l]
]
[[; result]]
