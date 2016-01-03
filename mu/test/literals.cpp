extern char const * const generate_empty_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  unreachable, !dbg !7
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_empty", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
  call void @llvm.dbg.declare(metadata i32** %2, metadata !12, metadata !13), !dbg !14
  %3 = bitcast i32* %0 to i8*, !dbg !14
  %4 = alloca i8*
  store i8* %3, i8** %4
  call void @llvm.dbg.declare(metadata i8** %4, metadata !15, metadata !13), !dbg !14
  call void @llvm.dbg.value(metadata i8* %3, i64 0, metadata !15, metadata !13), !dbg !14
  ret i8* %3, !dbg !14
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_bitcast", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !10}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !9, size: 8)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !11, size: 8)
!11 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!12 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !10)
!13 = !DIExpression()
!14 = !DILocation(line: 0, scope: !4)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
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
  call void @llvm.dbg.declare(metadata { i1 }* %2, metadata !11, metadata !12), !dbg !13
  %3 = and i1 true, true
  %4 = extractvalue { i1 } %0, 0, !dbg !13
  %5 = alloca i1
  store i1 %4, i1* %5
  call void @llvm.dbg.declare(metadata i1* %5, metadata !14, metadata !12), !dbg !13
  call void @llvm.dbg.value(metadata i1 %4, i64 0, metadata !14, metadata !12), !dbg !13
  ret i1 %4, !dbg !13
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_extractvalue", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 1, elements: !10)
!10 = !{!7}
!11 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!12 = !DIExpression()
!13 = !DILocation(line: 0, scope: !4)
!14 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_getelementptr_expected = R"%%%(; ModuleID = '0000000000000000'

define i8* @"0000000000000000-0000000000000000-0"(i8*) {
  %2 = alloca i8*
  store i8* %0, i8** %2
  call void @llvm.dbg.declare(metadata i8** %2, metadata !10, metadata !11), !dbg !12
  %3 = and i1 true, true
  %4 = getelementptr inbounds i8, i8* %0, i8 0, !dbg !12
  %5 = alloca i8*
  store i8* %4, i8** %5
  call void @llvm.dbg.declare(metadata i8** %5, metadata !13, metadata !11), !dbg !12
  call void @llvm.dbg.value(metadata i8* %4, i64 0, metadata !13, metadata !11), !dbg !12
  ret i8* %4, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_getelementptr", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !9, size: 8)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_global_variable_expected = R"%%%(; ModuleID = '0000000000000000'

@"0000000000000000-0000000000000000-0" = global i32 42

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, globals: !3)
!1 = !DIFile(filename: "generate_global_variable", directory: "")
!2 = !{}
!3 = !{!4}
!4 = !DIGlobalVariable(name: "0", linkageName: "0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, variable: i32* @"0000000000000000-0000000000000000-0")
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !6, size: 8)
!6 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
  call void @llvm.dbg.declare(metadata i8* %2, metadata !9, metadata !10), !dbg !11
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !12, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %0, i64 0, metadata !12, metadata !10), !dbg !11
  ret i8 %0, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_identity", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "element1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_lshr_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = lshr i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_lshr", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_insertvalue_expected = R"%%%(; ModuleID = '0000000000000000'

define { i1 } @"0000000000000000-0000000000000000-0"(i1, { i1 }) {
  %3 = alloca i1
  store i1 %0, i1* %3
  call void @llvm.dbg.declare(metadata i1* %3, metadata !12, metadata !13), !dbg !14
  %4 = alloca { i1 }
  store { i1 } %1, { i1 }* %4
  call void @llvm.dbg.declare(metadata { i1 }* %4, metadata !15, metadata !13), !dbg !14
  %5 = and i1 true, true
  %6 = insertvalue { i1 } %1, i1 %0, 0, !dbg !14
  %7 = alloca { i1 }
  store { i1 } %6, { i1 }* %7
  call void @llvm.dbg.declare(metadata { i1 }* %7, metadata !16, metadata !13), !dbg !14
  call void @llvm.dbg.value(metadata { i1 } %6, i64 0, metadata !16, metadata !13), !dbg !14
  ret { i1 } %6, !dbg !14
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_insertvalue", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !11, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 1, elements: !9)
!9 = !{!10}
!10 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !11, size: 1)
!11 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!12 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !11)
!13 = !DIExpression()
!14 = !DILocation(line: 0, scope: !4)
!15 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!16 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
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
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = mul i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_mul", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_or_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = or i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_or", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_ptrfromint_expected = R"%%%(; ModuleID = '0000000000000000'

define i32* @"0000000000000000-0000000000000000-0"(i64) {
  %2 = alloca i64
  store i64 %0, i64* %2
  call void @llvm.dbg.declare(metadata i64* %2, metadata !11, metadata !12), !dbg !13
  %3 = inttoptr i64 %0 to i32*, !dbg !13
  %4 = alloca i32*
  store i32* %3, i32** %4
  call void @llvm.dbg.declare(metadata i32** %4, metadata !14, metadata !12), !dbg !13
  call void @llvm.dbg.value(metadata i32* %3, i64 0, metadata !14, metadata !12), !dbg !13
  ret i32* %3, !dbg !13
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_ptrfromint", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !10}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 8)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !9, size: 8)
!9 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!10 = !DIBasicType(name: "int64", size: 64, encoding: DW_ATE_unsigned)
!11 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !10)
!12 = !DIExpression()
!13 = !DILocation(line: 0, scope: !4)
!14 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_ptrtoint_expected = R"%%%(; ModuleID = '0000000000000000'

define i64 @"0000000000000000-0000000000000000-0"(i32*) {
  %2 = alloca i32*
  store i32* %0, i32** %2
  call void @llvm.dbg.declare(metadata i32** %2, metadata !11, metadata !12), !dbg !13
  %3 = ptrtoint i32* %0 to i64, !dbg !13
  %4 = alloca i64
  store i64 %3, i64* %4
  call void @llvm.dbg.declare(metadata i64* %4, metadata !14, metadata !12), !dbg !13
  call void @llvm.dbg.value(metadata i64 %3, i64 0, metadata !14, metadata !12), !dbg !13
  ret i64 %3, !dbg !13
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_ptrtoint", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 64)
!8 = !DIBasicType(name: "int64", size: 64, encoding: DW_ATE_unsigned)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !10, size: 8)
!10 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!11 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!12 = !DIExpression()
!13 = !DILocation(line: 0, scope: !4)
!14 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_sdiv_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = sdiv i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_sdiv", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_select_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = and i1 %3, true
  %5 = select i1 %0, i1 %0, i1 %0, !dbg !11
  %6 = alloca i1
  store i1 %5, i1* %6
  call void @llvm.dbg.declare(metadata i1* %6, metadata !12, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %5, i64 0, metadata !12, metadata !10), !dbg !11
  ret i1 %5, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_select_expected", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_sext_expected = R"%%%(; ModuleID = '0000000000000000'

define i16 @"0000000000000000-0000000000000000-0"(i8) {
  %2 = alloca i8
  store i8 %0, i8* %2
  call void @llvm.dbg.declare(metadata i8* %2, metadata !10, metadata !11), !dbg !12
  %3 = sext i8 %0 to i16, !dbg !12
  %4 = alloca i16
  store i16 %3, i16* %4
  call void @llvm.dbg.declare(metadata i16* %4, metadata !13, metadata !11), !dbg !12
  call void @llvm.dbg.value(metadata i16 %3, i64 0, metadata !13, metadata !11), !dbg !12
  ret i16 %3, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_sext", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 16)
!8 = !DIBasicType(name: "int16", size: 16, encoding: DW_ATE_unsigned)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_shl_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = shl i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_shl", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_srem_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = srem i8 %0, %1, !dbg !11
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
!1 = !DIFile(filename: "generate_srem", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, variables: !2)
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

extern char const * const generate_store_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1, i1*) {
  %3 = alloca i1
  store i1 %0, i1* %3
  call void @llvm.dbg.declare(metadata i1* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i1*
  store i1* %1, i1** %4
  call void @llvm.dbg.declare(metadata i1** %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  br i1 %5, label %6, label %7

; <label>:6                                       ; preds = %2
  store i1 %0, i1* %1, !dbg !13
  br label %7

; <label>:7                                       ; preds = %6, %2
  ret void, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_store", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void (i1, i1*)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7, !8}
!7 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, name: "ptr", baseType: !7, size: 8)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !7)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
)%%%";

extern char const * const generate_struct_type_undefined_expected = R"%%%(; ModuleID = '0000000000000000'

define { i1 } @"0000000000000000-0000000000000000-0"({ i1 }) {
  %2 = alloca { i1 }
  store { i1 } %0, { i1 }* %2
  call void @llvm.dbg.declare(metadata { i1 }* %2, metadata !12, metadata !13), !dbg !14
  ret { i1 } undef, !dbg !14
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_struct_type_undefined", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: { i1 } ({ i1 })* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 1, elements: !9)
!9 = !{!10}
!10 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !11, size: 1)
!11 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!12 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!13 = !DIExpression()
!14 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_sub_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = sub i1 %0, %0, !dbg !12
  %5 = alloca i1
  store i1 %4, i1* %5
  call void @llvm.dbg.declare(metadata i1* %5, metadata !14, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %4, i64 0, metadata !14, metadata !10), !dbg !11
  ret i1 %4, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_sub", directory: "")
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
!12 = !DILocation(line: 0, scope: !13)
!13 = distinct !DILexicalBlock(scope: !4, file: !1)
!14 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_udiv_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = udiv i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !15, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !15, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_udiv", directory: "")
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
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_urem_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = urem i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !15, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !15, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_urem", directory: "")
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
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_xor_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i8, i8) {
  %3 = alloca i8
  store i8 %0, i8* %3
  call void @llvm.dbg.declare(metadata i8* %3, metadata !9, metadata !10), !dbg !11
  %4 = alloca i8
  store i8 %1, i8* %4
  call void @llvm.dbg.declare(metadata i8* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 true, true
  %6 = xor i8 %0, %1, !dbg !13
  %7 = alloca i8
  store i8 %6, i8* %7
  call void @llvm.dbg.declare(metadata i8* %7, metadata !15, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i8 %6, i64 0, metadata !15, metadata !10), !dbg !11
  ret i8 %6, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_xor", directory: "")
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
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !4, file: !1)
!15 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_zext_expected = R"%%%(; ModuleID = '0000000000000000'

define i16 @"0000000000000000-0000000000000000-0"(i8) {
  %2 = alloca i8
  store i8 %0, i8* %2
  call void @llvm.dbg.declare(metadata i8* %2, metadata !10, metadata !11), !dbg !12
  %3 = zext i8 %0 to i16, !dbg !12
  %4 = alloca i16
  store i16 %3, i16* %4
  call void @llvm.dbg.declare(metadata i16* %4, metadata !13, metadata !11), !dbg !12
  call void @llvm.dbg.value(metadata i16 %3, i64 0, metadata !13, metadata !11), !dbg !12
  ret i16 %3, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_zext", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i16 (i8)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 16)
!8 = !DIBasicType(name: "int16", size: 16, encoding: DW_ATE_unsigned)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "instruction1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_two_return_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i1, i1 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !12, metadata !13), !dbg !14
  %3 = insertvalue %0 undef, i1 %0, 0
  %4 = insertvalue %0 %3, i1 %0, 1
  ret %0 %4, !dbg !14
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_two_return", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: %0 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !10}
!7 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 2, elements: !8)
!8 = !{!9, !11}
!9 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 1)
!10 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 1, offset: 1)
!12 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !10)
!13 = !DIExpression()
!14 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_if_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
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

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_if_value_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i32, i32, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !14, metadata !15), !dbg !16
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
  ret %0 %15, !dbg !16
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_value", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: %0 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !13}
!7 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 64, elements: !8)
!8 = !{!9, !11, !12}
!9 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 32)
!10 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 32, offset: 32)
!12 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!13 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!14 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !13)
!15 = !DIExpression()
!16 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_if_join_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !8, metadata !9), !dbg !10
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  %8 = and i1 true, %6
  %9 = or i1 false, %7
  %10 = or i1 %9, %8
  ret void, !dbg !10
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_join", directory: "")
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

extern char const * const generate_if_join_value_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 true, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 true, %6
  %8 = and i1 %3, %7
  %9 = add i1 %0, %0, !dbg !11
  %10 = alloca i1
  store i1 %9, i1* %10
  call void @llvm.dbg.declare(metadata i1* %10, metadata !12, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %9, i64 0, metadata !12, metadata !10), !dbg !11
  %11 = and i1 true, %8
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !11
  %15 = alloca i1
  store i1 %14, i1* %15
  call void @llvm.dbg.declare(metadata i1* %15, metadata !13, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %14, i64 0, metadata !13, metadata !10), !dbg !11
  %16 = and i1 true, %13
  %17 = or i1 false, %11
  %18 = select i1 %11, i1 %9, i1 undef
  %19 = or i1 %17, %16
  %20 = select i1 %16, i1 %14, i1 %18
  %21 = alloca i1
  store i1 %20, i1* %21
  call void @llvm.dbg.declare(metadata i1* %21, metadata !14, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %20, i64 0, metadata !14, metadata !10), !dbg !11
  ret i1 %20, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_join_value", directory: "")
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
!12 = !DILocalVariable(name: "add1", scope: !4, file: !1, type: !8)
!13 = !DILocalVariable(name: "add2", scope: !4, file: !1, type: !8)
!14 = !DILocalVariable(name: "join1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_if_join_value_predicate_expected = R"%%%(; ModuleID = '0000000000000000'

define i32 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !10, metadata !11), !dbg !12
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
  call void @llvm.dbg.declare(metadata i32* %15, metadata !13, metadata !11), !dbg !12
  call void @llvm.dbg.value(metadata i32 %14, i64 0, metadata !13, metadata !11), !dbg !12
  ret i32 %14, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_join_value_predicate", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i32 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 32)
!8 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!9 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !9)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "join1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_if_join_2value_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i1, i1, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !13, metadata !14), !dbg !15
  %3 = and i1 true, true
  %4 = icmp eq i1 %0, false
  %5 = and i1 true, %4
  %6 = icmp eq i1 %0, true
  %7 = and i1 true, %6
  %8 = and i1 %3, %5
  %9 = add i1 %0, %0, !dbg !15
  %10 = alloca i1
  store i1 %9, i1* %10
  call void @llvm.dbg.declare(metadata i1* %10, metadata !16, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %9, i64 0, metadata !16, metadata !14), !dbg !15
  %11 = and i1 true, %8
  %12 = and i1 true, true
  %13 = and i1 %12, %7
  %14 = add i1 %0, %0, !dbg !15
  %15 = alloca i1
  store i1 %14, i1* %15
  call void @llvm.dbg.declare(metadata i1* %15, metadata !17, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %14, i64 0, metadata !17, metadata !14), !dbg !15
  %16 = and i1 true, %13
  %17 = or i1 false, %11
  %18 = select i1 %11, i1 %9, i1 undef
  %19 = or i1 %17, %16
  %20 = select i1 %16, i1 %14, i1 %18
  %21 = alloca i1
  store i1 %20, i1* %21
  call void @llvm.dbg.declare(metadata i1* %21, metadata !18, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %20, i64 0, metadata !18, metadata !14), !dbg !15
  %22 = and i1 true, %19
  %23 = select i1 %22, i8 0, i8 undef
  %24 = and i1 true, true
  %25 = and i1 %24, %5
  %26 = add i1 %0, %0, !dbg !15
  %27 = alloca i1
  store i1 %26, i1* %27
  call void @llvm.dbg.declare(metadata i1* %27, metadata !19, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %26, i64 0, metadata !19, metadata !14), !dbg !15
  %28 = and i1 true, %25
  %29 = and i1 true, true
  %30 = and i1 %29, %7
  %31 = add i1 %0, %0, !dbg !15
  %32 = alloca i1
  store i1 %31, i1* %32
  call void @llvm.dbg.declare(metadata i1* %32, metadata !20, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %31, i64 0, metadata !20, metadata !14), !dbg !15
  %33 = and i1 true, %30
  %34 = or i1 false, %28
  %35 = select i1 %28, i1 %26, i1 undef
  %36 = or i1 %34, %33
  %37 = select i1 %33, i1 %31, i1 %35
  %38 = alloca i1
  store i1 %37, i1* %38
  call void @llvm.dbg.declare(metadata i1* %38, metadata !21, metadata !14), !dbg !15
  call void @llvm.dbg.value(metadata i1 %37, i64 0, metadata !21, metadata !14), !dbg !15
  %39 = and i1 true, %36
  %40 = select i1 %39, i8 1, i8 %23
  %41 = insertvalue %0 undef, i1 %20, 0
  %42 = insertvalue %0 %41, i1 %37, 1
  %43 = insertvalue %0 %42, i8 %40, 2
  ret %0 %43, !dbg !15
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_join_2value", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: %0 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !10}
!7 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 2, elements: !8)
!8 = !{!9, !11, !12}
!9 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 1)
!10 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 1, offset: 1)
!12 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!13 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !10)
!14 = !DIExpression()
!15 = !DILocation(line: 0, scope: !4)
!16 = !DILocalVariable(name: "add1", scope: !4, file: !1, type: !10)
!17 = !DILocalVariable(name: "add2", scope: !4, file: !1, type: !10)
!18 = !DILocalVariable(name: "join1", scope: !4, file: !1, type: !10)
!19 = !DILocalVariable(name: "add3", scope: !4, file: !1, type: !10)
!20 = !DILocalVariable(name: "add4", scope: !4, file: !1, type: !10)
!21 = !DILocalVariable(name: "join2", scope: !4, file: !1, type: !10)
)%%%";

extern char const * const generate_if_join_load_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !9, metadata !10), !dbg !11
  %3 = icmp eq i1 %0, false
  %4 = and i1 true, %3
  %5 = icmp eq i1 %0, true
  %6 = and i1 true, %5
  %7 = and i1 true, %4
  br i1 %7, label %8, label %10

; <label>:8                                       ; preds = %1
  %9 = load i1, i1* null, !dbg !12
  br label %10

; <label>:10                                      ; preds = %8, %1
  %11 = phi i1 [ %9, %8 ], [ undef, %1 ]
  %12 = alloca i1
  store i1 %11, i1* %12
  call void @llvm.dbg.declare(metadata i1* %12, metadata !14, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %11, i64 0, metadata !14, metadata !10), !dbg !11
  %13 = and i1 true, %7
  %14 = and i1 true, %6
  br i1 %14, label %15, label %17

; <label>:15                                      ; preds = %10
  %16 = load i1, i1* null, !dbg !12
  br label %17

; <label>:17                                      ; preds = %15, %10
  %18 = phi i1 [ %16, %15 ], [ undef, %10 ]
  %19 = alloca i1
  store i1 %18, i1* %19
  call void @llvm.dbg.declare(metadata i1* %19, metadata !15, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %18, i64 0, metadata !15, metadata !10), !dbg !11
  %20 = and i1 true, %14
  %21 = or i1 false, %13
  %22 = select i1 %13, i1 %11, i1 undef
  %23 = or i1 %21, %20
  %24 = select i1 %20, i1 %18, i1 %22
  %25 = alloca i1
  store i1 %24, i1* %25
  call void @llvm.dbg.declare(metadata i1* %25, metadata !16, metadata !10), !dbg !11
  call void @llvm.dbg.value(metadata i1 %24, i64 0, metadata !16, metadata !10), !dbg !11
  ret i1 %24, !dbg !11
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_if_join_load", directory: "")
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
!12 = !DILocation(line: 0, scope: !13)
!13 = distinct !DILexicalBlock(scope: !4, file: !1)
!14 = !DILocalVariable(name: "load1", scope: !4, file: !1, type: !8)
!15 = !DILocalVariable(name: "load2", scope: !4, file: !1, type: !8)
!16 = !DILocalVariable(name: "join1", scope: !4, file: !1, type: !8)
)%%%";

extern char const * const generate_call_0_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !8
}

define void @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !9
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !11
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_0", directory: "")
!2 = !{}
!3 = !{!4, !7}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000001-1", variables: !2)
!8 = !DILocation(line: 0, scope: !4)
!9 = !DILocation(line: 0, scope: !10)
!10 = distinct !DILexicalBlock(scope: !7, file: !1)
!11 = !DILocation(line: 0, scope: !7)
)%%%";

extern char const * const generate_call_1_expected = R"%%%(; ModuleID = '0000000000000000'

define i1 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !10, metadata !11), !dbg !12
  ret i1 %0, !dbg !12
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

define i1 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !13, metadata !11), !dbg !14
  %3 = and i1 true, true
  br i1 %3, label %4, label %6

; <label>:4                                       ; preds = %1
  %5 = call i1 @"0000000000000000-0000000000000000-0"(i1 %0), !dbg !15
  br label %6

; <label>:6                                       ; preds = %1, %4
  %7 = phi i1 [ %5, %4 ], [ undef, %1 ]
  ret i1 %7, !dbg !14
}

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_1", directory: "")
!2 = !{}
!3 = !{!4, !9}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i1 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 1)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i1 (i1)* @"0000000000000000-0000000000000001-1", variables: !2)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "parameter2", scope: !9, file: !1, type: !8)
!14 = !DILocation(line: 0, scope: !9)
!15 = !DILocation(line: 0, scope: !16)
!16 = distinct !DILexicalBlock(scope: !9, file: !1)
)%%%";

extern char const * const generate_call_2_expected = R"%%%(; ModuleID = '0000000000000000'

define i8 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !10, metadata !11), !dbg !12
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

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

define i8 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !13, metadata !11), !dbg !14
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

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_2", directory: "")
!2 = !{}
!3 = !{!4, !9}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!8 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!9 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i1)* @"0000000000000000-0000000000000001-1", variables: !2)
!10 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!11 = !DIExpression()
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "parameter2", scope: !9, file: !1, type: !8)
!14 = !DILocation(line: 0, scope: !9)
!15 = !DILocation(line: 0, scope: !16)
!16 = distinct !DILexicalBlock(scope: !9, file: !1)
)%%%";

extern char const * const generate_call_3_expected = R"%%%(; ModuleID = '0000000000000000'

%0 = type { i32, i32, i8 }
%1 = type { i32, i8 }

define %0 @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !19, metadata !20), !dbg !21
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
  ret %0 %15, !dbg !21
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

define %1 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !22, metadata !20), !dbg !23
  %3 = and i1 true, true
  br i1 %3, label %4, label %6

; <label>:4                                       ; preds = %1
  %5 = call %0 @"0000000000000000-0000000000000000-0"(i1 %0), !dbg !24
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
  ret %1 %22, !dbg !23
}

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_3", directory: "")
!2 = !{}
!3 = !{!4, !14}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: %0 (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !13}
!7 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 64, elements: !8)
!8 = !{!9, !11, !12}
!9 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 32)
!10 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !10, size: 32, offset: 32)
!12 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!13 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!14 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !15, isLocal: false, isDefinition: true, isOptimized: false, function: %1 (i1)* @"0000000000000000-0000000000000001-1", variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!17, !13}
!17 = !DICompositeType(tag: DW_TAG_structure_type, scope: !1, file: !1, size: 32, elements: !18)
!18 = !{!9, !12}
!19 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !13)
!20 = !DIExpression()
!21 = !DILocation(line: 0, scope: !4)
!22 = !DILocalVariable(name: "parameter2", scope: !14, file: !1, type: !13)
!23 = !DILocation(line: 0, scope: !14)
!24 = !DILocation(line: 0, scope: !25)
!25 = distinct !DILexicalBlock(scope: !14, file: !1)
)%%%";

extern char const * const generate_call_out_of_order_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000001-0"(), !dbg !8
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !10
}

define void @"0000000000000000-0000000000000001-0"() {
  ret void, !dbg !11
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_out_of_order", directory: "")
!2 = !{}
!3 = !{!4, !7}
!4 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000000-1", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-1", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000001-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000001-0", variables: !2)
!8 = !DILocation(line: 0, scope: !9)
!9 = distinct !DILexicalBlock(scope: !4, file: !1)
!10 = !DILocation(line: 0, scope: !4)
!11 = !DILocation(line: 0, scope: !7)
)%%%";

extern char const * const generate_call_predicate_b1v0_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !8
}

define void @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !9
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret void, !dbg !11
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_predicate_b1v0", directory: "")
!2 = !{}
!3 = !{!4, !7}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000001-1", variables: !2)
!8 = !DILocation(line: 0, scope: !4)
!9 = !DILocation(line: 0, scope: !10)
!10 = distinct !DILexicalBlock(scope: !7, file: !1)
!11 = !DILocation(line: 0, scope: !7)
)%%%";

extern char const * const generate_call_0_predicate_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !12
}

define i8 @"0000000000000000-0000000000000001-1"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !13, metadata !14), !dbg !15
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

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_0_predicate", directory: "")
!2 = !{}
!3 = !{!4, !7}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !8, isLocal: false, isDefinition: true, isOptimized: false, function: i8 (i1)* @"0000000000000000-0000000000000001-1", variables: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10, !11}
!10 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned_char)
!11 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocalVariable(name: "p0", scope: !7, file: !1, type: !11)
!14 = !DIExpression()
!15 = !DILocation(line: 0, scope: !7)
!16 = !DILocation(line: 0, scope: !17)
!17 = distinct !DILexicalBlock(scope: !7, file: !1)
)%%%";

extern char const * const generate_call_predicate_b1v1_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  ret void, !dbg !12
}

define i1 @"0000000000000000-0000000000000001-1"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void @"0000000000000000-0000000000000000-0"(), !dbg !13
  br label %2

; <label>:2                                       ; preds = %0, %1
  ret i1 false, !dbg !15
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_call_predicate_b1v1", directory: "")
!2 = !{}
!3 = !{!4, !7}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = distinct !DISubprogram(name: "1", linkageName: "0000000000000000-0000000000000001-1", scope: !1, file: !1, type: !8, isLocal: false, isDefinition: true, isOptimized: false, function: i1 ()* @"0000000000000000-0000000000000001-1", variables: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !11, size: 1)
!11 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!12 = !DILocation(line: 0, scope: !4)
!13 = !DILocation(line: 0, scope: !14)
!14 = distinct !DILexicalBlock(scope: !7, file: !1)
!15 = !DILocation(line: 0, scope: !7)
)%%%";

extern char const * const generate_loop1_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"(i1) {
  %2 = alloca i1
  store i1 %0, i1* %2
  call void @llvm.dbg.declare(metadata i1* %2, metadata !8, metadata !9), !dbg !10
  %3 = and i1 true, true
  %4 = alloca i1
  call void @llvm.dbg.declare(metadata i1* %4, metadata !11, metadata !9), !dbg !10
  br i1 %3, label %5, label %18

; <label>:5                                       ; preds = %7, %1
  %6 = phi i1 [ %0, %1 ], [ %6, %7 ]
  br label %7

; <label>:7                                       ; preds = %5
  store i1 %6, i1* %4
  %8 = and i1 true, true
  %9 = icmp eq i1 %6, false, !dbg !12
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
  ret void, !dbg !10
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_loop1", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void (i1)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7}
!7 = !DIBasicType(name: "int1", size: 1, encoding: DW_ATE_unsigned)
!8 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !7)
!9 = !DIExpression()
!10 = !DILocation(line: 0, scope: !4)
!11 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !7)
!12 = !DILocation(line: 0, scope: !13)
!13 = distinct !DILexicalBlock(scope: !4, file: !1)
)%%%";

extern char const * const generate_loop_count_expected = R"%%%(; ModuleID = '0000000000000000'

define i32 @"0000000000000000-0000000000000000-0"(i32) {
  %2 = alloca i32
  store i32 %0, i32* %2
  call void @llvm.dbg.declare(metadata i32* %2, metadata !9, metadata !10), !dbg !11
  %3 = and i1 true, true
  %4 = alloca i32
  call void @llvm.dbg.declare(metadata i32* %4, metadata !12, metadata !10), !dbg !11
  %5 = and i1 %3, true
  %6 = alloca i32
  call void @llvm.dbg.declare(metadata i32* %6, metadata !13, metadata !10), !dbg !11
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

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #0

attributes #0 = { nounwind readnone }

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_loop_count", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: i32 (i32)* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 32)
!8 = !DIBasicType(name: "int32", size: 32, encoding: DW_ATE_unsigned)
!9 = !DILocalVariable(name: "parameter1", scope: !4, file: !1, type: !8)
!10 = !DIExpression()
!11 = !DILocation(line: 0, scope: !4)
!12 = !DILocalVariable(name: "parameter2", scope: !4, file: !1, type: !8)
!13 = !DILocalVariable(name: "parameter3", scope: !4, file: !1, type: !8)
!14 = !DILocation(line: 0, scope: !15)
!15 = distinct !DILexicalBlock(scope: !4, file: !1)
)%%%";

extern char const * const generate_asm_expected = R"%%%(; ModuleID = '0000000000000000'

define void @"0000000000000000-0000000000000000-0"() {
  br i1 true, label %1, label %2

; <label>:1                                       ; preds = %0
  call void asm sideeffect "text", ""()
  br label %2

; <label>:2                                       ; preds = %1, %0
  ret void, !dbg !7
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_asm", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = !DILocation(line: 0, scope: !4)
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
  %7 = add i32 %5, %5, !dbg !7
  ret void, !dbg !7
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_asm2", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: void ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = !DILocation(line: 0, scope: !4)
)%%%";

extern char const * const generate_array_expected = R"%%%(; ModuleID = '0000000000000000'

define [16 x i8] @"0000000000000000-0000000000000000-0"() {
  ret [16 x i8] c"\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD\CD", !dbg !11
}

!llvm.dbg.cu = !{!0}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "MU 0 (Colin LeMahieu)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "generate_array", directory: "")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "0", linkageName: "0000000000000000-0000000000000000-0", scope: !1, file: !1, type: !5, isLocal: false, isDefinition: true, isOptimized: false, function: [16 x i8] ()* @"0000000000000000-0000000000000000-0", variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIDerivedType(tag: DW_TAG_member, scope: !1, file: !1, baseType: !8, size: 16)
!8 = !DICompositeType(tag: DW_TAG_array_type, baseType: !9, size: 16, elements: !10)
!9 = !DIBasicType(name: "int8", size: 8, encoding: DW_ATE_unsigned)
!10 = !{i64 0, i64 16}
!11 = !DILocation(line: 0, scope: !4)
)%%%";