# Copy needed test files to build directory
copy = find_program('copy.py')

run_command(
    copy,
    '../LICENSE',
    '../LICENSE')

run_command(
    copy,
    '../resources/samples/embed' / '835127a09fc542aeb3bfa99c9d91972d.png.png',
    '../samples/embed' / '835127a09fc542aeb3bfa99c9d91972d.png.png')

run_command(
    copy,
    '../resources/samples/embed' / 'audio02.ogg',
    '../samples/embed' / 'audio02.ogg')

run_command(
    copy,
    '../resources/samples/extract' / '835127a09fc542aeb3bfa99c9d91972d.png',
    '../samples/extract' / '835127a09fc542aeb3bfa99c9d91972d.png')

# Unit Tests
test_oggex = executable(
    'test_oggex',
    'test_oggex.cpp',
    include_directories: [incs],
    dependencies: [dep_oggex, dep_doctest])

# Integration Tests
test_oggex_int = executable(
    'test_oggex_int',
    'test_oggex_int.cpp',
    include_directories: [incs],
    dependencies: [dep_oggex, dep_doctest])

test('Oggex Unit Tests', test_oggex)
test('Oggex Integration Tests', test_oggex_int)
