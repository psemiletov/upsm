project('upsm', 'cpp', 
         default_options : ['cpp_std=c++11'],
         version : '2.1.1',
         license : 'GPLv3')


qt5_dep = dependency('qt5', modules : ['Core', 'Gui', 'Widgets']) 
qt5 = import('qt5') 


processed = qt5.preprocess(
  moc_headers : 'mainwindow.h',   # Only headers that need moc should be put here
#  moc_sources : 'mainwindow.cpp', # must have #include"moc_helperFile.cpp"
  qresources  : 'upsm.qrc',
)

q5exe = executable('upsm',
  sources     : ['main.cpp', 'mainwindow.cpp',
                 processed], install : true,
  dependencies: qt5_dep,
  cpp_args : '-std=c++11'
  )

install_data(['icons/upsm.png'],
             install_dir : 'share/icons/hicolor/128x128/apps')

install_data(['icons/upsm.svg'],
             install_dir : 'share/icons/hicolor/scalable/apps')

install_data(['icons/upsm.desktop'],
             install_dir : 'share/applications')
             
