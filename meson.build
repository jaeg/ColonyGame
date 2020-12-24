project('game', 'cpp', default_options : ['cpp_std=c++14'])
subdir('src')
sdl2_lib = meson.get_compiler('cpp').find_library('SDL2')
sdldep = declare_dependency(dependencies : [sdl2_lib])

sdl2image_lib = meson.get_compiler('cpp').find_library('SDL2_image')
sdlimagedep = declare_dependency(dependencies : [sdl2image_lib])
executable('game', sources,  dependencies : [sdldep, sdlimagedep])