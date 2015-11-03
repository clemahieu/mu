set(LLVM_LINK_COMPONENTS
  Core
  MC)

find_package (Boost REQUIRED COMPONENTS filesystem program_options system)
include_directories (${Boost_INCLUDE_DIR})

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (mu/core)
add_subdirectory (mu/io)
add_subdirectory (mu/llvmc)
add_subdirectory (mu/test)
add_subdirectory (mu/muc)
