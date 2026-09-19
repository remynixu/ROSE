project('ROSE', 'c',
        version: '0.1',
        default_options: ['c_std=c89', 'b_vscrt=none']
)

inc_dir = include_directories('include')

sources = [
        'src/boot.c'
]

executable('BOOTX64', sources,
        include_directories: inc_dir,
        name_suffix: 'EFI'
)
