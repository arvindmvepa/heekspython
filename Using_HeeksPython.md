First, you must import HeeksPython into itself by typing something like

import HeeksPython as cad

into the terminal

then you can create lines and such by typing

cad.line(x1,y1,x2,y2)

if you want to get a handle to the object you must use

line = cad.getlastobj()

this is a little weird but is necessary because otherwise python will print tons of garbage to the console if you don't use the returned handles in a loop

cad.group() is one of my favorites. after getting the handle you can use

cad.add(group,line)

you can also make sketches with

cad.sketch()

there are functions for arc, cuboids, circles, line3d


cad.cut only works on a group and a solid

you must cad.getlastobj() after doing a cut or a fuse as the old objects have been deleted and there handles are no longer valid

**Importing scripts**

Scripts don't have to be entered in the python interpreter window by hand. They can be imported. You can create a python script and save it, then do something like:

import sys

sys.path.insert(0,'/home/dan/HeeksCAD/heekspython/examples/buttons')

import macro

do\_it = macro.MyFrame1(None, -1, "")

do\_it.Show()

In this example, 'macro' is a wxpython script that brings up a gui

**Examples**

There are a few example scripts in the 'examples' directory

'examples.py' runs through a lot of the geometric types that are available for heekspython.

'polar\_array.py' is a small example of how a wxgui can be applied to heekspython. Look at polar\_array\_readme.txt to see how to use it.


