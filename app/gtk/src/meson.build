oggex_sources = [
  'filechooserbutton.c',
  'embedwidget.cpp',
  'extractwidget.cpp',
  'oggex-window.c',
  'oggex-application.c',
  'main.cpp',
]

oggex_sources += gnome.compile_resources('oggex-resources',
  'oggex.gresource.xml',
  c_name: 'oggex')

executable('oggex-gtk',
  oggex_sources,
  include_directories: incs,
  dependencies: [deps_gtk4, dep_cli, dep_oggex, dep_ogx, deps],
  install: true)
