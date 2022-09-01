project('oggex', ['c', 'cpp'],
version: '2.2.0',
subproject_dir: 'meson-subprojects',
license: 'MIT')

# Include project version
add_project_arguments([
  '-I' + meson.project_build_root(),
], language: ['c', 'cpp'])

# Include project headers
inc = include_directories('include')
inc_ver = include_directories('.')
incs = [inc, inc_ver]

# Single source project version
project_version = meson.project_version().split('.')

conf_data = configuration_data()
conf_data.set('CMAKE_PROJECT_VERSION_MAJOR', project_version[0])
conf_data.set('CMAKE_PROJECT_VERSION_MINOR', project_version[1])
conf_data.set('CMAKE_PROJECT_VERSION_PATCH', project_version[2])

configure_file(input : 'include/Version.h.in',
                        output : 'Version.h',
                        configuration : conf_data)

# Dependencies
cc     = meson.get_compiler('c')
dep_m = cc.find_library('m', required : false)
dep_pcre = dependency('libpcre')

# Subprojects
proj_utility = subproject('utility')
dep_utility = proj_utility.get_variable('dep_utility')

proj_jolly = subproject('jolly')
dep_jolly = proj_jolly.get_variable('dep_jolly')

proj_spdlog = subproject('spdlog')
spdlog_dep = proj_spdlog.get_variable('spdlog_dep')

deps = [ dep_m, dep_pcre, dep_utility, dep_jolly, spdlog_dep ]

subdir('src')
subdir('app')
#subdir('test')
