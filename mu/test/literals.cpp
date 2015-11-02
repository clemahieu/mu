extern char const * const generate_empty_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  unreachable, !dbg !7
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_empty", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_parameter_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !8, metadata !9), !dbg !10
  unreachable, !dbg !10
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_parameter", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7}
!7 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!8 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !7)
!9 = !DIExpression()
!10 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_parameter_return_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
  ret i1 %0, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_parameter_return", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i1 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_add_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = add i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !13, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !13, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_add", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i8, i8)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_alloca_expected = R"%%%(; ModuleID = '0000000000000000'

define i8* @"0000000000000000-0000000000000000-0"() {
  br i1 true, label %1, label %3

; <label>:1                                       ; preds = %0
  %2 = alloca i8, !dbg !10
  br label %3

; <label>:3                                       ; preds = %1, %0
  %4 = phi i8* [ %2, %1 ], [ undef, %0 ]
  %5 = alloca i8*
  store i8* %4, i8** %5
  call void @llvm.dbg.declare(metadata i8** %5, metadata !11, metadata !12), !dbg !10
  call void @llvm.dbg.value(metadata i8* %4, i64 0, metadata !11, metadata !12), !dbg !10
  ret i8* %4, !dbg !10
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_alloca", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8* ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !9, size: 8)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !DILocation(line: 0, scope: !4)
!11 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
!12 = !DIExpression()
)%%%";

extern char const * const generate_and_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = and i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !13, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !13, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_and", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i8, i8)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_ashr_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = ashr i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !13, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !13, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_ashr", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i8, i8)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_bitcast_expected = R"%%%(; ModuleID = '0000000000000000'

define i8* @"0000000000000000-0000000000000000-0"(i32*) {
  %2 = alloca i32*
  store i32* %0, i32** %2
  call void @llvm.dbg.declare(metadata !{i32** %2}, metadata !13), !dbg !14
  %3 = bitcast i32* %0 to i8*, !dbg !14
  %4 = alloca i8*
  store i8* %3, i8** %4
  call void @llvm.dbg.declare(metadata !{i8** %4}, metadata !15), !dbg !14
  call void @llvm.dbg.value(metadata !{i8* %3}, i64 0, metadata !15), !dbg !14
  ret i8* %3, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_bitcast", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_bitcast] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8* (i32*)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_bitcast", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !11}
!9 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int8]
!10 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int32]
!12 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !11, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_cmpxchg_expected = R"%%%(
define i8 @0(i8*, i8, i8) {
  call void @llvm.dbg.declare(metadata !{i8* %0}, metadata !11)
  call void @llvm.dbg.declare(metadata !{i8 %1}, metadata !12)
  call void @llvm.dbg.declare(metadata !{i8 %2}, metadata !13)
  %4 = and i1 true, true
  %5 = and i1 %4, true
  %6 = and i1 %5, true
  br i1 %6, label %7, label %9

; <label>:7                                       ; preds = %3
  %8 = cmpxchg i8* %0, i8 %1, i8 %2 acq_rel, !dbg !14
  br label %9

; <label>:9                                       ; preds = %7, %3
  %10 = phi i8 [ %8, %7 ], [ undef, %3 ]
  call void @llvm.dbg.declare(metadata !{i8 %10}, metadata !15)
  ret i8 %10, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_cmpxchg", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_cmpxchg] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8*, i8, i8)* @0, null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_cmpxchg", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int8]
!11 = metadata !{i32 786689, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter1] [line 0]
!12 = metadata !{i32 786689, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786689, metadata !5, metadata !"parameter3", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [parameter3] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_extractvalue_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"({ i1 }) {
  %2 = alloca { i1 }
  store { i1 } %0, { i1 }* %2
  call void @llvm.dbg.declare(metadata !{{ i1 }* %2}, metadata !13), !dbg !14
  %3 = and i1 true, true
  %4 = extractvalue { i1 } %0, 0, !dbg !14
  %5 = alloca i1
  store i1 %4, i1* %5
  call void @llvm.dbg.declare(metadata !{i1* %5}, metadata !15), !dbg !14
  call void @llvm.dbg.value(metadata !{i1 %4}, i64 0, metadata !15), !dbg !14
  ret i1 %4, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_extractvalue", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_extractvalue] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 ({ i1 })* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_extractvalue", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i32 0, i32 0, null, metadata !11, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 1, align 0, offset 0] [from ]
!11 = metadata !{metadata !12}
!12 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_getelementptr_expected = R"%%%(; ModuleID = '0000000000000000'

define i8* @"0000000000000000-0000000000000000-0"(i8*) {
  %2 = alloca i8*
  store i8* %0, i8** %2
  call void @llvm.dbg.declare(metadata !{i8** %2}, metadata !11), !dbg !12
  %3 = and i1 true, true
  %4 = getelementptr inbounds i8* %0, i8 0, !dbg !12
  %5 = alloca i8*
  store i8* %4, i8** %5
  call void @llvm.dbg.declare(metadata !{i8** %5}, metadata !13), !dbg !12
  call void @llvm.dbg.value(metadata !{i8* %4}, i64 0, metadata !13), !dbg !12
  ret i8* %4, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_getelementptr", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_getelementptr] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8* (i8*)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_getelementptr", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int8]
!10 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_global_variable_expected = R"%%%(; ModuleID = '0000000000000000'

@"0000000000000000-0000000000000000-0" = global i32 42

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_global_variable", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !1, metadata !3} ; [ DW_TAG_compile_unit ] [/generate_global_variable] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786484, i32 0, null, metadata !"0", metadata !"0", metadata !"0", metadata !6, i32 0, metadata !7, i32 0, i32 1, i32* @"0000000000000000-0000000000000000-0"} ; [ DW_TAG_variable ] [0] [line 0] [def]
!6 = metadata !{i32 786473, metadata !"generate_global_variable", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !8} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int32]
!8 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
)%%%";

extern char const * const generate_icmp1_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1, i1) {
  %3 = alloca i1
  store i1 %0, i1* %3
  call void @llvm.dbg.declare(metadata i1* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i1
  store i1 %1, i1* %4
  call void @llvm.dbg.declare(metadata i1* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = icmp eq i1 %0, %1, !dbg !13
  %7 = alloca i1
  store i1 %6, i1* %7
  call void @llvm.dbg.declare(metadata i1* %7, metadata !15, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %6, i64 0, metadata !15, metadata !10), !dbg !11
  ret i1 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_icmp1", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i1 (i1, i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_identity_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8) {
  %2 = alloca i8
  store i8 %0, i8* %2
  call void @llvm.dbg.declare(metadata !{i8* %2}, metadata !10), !dbg !11
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !12), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %0}, i64 0, metadata !12), !dbg !11
  ret i8 %0, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_identity", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_identity] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_identity", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"element1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [element1] [line 0]
)%%%";

extern char const * const generate_lshr_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = lshr i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_lshr", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_lshr] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_lshr", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_insertvalue_expected = R"%%%(; ModuleID = '0000000000000000'

define { i1 } @"0000000000000000-0000000000000000-0"(i1, { i1 }) {
  %3 = alloca i1
  store i1 %0, i1* %3
  call void @llvm.dbg.declare(metadata !{i1* %3}, metadata !13), !dbg !14
  %4 = alloca { i1 }
  store { i1 } %1, { i1 }* %4
  call void @llvm.dbg.declare(metadata !{{ i1 }* %4}, metadata !15), !dbg !14
  %5 = and i1 true, true
  %6 = insertvalue { i1 } %1, i1 %0, 0, !dbg !14
  %7 = alloca { i1 }
  store { i1 } %6, { i1 }* %7
  call void @llvm.dbg.declare(metadata !{{ i1 }* %7}, metadata !16), !dbg !14
  call void @llvm.dbg.value(metadata !{{ i1 } %6}, i64 0, metadata !16), !dbg !14
  ret { i1 } %6, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_insertvalue", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_insertvalue] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, { i1 } (i1, { i1 })* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_insertvalue", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !12, metadata !9}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 1, align 0, offset 0] [from ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
!15 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!16 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_load_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1*) {
  %2 = alloca i1*
  store i1* %0, i1** %2
  call void @llvm.dbg.declare(metadata i1** %2, metadata !10, metadata !11), !dbg !12
  br i1 true, label %3, label %5

; <label>:3                                       ; preds = %1
  %4 = load i1, i1* %0, !dbg !13
  br label %5

; <label>:5                                       ; preds = %3, %1
  %6 = phi i1 [ %4, %3 ], [ undef, %1 ]
  %7 = alloca i1
  store i1 %6, i1* %7
  call void @llvm.dbg.declare(metadata i1* %7, metadata !15, metadata !11), !dbg !12
  call void @llvm.dbg.value(metadata i1 %6, i64 0, metadata !15, metadata !11), !dbg !12
  ret i1 %6, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_load", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i1 (i1*)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !8, size: 8)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_mul_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = mul i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_mul", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_mul] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_mul", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_or_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = or i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_or", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_or] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_or", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_ptrfromint_expected = R"%%%(; ModuleID = '0000000000000000'

define i32* @"0000000000000000-0000000000000000-0"(i64) {
  %2 = alloca i64
  store i64 %0, i64* %2
  call void @llvm.dbg.declare(metadata !{i64* %2}, metadata !12), !dbg !13
  %3 = inttoptr i64 %0 to i32*, !dbg !13
  %4 = alloca i32*
  store i32* %3, i32** %4
  call void @llvm.dbg.declare(metadata !{i32** %4}, metadata !14), !dbg !13
  call void @llvm.dbg.value(metadata !{i32* %3}, i64 0, metadata !14), !dbg !13
  ret i32* %3, !dbg !13
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_ptrfromint", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_ptrfromint] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32* (i64)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_ptrfromint", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !11}
!9 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !10} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int32]
!10 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786468, null, metadata !"int64", null, i32 0, i64 64, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int64] [line 0, size 64, align 0, offset 0, enc DW_ATE_unsigned]
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !11, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !5, null}
!14 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_ptrtoint_expected = R"%%%(; ModuleID = '0000000000000000'

define i64 @"0000000000000000-0000000000000000-0"(i32*) {
  %2 = alloca i32*
  store i32* %0, i32** %2
  call void @llvm.dbg.declare(metadata !{i32** %2}, metadata !12), !dbg !13
  %3 = ptrtoint i32* %0 to i64, !dbg !13
  %4 = alloca i64
  store i64 %3, i64* %4
  call void @llvm.dbg.declare(metadata !{i64* %4}, metadata !14), !dbg !13
  call void @llvm.dbg.value(metadata !{i64 %3}, i64 0, metadata !14), !dbg !13
  ret i64 %3, !dbg !13
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_ptrtoint", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_ptrtoint] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i64 (i32*)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_ptrtoint", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int64", null, i32 0, i64 64, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int64] [line 0, size 64, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !11} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int32]
!11 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !5, null}
!14 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_sdiv_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = sdiv i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_sdiv", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_sdiv] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_sdiv", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_select_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = and i1 %3, true
  %5 = select i1 %0, i1 %0, i1 %0, !dbg !11
  %6 = alloca i1
  store i1 %5, i1* %6
  call void @llvm.dbg.declare(metadata !{i1* %6}, metadata !12), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %5}, i64 0, metadata !12), !dbg !11
  ret i1 %5, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_select_expected", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_select_expected] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_select_expected", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_sext_expected = R"%%%(; ModuleID = '0000000000000000'

define i16 @"0000000000000000-0000000000000000-0"(i8) {
  %2 = alloca i8
  store i8 %0, i8* %2
  call void @llvm.dbg.declare(metadata !{i8* %2}, metadata !11), !dbg !12
  %3 = sext i8 %0 to i16, !dbg !12
  %4 = alloca i16
  store i16 %3, i16* %4
  call void @llvm.dbg.declare(metadata !{i16* %4}, metadata !13), !dbg !12
  call void @llvm.dbg.value(metadata !{i16 %3}, i64 0, metadata !13), !dbg !12
  ret i16 %3, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_sext", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_sext] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i16 (i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_sext", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int16", null, i32 0, i64 16, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int16] [line 0, size 16, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_shl_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = shl i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_shl", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_shl] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_shl", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_srem_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = srem i8 %0, %1, !dbg !11
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !13), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_srem", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_srem] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_srem", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_store_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1, i1*) {
  %3 = alloca i1
  store i1 %0, i1* %3
  call void @llvm.dbg.declare(metadata !{i1* %3}, metadata !11), !dbg !12
  %4 = alloca i1*
  store i1* %1, i1** %4
  call void @llvm.dbg.declare(metadata !{i1** %4}, metadata !13), !dbg !12
  %5 = and i1 true, true
  br i1 %5, label %6, label %7

; <label>:6                                       ; preds = %2
  store i1 %0, i1* %1, !dbg !14
  br label %7

; <label>:7                                       ; preds = %6, %2
  ret void, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_store", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_store] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1, i1*)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_store", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786447, null, metadata !"ptr", null, i32 0, i64 8, i64 0, i64 0, i32 0, metadata !9} ; [ DW_TAG_pointer_type ] [ptr] [line 0, size 8, align 0, offset 0] [from int1]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 17} ; [ DW_TAG_lexical_block ] [/generate_store]
)%%%";

extern char const * const generate_struct_type_undefined_expected = R"%%%(; ModuleID = '0000000000000000'

define { i1 } @"0000000000000000-0000000000000000-0"({ i1 }) {
  %2 = alloca { i1 }
  store { i1 } %0, { i1 }* %2
  call void @llvm.dbg.declare(metadata !{{ i1 }* %2}, metadata !13), !dbg !14
  ret { i1 } undef, !dbg !14
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_struct_type_undefined", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_struct_type_undefined] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, { i1 } ({ i1 })* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_struct_type_undefined", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 1, align 0, offset 0] [from ]
!10 = metadata !{metadata !11}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_sub_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = sub i1 %0, %0, !dbg !12
  %5 = alloca i1
  store i1 %4, i1* %5
  call void @llvm.dbg.declare(metadata !{i1* %5}, metadata !14), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %4}, i64 0, metadata !14), !dbg !11
  ret i1 %4, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_sub", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_sub] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_sub", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 18} ; [ DW_TAG_lexical_block ] [/generate_sub]
!14 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_udiv_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = udiv i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !15), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !15), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_udiv", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_udiv] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_udiv", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !14, null}
!14 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 19} ; [ DW_TAG_lexical_block ] [/generate_udiv]
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_urem_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = urem i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !15), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !15), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_urem", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_urem] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_urem", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !14, null}
!14 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 20} ; [ DW_TAG_lexical_block ] [/generate_urem]
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_xor_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata !{i8* %3}, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata !{i8* %4}, metadata !12), !dbg !11
  %5 = and i1 true, true
  %6 = xor i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata !{i8* %7}, metadata !15), !dbg !11
  call void @llvm.dbg.value(metadata !{i8 %6}, i64 0, metadata !15), !dbg !11
  ret i8 %6, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_xor", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_xor] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i8, i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_xor", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !14, null}
!14 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 21} ; [ DW_TAG_lexical_block ] [/generate_xor]
!15 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_zext_expected = R"%%%(; ModuleID = '0000000000000000'

define i16 @"0000000000000000-0000000000000000-0"(i8) {
  %2 = alloca i8
  store i8 %0, i8* %2
  call void @llvm.dbg.declare(metadata !{i8* %2}, metadata !11), !dbg !12
  %3 = zext i8 %0 to i16, !dbg !12
  %4 = alloca i16
  store i16 %3, i16* %4
  call void @llvm.dbg.declare(metadata !{i16* %4}, metadata !13), !dbg !12
  call void @llvm.dbg.value(metadata !{i16 %3}, i64 0, metadata !13), !dbg !12
  ret i16 %3, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_zext", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_zext] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i16 (i8)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_zext", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int16", null, i32 0, i64 16, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int16] [line 0, size 16, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !5, metadata !"instruction1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [instruction1] [line 0]
)%%%";

extern char const * const generate_two_return_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i1, i1 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !14), !dbg !15
  %3 = insertvalue %0 undef, i1 %0, 0
  %4 = insertvalue %0 %3, i1 %0, 1
  ret %0 %4, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_two_return", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_two_return] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_two_return", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !12}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 2, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 2, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 1, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 1] [from int1]
!14 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!15 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_value_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i32, i32, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !16), !dbg !17
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 4, 0
  %14 = insertvalue %0 %13, i32 5, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15, !dbg !17
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !15}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 64, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 64, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 0] [from int32]
!12 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 32, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 32] [from int32]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!16 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!17 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_join_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = and i1 true, %6
  %9 = or i1 false, %7
  %10 = or i1 %9, %8
  ret void, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_if_join_value_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 true, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 true, %6
  %8 = and i1 %3, %7
  %9 = add i1 %0, %0, !dbg !11
  %10 = alloca i1
  store i1 %9, i1* %10
  call void @llvm.dbg.declare(metadata !{i1* %10}, metadata !12), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %9}, i64 0, metadata !12), !dbg !11
  %11 = and i1 true, %8
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !11
  %15 = alloca i1
  store i1 %14, i1* %15
  call void @llvm.dbg.declare(metadata !{i1* %15}, metadata !13), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %14}, i64 0, metadata !13), !dbg !11
  %16 = and i1 true, %13
  %17 = or i1 false, %11
  %18 = select i1 %11, i1 %9, i1 undef
  %19 = or i1 %17, %16
  %20 = select i1 %16, i1 %14, i1 %18
  %21 = alloca i1
  store i1 %20, i1* %21
  call void @llvm.dbg.declare(metadata !{i1* %21}, metadata !14), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %20}, i64 0, metadata !14), !dbg !11
  ret i1 %20, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"add1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add1] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"add2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add2] [line 0]
!14 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
)%%%";

extern char const * const generate_if_join_value_predicate_expected = R"%%%(; ModuleID = '0000000000000000'

define i32 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !11), !dbg !12
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 true, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 true, %6
  %8 = and i1 %3, %5
  %9 = and i1 true, true
  %10 = and i1 %9, %7
  %11 = or i1 false, %8
  %12 = select i1 %8, i32 42, i32 undef
  %13 = or i1 %11, %10
  %14 = select i1 %10, i32 13, i32 %12
  %15 = alloca i32
  store i32 %14, i32* %15
  call void @llvm.dbg.declare(metadata !{i32* %15}, metadata !13), !dbg !12
  call void @llvm.dbg.value(metadata !{i32 %14}, i64 0, metadata !13), !dbg !12
  ret i32 %14, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_value_predicate", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_value_predicate] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_value_predicate", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !10}
!9 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !10, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
)%%%";

extern char const * const generate_if_join_2value_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i1, i1, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !15), !dbg !16
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 true, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 true, %6
  %8 = and i1 %3, %5
  %9 = add i1 %0, %0, !dbg !16
  %10 = alloca i1
  store i1 %9, i1* %10
  call void @llvm.dbg.declare(metadata !{i1* %10}, metadata !17), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %9}, i64 0, metadata !17), !dbg !16
  %11 = and i1 true, %8
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !16
  %15 = alloca i1
  store i1 %14, i1* %15
  call void @llvm.dbg.declare(metadata !{i1* %15}, metadata !18), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %14}, i64 0, metadata !18), !dbg !16
  %16 = and i1 true, %13
  %17 = or i1 false, %11
  %18 = select i1 %11, i1 %9, i1 undef
  %19 = or i1 %17, %16
  %20 = select i1 %16, i1 %14, i1 %18
  %21 = alloca i1
  store i1 %20, i1* %21
  call void @llvm.dbg.declare(metadata !{i1* %21}, metadata !19), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %20}, i64 0, metadata !19), !dbg !16
  %22 = and i1 true, %19
  %23 = select i1 %22, i8 0, i8 undef
  %24 = and i1 true, true
  %25 = and i1 %24, %5
  %26 = add i1 %0, %0, !dbg !16
  %27 = alloca i1
  store i1 %26, i1* %27
  call void @llvm.dbg.declare(metadata !{i1* %27}, metadata !20), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %26}, i64 0, metadata !20), !dbg !16
  %28 = and i1 true, %25
  %29 = and i1 true, true
  %30 = and i1 %29, %7
  %31 = add i1 %0, %0, !dbg !16
  %32 = alloca i1
  store i1 %31, i1* %32
  call void @llvm.dbg.declare(metadata !{i1* %32}, metadata !21), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %31}, i64 0, metadata !21), !dbg !16
  %33 = and i1 true, %30
  %34 = or i1 false, %28
  %35 = select i1 %28, i1 %26, i1 undef
  %36 = or i1 %34, %33
  %37 = select i1 %33, i1 %31, i1 %35
  %38 = alloca i1
  store i1 %37, i1* %38
  call void @llvm.dbg.declare(metadata !{i1* %38}, metadata !22), !dbg !16
  call void @llvm.dbg.value(metadata !{i1 %37}, i64 0, metadata !22), !dbg !16
  %39 = and i1 true, %36
  %40 = select i1 %39, i8 1, i8 %23
  %41 = insertvalue %0 undef, i1 %20, 0
  %42 = insertvalue %0 %41, i1 %37, 1
  %43 = insertvalue %0 %42, i8 %40, 2
  ret %0 %43, !dbg !16
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_2value", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_2value] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_2value", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !12}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 2, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 2, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 0] [from int1]
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 1, i64 0, i64 1, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 1, align 0, offset 1] [from int1]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!16 = metadata !{i32 0, i32 0, metadata !5, null}
!17 = metadata !{i32 786688, metadata !5, metadata !"add1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add1] [line 0]
!18 = metadata !{i32 786688, metadata !5, metadata !"add2", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add2] [line 0]
!19 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
!20 = metadata !{i32 786688, metadata !5, metadata !"add3", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add3] [line 0]
!21 = metadata !{i32 786688, metadata !5, metadata !"add4", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [add4] [line 0]
!22 = metadata !{i32 786688, metadata !5, metadata !"join2", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join2] [line 0]
)%%%";

extern char const * const generate_if_join_load_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  br i1 %7, label %8, label %10

; <label>:8                                       ; preds = %1
  %9 = load i1* null, !dbg !12
  br label %10

; <label>:10                                      ; preds = %8, %1
  %11 = phi i1 [ %9, %8 ], [ undef, %1 ]
  %12 = alloca i1
  store i1 %11, i1* %12
  call void @llvm.dbg.declare(metadata !{i1* %12}, metadata !14), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %11}, i64 0, metadata !14), !dbg !11
  %13 = and i1 true, %7
  %14 = and i1 true, %6
  br i1 %14, label %15, label %17

; <label>:15                                      ; preds = %10
  %16 = load i1* null, !dbg !12
  br label %17

; <label>:17                                      ; preds = %15, %10
  %18 = phi i1 [ %16, %15 ], [ undef, %10 ]
  %19 = alloca i1
  store i1 %18, i1* %19
  call void @llvm.dbg.declare(metadata !{i1* %19}, metadata !15), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %18}, i64 0, metadata !15), !dbg !11
  %20 = and i1 true, %14
  %21 = or i1 false, %13
  %22 = select i1 %13, i1 %11, i1 undef
  %23 = or i1 %21, %20
  %24 = select i1 %20, i1 %18, i1 %22
  %25 = alloca i1
  store i1 %24, i1* %25
  call void @llvm.dbg.declare(metadata !{i1* %25}, metadata !16), !dbg !11
  call void @llvm.dbg.value(metadata !{i1 %24}, i64 0, metadata !16), !dbg !11
  ret i1 %24, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

declare void @llvm.dbg.value(metadata, i64, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_if_join_load", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_if_join_load] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_if_join_load", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 0, i32 0, metadata !13, null}
!13 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 29} ; [ DW_TAG_lexical_block ] [/generate_if_join_load]
!14 = metadata !{i32 786688, metadata !5, metadata !"load1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [load1] [line 0]
!15 = metadata !{i32 786688, metadata !5, metadata !"load2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [load2] [line 0]
!16 = metadata !{i32 786688, metadata !5, metadata !"join1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [join1] [line 0]
)%%%";

extern char const * const generate_call_0_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !10
}

define void @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !11
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !13
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_0", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_0] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_0", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 0, i32 0, metadata !5, null}
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 31} ; [ DW_TAG_lexical_block ] [/generate_call_0]
!13 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_call_1_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !11), !dbg !12
  ret i1 %0, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i1 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !13), !dbg !14
  %3 = and i1 true, true
  br i1 %3, label %4, label %6

; <label>:4                                       ; preds = %1
  %5 = call i1 @"0000000000000000-0000000000000000-0"(i1 %0), !dbg !15
  br label %6

; <label>:6                                       ; preds = %1, %4
  %7 = phi i1 [ %5, %4 ], [ undef, %1 ]
  ret i1 %7, !dbg !14
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !10}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 (i1)* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !10, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !10, null}
!15 = metadata !{i32 0, i32 0, metadata !16, null}
!16 = metadata !{i32 786443, metadata !10, i32 0, i32 0, metadata !6, i32 33} ; [ DW_TAG_lexical_block ] [/generate_call_1]
)%%%";

extern char const * const generate_call_2_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !11), !dbg !12
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = select i1 %7, i8 0, i8 undef
  %9 = and i1 true, %6
  %10 = select i1 %9, i8 1, i8 %8
  ret i8 %10, !dbg !12
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define i8 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !13), !dbg !14
  %3 = and i1 true, true
  br i1 %3, label %4, label %6

; <label>:4                                       ; preds = %1
  %5 = call i8 @"0000000000000000-0000000000000000-0"(i1 %0), !dbg !15
  br label %6

; <label>:6                                       ; preds = %1, %4
  %7 = phi i8 [ %5, %4 ], [ undef, %1 ]
  %8 = icmp eq i8 %7, 0
  %9 = and i1 %3, %8
  %10 = icmp eq i8 %7, 1
  %11 = and i1 %3, %10
  %12 = and i1 true, %9
  %13 = select i1 %12, i8 0, i8 undef
  %14 = and i1 true, %11
  %15 = select i1 %14, i8 1, i8 %13
  ret i8 %15, !dbg !14
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_2", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_2] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !10}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_2", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!11 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 786688, metadata !10, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !10, null}
!15 = metadata !{i32 0, i32 0, metadata !16, null}
!16 = metadata !{i32 786443, metadata !10, i32 0, i32 0, metadata !6, i32 35} ; [ DW_TAG_lexical_block ] [/generate_call_2]
)%%%";

extern char const * const generate_call_3_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i32, i32, i8 }
%1 = type { i32, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !21), !dbg !22
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = and i1 %7, true
  %9 = select i1 %8, i8 0, i8 undef
  %10 = and i1 true, %6
  %11 = and i1 %10, true
  %12 = select i1 %11, i8 1, i8 %9
  %13 = insertvalue %0 undef, i32 1, 0
  %14 = insertvalue %0 %13, i32 2, 1
  %15 = insertvalue %0 %14, i8 %12, 2
  ret %0 %15, !dbg !22
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

define %1 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !23), !dbg !24
  %3 = and i1 true, true
  br i1 %3, label %4, label %6

; <label>:4                                       ; preds = %1
  %5 = call %0 @"0000000000000000-0000000000000000-0"(i1 %0), !dbg !25
  br label %6

; <label>:6                                       ; preds = %1, %4
  %7 = phi %0 [ %5, %4 ], [ undef, %1 ]
  %8 = extractvalue %0 %7, 2
  %9 = icmp eq i8 %8, 0
  %10 = and i1 %3, %9
  %11 = extractvalue %0 %7, 0
  %12 = icmp eq i8 %8, 1
  %13 = and i1 %3, %12
  %14 = extractvalue %0 %7, 1
  %15 = icmp eq i8 %8, 2
  %16 = and i1 %3, %15
  %17 = and i1 true, %10
  %18 = select i1 %17, i8 0, i8 undef
  %19 = and i1 true, %13
  %20 = select i1 %19, i8 1, i8 %18
  %21 = insertvalue %1 undef, i32 %14, 0
  %22 = insertvalue %1 %21, i8 %20, 1
  ret %1 %22, !dbg !24
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_3", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_3] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !16}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %0 (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_3", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !15}
!9 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 64, i64 0, i32 0, i32 0, null, metadata !10, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 64, align 0, offset 0] [from ]
!10 = metadata !{metadata !11, metadata !13, metadata !14}
!11 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 0, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 0] [from int32]
!12 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 786445, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i64 32, i32 0, metadata !12} ; [ DW_TAG_member ] [line 0, size 32, align 0, offset 32] [from int32]
!14 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 8} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned_char]
!15 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!16 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !17, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, %1 (i1)* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!17 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !18, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!18 = metadata !{metadata !19, metadata !15}
!19 = metadata !{i32 786451, metadata !6, metadata !"", metadata !6, i32 0, i64 32, i64 0, i32 0, i32 0, null, metadata !20, i32 0, i32 0, i32 0} ; [ DW_TAG_structure_type ] [line 0, size 32, align 0, offset 0] [from ]
!20 = metadata !{metadata !11, metadata !14}
!21 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!22 = metadata !{i32 0, i32 0, metadata !5, null}
!23 = metadata !{i32 786688, metadata !16, metadata !"parameter2", metadata !6, i32 0, metadata !15, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!24 = metadata !{i32 0, i32 0, metadata !16, null}
!25 = metadata !{i32 0, i32 0, metadata !26, null}
!26 = metadata !{i32 786443, metadata !16, i32 0, i32 0, metadata !6, i32 37} ; [ DW_TAG_lexical_block ] [/generate_call_3]
)%%%";

extern char const * const generate_call_out_of_order_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000001-0"(), !dbg !10
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !12
}

define void @"0000000000000000-0000000000000001-0"() {
  ret void, !dbg !13
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_out_of_order", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_out_of_order] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000000-1", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!6 = metadata !{i32 786473, metadata !"generate_call_out_of_order", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000001-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000001-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!10 = metadata !{i32 0, i32 0, metadata !11, null}
!11 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 60} ; [ DW_TAG_lexical_block ] [/generate_call_out_of_order]
!12 = metadata !{i32 0, i32 0, metadata !5, null}
!13 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_call_predicate_b1v0_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !10
}

define void @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !11
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !13
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_predicate_b1v0", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_predicate_b1v0] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_predicate_b1v0", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 0, i32 0, metadata !5, null}
!11 = metadata !{i32 0, i32 0, metadata !12, null}
!12 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 39} ; [ DW_TAG_lexical_block ] [/generate_call_predicate_b1v0]
!13 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_call_0_predicate_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !13
}

define i8 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !14), !dbg !15
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %6
  br i1 %7, label %8, label %9

; <label>:8                                       ; preds = %1
  call void @"0000000000000000-0000000000000000-0"(), !dbg !16
  br label %9

; <label>:9                                       ; preds = %1, %8
  %10 = and i1 true, %7
  %11 = select i1 %10, i8 0, i8 undef
  %12 = and i1 true, %4
  %13 = select i1 %12, i8 1, i8 %11
  ret i8 %13, !dbg !15
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_0_predicate", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_0_predicate] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_0_predicate", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !10, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i8 (i1)* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{null, metadata !12}
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 0, i32 0, metadata !5, null}
!14 = metadata !{i32 786688, metadata !9, metadata !"p0", metadata !6, i32 0, metadata !12, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [p0] [line 0]
!15 = metadata !{i32 0, i32 0, metadata !9, null}
!16 = metadata !{i32 0, i32 0, metadata !17, null}
!17 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 49} ; [ DW_TAG_lexical_block ] [/generate_call_0_predicate]
)%%%";

extern char const * const generate_call_predicate_b1v1_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !13
}

define i1 @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !14
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret i1 false, !dbg !16
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_call_predicate_b1v1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_call_predicate_b1v1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5, metadata !9}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_call_predicate_b1v1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 786478, i32 0, metadata !6, metadata !"1", metadata !"1", metadata !"0000000000000000-0000000000000001-1", metadata !6, i32 0, metadata !10, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i1 ()* @"0000000000000000-0000000000000001-1", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [1]
!10 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{metadata !12}
!12 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!13 = metadata !{i32 0, i32 0, metadata !5, null}
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !9, i32 0, i32 0, metadata !6, i32 41} ; [ DW_TAG_lexical_block ] [/generate_call_predicate_b1v1]
!16 = metadata !{i32 0, i32 0, metadata !9, null}
)%%%";

extern char const * const generate_loop1_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata !{i1* %2}, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = alloca i1
  call void @llvm.dbg.declare(metadata !{i1* %4}, metadata !12), !dbg !11
  br i1 %3, label %5, label %18

; <label>:5                                       ; preds = %7, %1
  %6 = phi i1 [ %0, %1 ], [ %6, %7 ]
  br label %7

; <label>:7                                       ; preds = %5
  store i1 %6, i1* %4
  %8 = and i1 true, true
  %9 = icmp eq i1 %6, false, !dbg !13
  %10 = icmp eq i1 %9, false
  %11 = and i1 %8, %10
  %12 = icmp eq i1 %9, true
  %13 = and i1 %8, %12
  %14 = and i1 true, %11
  %15 = and i1 %14, true
  %16 = and i1 true, %13
  %17 = select i1 %16, i8 0, i8 undef
  br i1 %15, label %5, label %18

; <label>:18                                      ; preds = %7, %1
  %19 = phi i8 [ undef, %1 ], [ %17, %7 ]
  br label %20

; <label>:20                                      ; preds = %18
  %21 = icmp eq i8 %19, 0
  %22 = and i1 %3, %21
  ret void, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_loop1", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_loop1] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void (i1)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_loop1", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int1", null, i32 0, i64 1, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int1] [line 0, size 1, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 0, i32 0, metadata !14, null}
!14 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 42} ; [ DW_TAG_lexical_block ] [/generate_loop1]
)%%%";

extern char const * const generate_loop_count_expected = R"%%%(; ModuleID = '0000000000000000'

define i32 @"0000000000000000-0000000000000000-0"(i32) {
  %2 = alloca i32
  store i32 %0, i32* %2
  call void @llvm.dbg.declare(metadata !{i32* %2}, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = alloca i32
  call void @llvm.dbg.declare(metadata !{i32* %4}, metadata !12), !dbg !11
  %5 = and i1 %3, true
  %6 = alloca i32
  call void @llvm.dbg.declare(metadata !{i32* %6}, metadata !13), !dbg !11
  br i1 %5, label %7, label %27

; <label>:7                                       ; preds = %10, %1
  %8 = phi i32 [ %0, %1 ], [ %19, %10 ]
  %9 = phi i32 [ 0, %1 ], [ %22, %10 ]
  br label %10

; <label>:10                                      ; preds = %7
  store i32 %8, i32* %4
  store i32 %9, i32* %6
  %11 = and i1 true, true
  %12 = icmp eq i32 %8, 0, !dbg !14
  %13 = icmp eq i1 %12, false
  %14 = and i1 %11, %13
  %15 = icmp eq i1 %12, true
  %16 = and i1 %11, %15
  %17 = and i1 true, %14
  %18 = and i1 true, true
  %19 = add i32 1, %8, !dbg !11
  %20 = and i1 %17, %18
  %21 = and i1 true, true
  %22 = add i32 1, %9, !dbg !11
  %23 = and i1 %20, %21
  %24 = and i1 true, %16
  %25 = and i1 %24, true
  %26 = select i1 %25, i8 0, i8 undef
  br i1 %23, label %7, label %27

; <label>:27                                      ; preds = %10, %1
  %28 = phi i8 [ undef, %1 ], [ %26, %10 ]
  %29 = phi i32 [ undef, %1 ], [ %9, %10 ]
  br label %30

; <label>:30                                      ; preds = %27
  %31 = icmp eq i8 %28, 0
  %32 = and i1 %5, %31
  ret i32 %29, !dbg !11
}

declare void @llvm.dbg.declare(metadata, metadata) nounwind readnone

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_loop_count", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_loop_count] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i32 (i32)* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_loop_count", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9, metadata !9}
!9 = metadata !{i32 786468, null, metadata !"int32", null, i32 0, i64 32, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int32] [line 0, size 32, align 0, offset 0, enc DW_ATE_unsigned]
!10 = metadata !{i32 786688, metadata !5, metadata !"parameter1", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter1] [line 0]
!11 = metadata !{i32 0, i32 0, metadata !5, null}
!12 = metadata !{i32 786688, metadata !5, metadata !"parameter2", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter2] [line 0]
!13 = metadata !{i32 786688, metadata !5, metadata !"parameter3", metadata !6, i32 0, metadata !9, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [parameter3] [line 0]
!14 = metadata !{i32 0, i32 0, metadata !15, null}
!15 = metadata !{i32 786443, metadata !5, i32 0, i32 0, metadata !6, i32 43} ; [ DW_TAG_lexical_block ] [/generate_loop_count]
)%%%";

extern char const * const generate_asm_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void asm sideeffect "text", ""()
  br label %2

; <label>:2                                       ; preds = %1, %0
  ret void, !dbg !9
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_asm", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_asm] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_asm", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_asm2_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  %1 = and i1 true, true
  br i1 %1, label %2, label %4

; <label>:2                                       ; preds = %0
  %3 = call i32 asm sideeffect "bswap $0", "=r,r"(i32 -1122868)
  br label %4

; <label>:4                                       ; preds = %2, %0
  %5 = phi i32 [ %3, %2 ], [ undef, %0 ]
  %6 = and i1 %1, %1
  %7 = add i32 %5, %5, !dbg !9
  ret void, !dbg !9
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_asm2", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_asm2] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_asm2", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{null}
!9 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";

extern char const * const generate_array_expected = R"%%%(; ModuleID = '0000000000000000'

define [16 x i8] @"0000000000000000-0000000000000000-0"() {
  ret [16 x i8] c"\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD", !dbg !12
}

!llvm.dbg.cu = !{!0}

!0 = metadata !{i32 786449, i32 0, i32 2, metadata !"generate_array", metadata !"", metadata !"MU 0 (Colin LeMahieu)", i1 true, i1 false, metadata !"", i32 0, metadata !1, metadata !1, metadata !3, metadata !1} ; [ DW_TAG_compile_unit ] [/generate_array] [DW_LANG_C]
!1 = metadata !{metadata !2}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4}
!4 = metadata !{metadata !5}
!5 = metadata !{i32 786478, i32 0, metadata !6, metadata !"0", metadata !"0", metadata !"0000000000000000-0000000000000000-0", metadata !6, i32 0, metadata !7, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, [16 x i8] ()* @"0000000000000000-0000000000000000-0", null, null, metadata !1, i32 0} ; [ DW_TAG_subprogram ] [line 0] [def] [0]
!6 = metadata !{i32 786473, metadata !"generate_array", metadata !"", null} ; [ DW_TAG_file_type ]
!7 = metadata !{i32 786453, i32 0, metadata !"", i32 0, i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !8, i32 0, i32 0} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!8 = metadata !{metadata !9}
!9 = metadata !{i32 786433, null, metadata !"", null, i32 0, i64 16, i64 0, i32 0, i32 0, metadata !10, metadata !11, i32 0, i32 0} ; [ DW_TAG_array_type ] [line 0, size 16, align 0, offset 0] [from int8]
!10 = metadata !{i32 786468, null, metadata !"int8", null, i32 0, i64 8, i64 0, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [int8] [line 0, size 8, align 0, offset 0, enc DW_ATE_unsigned]
!11 = metadata !{i64 0, i64 16}
!12 = metadata !{i32 0, i32 0, metadata !5, null}
)%%%";