oggex = shared_library('oggex',
        'oggex.cpp',
        include_directories: inc,
        dependencies: [deps])

oggex_static = static_library('oggex_static',
        'oggex.cpp',
        include_directories: inc,
        dependencies: [deps])

dep_oggex = declare_dependency(
        link_with : oggex,
        include_directories : inc,
        dependencies: [deps])
