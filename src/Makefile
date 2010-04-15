WXCFLAGS=$(shell wx-config --cflags --libs --gl-libs)

# dan heeks uncomments the next line to make it work for him on his Inspiron 530
#WXCFLAGS=-I/usr/lib/wx/include/gtk2-unicode-release-2.8 -I/usr/include/wx-2.8

#check the environment variable HEEKSCADPATH.  If it's not set, print a message and assume ../..
ifeq ($(strip $(HEEKSCADPATH)),)
  heekspathmessage = message
  HEEKSCADPATH = ../..
else
  heekspathmessage = 
endif

CCFLAGS=-Wall -fPIC -g -I "./" $(WXCFLAGS) -I$(HEEKSCADPATH) -I/usr/include/GL -I/usr/include/python2.5 -I/usr/include/opencascade/ -D__WXGTK__ -DHEEKSCNC -DUNICODE -DWXUSINGDLL -lstdc++ -DWXUSINGDLL -lwx2.8 

#WX_LIB_LETTER=d
WX_LIB_LETTER=u

OBJECTS=ConsoleCanvas.o HeeksPython.o PythonInterface.o 

SHARED_LIBRARY=../HeeksPython.so

${SHARED_LIBRARY}: $(heekspathmessage) ${OBJECTS}
	gcc -shared -fPIC -Wl,-soname,HeeksPython.so -lpython2.5 -Xlinker -export-dynamic -o ${SHARED_LIBRARY} ${OBJECTS} -lstdc++ -lGLU ${WXCFLAGS} -pthread   -lwx_gtk2u_richtext-2.8 -lwx_gtk2u_aui-2.8 -lwx_gtk2u_xrc-2.8 -lwx_gtk2u_qa-2.8 -lwx_gtk2u_html-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_core-2.8 -lwx_baseu_xml-2.8 -lwx_baseu_net-2.8 -lwx_baseu-2.8  

#print a message if HEEKSCADPATH is not set
#use escape sequences for colors.  Z gets translated to \033
message:
	@echo Z[1mEnvironment variable HEEKSCADPATH not set. Assuming Z[32m../..Z[37mZ[0m | tr Z '\033'

ConsoleCanvas.o: ConsoleCanvas.cpp
	gcc -c $? ${CCFLAGS} -o $@
HeeksPython.o: HeeksPython.cpp
	gcc -c $? ${CCFLAGS} -o $@
PythonInterface.o: PythonInterface.cpp
	gcc -c $? ${CCFLAGS} -o $@


clean:
	-rm ${SHARED_LIBRARY} ${OBJECTS}
