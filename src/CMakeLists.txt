file(GLOB_RECURSE BOOTLOADER_SOURCES CONFIGURE_DEPENDS 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.S"
)

add_executable(bootloader
        ${BOOTLOADER_SOURCES}
)

target_include_directories(bootloader PRIVATE
        "${ROSE_INCLUDE_DIRECTORY}"
)

target_compile_options(bootloader PRIVATE
        -target x86_64-pc-windows-msvc
        -O0
        -ffreestanding
        -mno-red-zone
        -nostdlib
)

target_link_options(bootloader PRIVATE
        -target x86_64-pc-windows-msvc
        -nostdlib
        -Wl,-entry:efi_bootloader
        -Wl,-subsystem:efi_application
)

set_target_properties(bootloader PROPERTIES
        OUTPUT_NAME "BOOTX64"
        SUFFIX ".EFI"
)