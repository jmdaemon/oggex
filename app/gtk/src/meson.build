oggex_sources = [
  'main.c',
  'oggex-window.c',
  'oggex-application.c',
]

oggex_sources += gnome.compile_resources('oggex-resources',
  'oggex.gresource.xml',
  c_name: 'oggex')

executable('oggex',
  oggex_sources,
  include_directories: incs,
  dependencies: deps_gtk4,
  install: true)
