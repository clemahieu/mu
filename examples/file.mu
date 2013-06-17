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
		syscall %%% {%%%} {di} %%% code]
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
	let text [alloca array int8 #12]
	let stored [store ascii {%}Hello world!% text]
	let result [write cint64 #1 [bitcast text ptr int8] cint64 #12; stored]
]
[[;result]]

function entry
[]
[
	let write_l [write-test]
	let result [exit cint32 #0; write_l]
]
[[; result]]
