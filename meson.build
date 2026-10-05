project('ROSE', 'c',
        version: '0.1',
        default_options: [
                'c_std=c89',
                'b_staticpic=false'
        ]
)

inc_dir = include_directories('src',)

bootloader_args = [
        '-mno-red-zone',
        '-nostdlib',
        '-fno-builtin',
        '-ffreestanding'
]

bootloader_sources = [
        'src/boot.c',
        'src/efi/efi_utils.c',
        'src/rose/basic_memory.c',
        'src/rose/elf.c'
]

bootloader_link_args = [
        '-Wl,/nodefaultlib',
        '-fuse-ld=lld',
        '-Wl,/subsystem:efi_application',
        '-Wl,/entry:efi_bootloader'
]

executable('BOOTX64', bootloader_sources,
        include_directories: inc_dir,
        c_args: bootloader_args,
        link_args: bootloader_link_args,
        name_suffix: 'EFI'
)