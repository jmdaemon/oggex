# Config variables
program_name = 'oggex'
app_id = '.'.join(['io.github.com.jmdaemon', program_name])
app_id_ui = '/' / app_id.replace('.', '/') 
localedir = '/usr/share/locale/'
resourcedir = '../../../resources/gtk'

# Imports
i18n = import('i18n')
gnome = import('gnome')

# Dependencies
dep_gtk4 = dependency('gtk4')
deps_gtk4 = [dep_gtk4]

# Configure gettext translations
config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', program_name)
config_h.set_quoted('PROGRAM_NAME', program_name)
config_h.set_quoted('LOCALEDIR', localedir)

# Configure project paths
config_h.set_quoted('APP_ID', app_id)
config_h.set_quoted('RESOURCES_DIR', resourcedir)

# Configure resource file paths
config_h.set_quoted('UI_OGGEX_WINDOW', app_id_ui / resourcedir / 'oggex-window.ui')
config_h.set_quoted('UI_HELP_OVERLAY', app_id_ui / resourcedir / 'help-overlay.ui')
config_h.set_quoted('UI_FILE_CHOOSER_BUTTON', app_id_ui / resourcedir / 'filechooserbutton.ui')
config_h.set_quoted('UI_EMBED_WIDGET', app_id_ui / resourcedir / 'embedwidget.ui')
config_h.set_quoted('UI_EXTRACT_WIDGET', app_id_ui / resourcedir / 'extractwidget.ui')

configure_file(
  input: 'oggex-config.h.in',
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
