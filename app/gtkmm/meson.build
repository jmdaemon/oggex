# TODO: Make CMake gtk functions for gresources
# TODO: Merge redundant oggex-config.h, oggex_gtk_defs.h with oggex_config.h 
# TODO: Replace all string functions with compile time constant strings
#   - Doing it this way allows us to 
#   - Use configure_file on CMake
#   - Use configuration_data on Meson
# TODO: Generate configure
# TODO: Run through tutorials and design initial main window with embedded widget

# Imports
i18n = import('i18n')
gnome = import('gnome')

# Dependencies
dep_gtk4 = dependency('gtk4')
deps_gtk4 = [dep_gtk4]

# Configure gettext translations
config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', 'oggex')
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
configure_file(
  output: 'oggex-config.h',
  configuration: config_h)

# Include directories
inc = include_directories('../../include')
inc_gtk = include_directories('../../include/gtk')
inc_config = include_directories('.')
incs = [inc, inc_config, inc_gtk]

subdir('data')
subdir('src')
subdir('po')

gnome.post_install(
  glib_compile_schemas: true,
  gtk_update_icon_cache: true,
  update_desktop_database: true,
)
