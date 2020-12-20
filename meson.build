project (
  'oggex', 
  'cpp', 
  version : '1.0.0', 
  default_options : ['cpp_std=c++17'] )

gtkmmdep = dependency('gtkmm-3.0')

encoder = executable('encoder', 'src/encoder/main/ogg-encoder.cpp', dependencies : gtkmmdep)

doctest = subproject('doctest')
libogg = subproject('libogg')
test('Encode OGG File', encoder)
