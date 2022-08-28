#project('app', 'cpp',
  #version : '0.1',
  #default_options : ['warning_level=3', 'cpp_std=c++14'])

#executable('app',
           #'oggex-bin.cpp',
           #'cli.c',
           #'main.cpp',
           #install : true)

#library('')

# Make static and shared library

# cli
cli = shared_library('cli',
        'cli.c',
        include_directories: incs,
        dependencies: [dep_m, dep_pcre])

dep_cli = declare_dependency(
                link_with: cli,
                include_directories: incs,
                dependencies: [dep_m, dep_pcre])

cli_static = static_library('cli_static',
        'cli.c',
        include_directories: incs,
        dependencies: [dep_m, dep_pcre])

# ogx
ogx = shared_library('ogx',
        'oggex-bin.cpp',
        include_directories: incs,
        dependencies: [dep_cli, deps, dep_oggex])

dep_ogx = declare_dependency(
                link_with: ogx,
                include_directories: incs)

ogx_static = static_library('ogx_static',
        'oggex-bin.cpp',
        include_directories: incs,
        dependencies: [dep_cli, deps, dep_oggex])

# oggex
executable('oggex-bin',
        'main.cpp',
        include_directories: incs,
        dependencies: [dep_cli, dep_oggex, dep_ogx, deps],
        install: true)

#subdir(qt)
