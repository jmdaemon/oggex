oggex = shared_library('oggex',
        'oggex.cpp',
        include_directories: inc,
        #dependencies: [dep_cli, deps])
        dependencies: [deps])
        #dependencies: [deps],
        #link_with: 'cli')
        #dependencies: 'cli')

oggex_static = static_library('oggex_static',
        'oggex.cpp',
        include_directories: inc,
        #dependencies: [dep_cli, deps])
        dependencies: [deps])
        #dependencies: 'cli')

dep_oggex = declare_dependency(
        link_with : oggex,
        include_directories : inc,
        dependencies: [deps])
        #dependencies: [dep_cli, deps])
        #dependencies: [deps],
        #link_with: 'cli')
