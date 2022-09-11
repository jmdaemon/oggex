qt6 = import('qt6')
dep_qt6 = dependency('qt6', modules: ['Widgets'])

qt_ui  = '../../resources/qt'
qt_hdr = '../../include/qt'
inc_qt = include_directories('../../include/qt')
inc_config = include_directories('.')

incs += inc_qt
incs += inc_config

# datamodel 
#datamodel_ui = qt6.compile_ui(sources : qt_ui / 'datamodel.ui')
datamodel_moc = qt6.compile_moc(
        headers : qt_hdr / 'datamodel.h',
        include_directories: [incs],
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

filechooser_ui = qt6.compile_ui(sources : qt_ui / 'filechooser.ui')
filechooser_moc = qt6.compile_moc(
        headers : qt_hdr / 'filechooser.h',
        #include_directories: [incs, datamodel_moc],
        include_directories: [incs],
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

embedwidget_ui = qt6.compile_ui(sources : qt_ui / 'embedwidget.ui')
embedwidget_moc = qt6.compile_moc(
        headers : qt_hdr / 'embedwidget.h',
        #include_directories: [incs, filechooser_moc],
        include_directories: [incs],
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

extractwidget_ui = qt6.compile_ui(sources : qt_ui / 'extractwidget.ui')
extractwidget_moc = qt6.compile_moc(
        headers : qt_hdr / 'extractwidget.h',
        include_directories: [incs],
        #dependencies: [dep_qt6, dep_oggex, dep_ogx, deps, datamodel_moc, filechooser_moc])
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

homewidget_ui = qt6.compile_ui(sources : qt_ui / 'homewidget.ui')
homewidget_moc = qt6.compile_moc(
        headers : qt_hdr / 'homewidget.h',
        include_directories: [incs],
        #dependencies: [dep_qt6, dep_oggex, dep_ogx, deps, datamodel_moc, filechooser_moc, embedwidget_moc, extractwidget_moc])
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

mainwindow_ui = qt6.compile_ui(sources : qt_ui / 'mainwindow.ui')
mainwindow_moc = qt6.compile_moc(
        headers : qt_hdr / 'mainwindow.h',
        include_directories: [incs],
        #dependencies: [dep_qt6, dep_oggex, dep_ogx, deps, datamodel_moc, filechooser_moc, embedwidget_moc, extractwidget_moc])
        dependencies: [dep_qt6, dep_oggex, dep_ogx, deps])

moc_files = [datamodel_moc, filechooser_moc, embedwidget_moc, extractwidget_moc, homewidget_moc, mainwindow_moc]
qt6_srcs = ['datamodel.cpp', 'filechooser.cpp', 'embedwidget.cpp', 'extractwidget.cpp', 'homewidget.cpp', 'mainwindow.cpp']
#ui_files = [datamodel_ui, filechooser_ui, embedwidget_ui, extractwidget_ui, homewidget_ui, mainwindow_ui]
ui_files = [filechooser_ui, embedwidget_ui, extractwidget_ui, homewidget_ui, mainwindow_ui]

executable('oggex-qt',
        [moc_files, qt6_srcs, 'oggex-qt.cpp', ui_files],
        include_directories: [incs],
        #dependencies: [dep_qt6, dep_oggex, dep_ogx, deps, datamodel_moc, filechooser_moc, embedwidget_moc, extractwidget_moc])
        dependencies: [dep_qt6, dep_cli, dep_oggex, dep_ogx, deps],
        install: true)

#datamodel_moc= qt6.compile_moc('myclass.h',
                            #extra_arguments: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
                            #include_directories: inc,
                            #dependencies: qt6_dep)
#translations = qt6.compile_translations(ts_files : 'myTranslation_fr.ts', build_by_default : true)
#executable('myprog', 'main.cpp', 'myclass.cpp', moc_files,
           #include_directories: inc,
           #dependencies : qt6_dep)
