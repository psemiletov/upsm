project('upsm', 'cpp',   default_options : ['cpp_std=c++11'])


#qt5_mod = import('qt5')
#qt5widgets = dependency('qt5', modules : 'Widgets')

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

