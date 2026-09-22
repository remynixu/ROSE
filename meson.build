project('ROSE', 'c',
        version: '0.1',
        default_options: ['c_std=c89', 'b_vscrt=none']
)

inc_dir = include_directories('src')

sources = [
        'src/boot.c',
        'src/boot_utils.c',
        'src/rose_utils.c'
]

executable('BOOTX64', sources,
        include_directories: inc_dir,
        name_suffix: 'EFI'
)
