project('upsm', 'cpp', 
         default_options : ['cpp_std=c++11'],
         version : '3.0.0',
         license : 'GPLv3')


qt5_dep = dependency('qt5', modules : ['Core', 'Gui', 'Widgets']) 
qt5 = import('qt5') 


processed = qt5.preprocess(
  moc_headers : 'mainwindow.h',   
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

install_data(['desktop/upsm.desktop'],
             install_dir : 'share/applications')
             
