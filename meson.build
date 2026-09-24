project('ROSE', 'c', 'cpp',
        version: '0.1',
        default_options: [
                'c_std=c89',
                'cpp_std=c++11',
                'b_vscrt=none',
                'b_staticpic=false'
        ]
)

common_kernel_args = [
  '-mno-red-zone',
  '-nostdlib',
  '-fno-builtin',
  '-ffreestanding'
]

cpp_kernel_args = common_kernel_args + [
  '-fno-exceptions',
  '-fno-rtti',
  '-fno-threadsafe-statics',
  '-nostdinc++'
]

uefi_link_args = [
  '-Wl,/nodefaultlib',
  '-fuse-ld=lld',
  '-Wl,/subsystem:efi_application',
  '-Wl,/entry:efi_bootloader'
]

inc_dir = include_directories('src',)

sources = [
        'src/boot.c',
        'src/efi/efi_utils.c',
        'src/rose/elf.c'
]

executable('BOOTX64', sources,
        include_directories: inc_dir,
        c_args: common_kernel_args,
        cpp_args: cpp_kernel_args,
        link_args: uefi_link_args,
        name_suffix: 'EFI'
)