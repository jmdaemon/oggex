# cli
cli = shared_library('cli',
        'cli.c',
        include_directories: incs,
        dependencies: [dep_m, dep_pcre])

cli_static = static_library('cli_static',
        'cli.c',
        include_directories: incs,
        dependencies: [dep_m, dep_pcre])

dep_cli = declare_dependency(
                link_with: cli,
                include_directories: incs,
                dependencies: [dep_m, dep_pcre])

# ogx
ogx = shared_library('ogx',
        'oggex-bin.cpp',
        include_directories: incs,
        dependencies: [dep_cli, deps, dep_oggex])

ogx_static = static_library('ogx_static',
        'oggex-bin.cpp',
        include_directories: incs,
        dependencies: [dep_cli, deps, dep_oggex])

dep_ogx = declare_dependency(
                link_with: ogx,
                include_directories: incs)

# oggex-bin
executable('oggex-bin',
        'main.cpp',
        include_directories: incs,
        dependencies: [dep_cli, dep_oggex, dep_ogx, deps],
        install: true)

#subdir(qt)
subdir('gtk')
