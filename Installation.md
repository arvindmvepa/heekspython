Must be installed under HeeksCAD/HeeksPython

I'll be working on some new projects that ease the dependency installation under windows.
Until then, here is what I did. You may/will need to edit the vcproj file to get it to build when you are done.

Here's a little outline of how i got it to build what i think is the
right way. I'll get this on the wiki soon.

Download python source to your hard disk. I got version 2.6.2?

Open the visual studio solution file in pythondir\PCBuild and let it
do its conversion.

Select configuration debug and hit build. This will run for a while,
and then will complain about ~7 build failures, don't worry about
these.
Select configuration release and hit build as well.

Download wxpython sources to your hard disk and unpack
This one is tricky because if you mess anything up, you'll have to
delete the entire tree, unpack and start over

rename the file in wxpythondir\include\wx\msw\setup0.h to setup.h

edit this file and change the following lines

wxUSE\_GRAPHICS\_CONTEXT         1
wxUSE\_GLCANVAS                 1
wxUSE\_POSTSCRIPT               1
wxUSE\_DATEPICKCTRL\_GENERIC     1

open up your visual studio command prompt and cd to

wxpythondir\build\msw

then type

nmake -f makefile.vc SHARED=1 MONOLITHIC=0 USE\_OPENGL=1 USE\_GDIPLUS=1
UNICODE=1 BUILD=debug

this will run for a while and hopefully not say anything bad

then cd to wxpythondir\contrib\build\stc

nmake -f makefile.vc SHARED=1 MONOLITHIC=0 USE\_OPENGL=1 USE\_GDIPLUS=1
UNICODE=1 BUILD=debug


then cd to wxpythondir\contrib\build\gizmos and issue a

nmake -f makefile.vc SHARED=1 MONOLITHIC=0 USE\_OPENGL=1 USE\_GDIPLUS=1
UNICODE=1 BUILD=debug



then cd to
wxdir\wxpython

and type

pythondir\PCBuild\python\_d.exe setup.py build\_ext --inplace
MONOLITHIC=0 --debug


then all should be well. the original visual studio project at least
describes what relative directories you need to use for linking and
including. The dll's must get copied to the heekscad directory.
Heekscad then needs to be changed to link against the wxwidgets libs
produced through this process. It is important to note that wxpython
source includes the wxwidgets source and this process builds them
both. You can't use different build of wxwidgets in different parts of
the program.

Linux builds should be easy once somebody makes a makefile.

You need to have installed under ubuntu:

python
wxwidgets
wxpython-tools

Somehow build and link against those and you should be a-ok.

The dll-name must be HeeksPython\_d.pyd for debug builds and HeeksPython.pyd for release builds(of HeeksCAD). This pyd file must be located in the same directory as the HeeksCAD executable. The plugin file chooser tries to filter files by extension, so you usually need to type in the plugin lib name to get it to work.