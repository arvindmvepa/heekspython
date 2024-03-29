// HeeksPython.cpp
#include "stdafx.h"

#ifdef WIN32
#include "windows.h"
#endif

#include "PythonInterface.h"
#include "Interface.h"
#include "interface/HeeksCADInterface.h"
#include "interface/HeeksObj.h"
#include "interface/ToolImage.h"
#include "PythonConfig.h"

#include <set>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif


extern CHeeksCADInterface *heeksCAD;
extern CHeeksPythonApp theApp;
extern wxWindow* m_window;


class Property;

void OnStartUp(CHeeksCADInterface* h, const wxString& dll_path)
{
	theApp.OnStartUp(h, dll_path);
}

void OnNewOrOpen(int open, int res)
{
	theApp.OnNewOrOpen(open != 0, res);
}

void GetOptions(void(*callbackfunc)(Property*))
{
	std::list<Property*> list;
	theApp.GetOptions(&list);
	for(std::list<Property*>::iterator It = list.begin(); It != list.end(); It++){
		Property* p = *It;
		(*callbackfunc)(p);
	}
}

void OnFrameDelete()
{
}

HeeksObj* lastobj;

static PyObject* NewPoint(PyObject* self, PyObject* args)
{
	const double p[3]={0,0,0};
	if (!PyArg_ParseTuple(args, "ddd", &p[0],&p[1],&p[2])) return NULL;

	lastobj = heeksCAD->NewPoint(p);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}




static PyObject* NewLine(PyObject* self, PyObject* args)
{
	double s[3]={0,0,0};
	double e[3]={0,0,0};
	if (!PyArg_ParseTuple(args, "dddd", &s[0],&s[1],&e[0],&e[1])) return NULL;

	lastobj = heeksCAD->NewLine(s,e);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewLine3d(PyObject* self, PyObject* args)
{
	double s[3]={0,0,0};
	double e[3]={0,0,0};
	if (!PyArg_ParseTuple(args, "dddddd", &s[0],&s[1],&s[2],&e[0],&e[1],&e[2])) return NULL;

	lastobj = heeksCAD->NewLine(s,e);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewCircle(PyObject* self, PyObject* args)
{
	double c[3]={0,0,0};
	double r=0;
	if (!PyArg_ParseTuple(args, "ddd", &c[0],&c[1],&r)) return NULL;

	lastobj = heeksCAD->NewCircle(c,r);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewArc(PyObject* self, PyObject* args)
{
	double c[3];
	double u[3];
	double r,s,e;

    if (!PyArg_ParseTuple( args, "ddddddddd", &c[0],&c[1],&c[2],&r,&s,&e,&u[0],&u[1],&u[2])) return NULL;

	lastobj = heeksCAD->NewArc(c,u,r,s,e);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);


	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

//added by DF- arc2 function using start point, end point,center point, uv
//NewArc(const double* s, const double* e, const double* c, const double* up)
static PyObject* NewArc2(PyObject* self, PyObject* args)
{
	double c[3];
	double u[3];
	double s[3];
    double e[3];

    if (!PyArg_ParseTuple( args, "dddddddddddd",&s[0],&s[1],&s[2],&e[0],&e[1],&e[2],&c[0],&c[1],&c[2],&u[0],&u[1],&u[2])) return NULL;

	lastobj = heeksCAD->NewArc(s,e,c,u);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}



static PyObject* NewCuboid(PyObject* self, PyObject* args)
{
	double c[3]={0,0,0};
	double x=0;
	double y=0;
	double z=0;
	if (!PyArg_ParseTuple(args, "dddddd", &c[0],&c[1],&c[2],&x,&y,&z)) return NULL;
	lastobj = heeksCAD->NewCuboid(c,x,y,z);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* NewCylinder(PyObject* self, PyObject* args)
{
	double c[3]={0,0,0};
	double r=0;
	double h=0;
	if (!PyArg_ParseTuple(args, "ddddd", &c[0],&c[1],&c[2],&r,&h)) return NULL;
	lastobj = heeksCAD->NewCylinder(c,r,h);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewCylinderEx(PyObject* self, PyObject* args)
{
	double pos[3]={0,0,0};
	double dir[3]={0,0,0};
	double r=0;
	double h=0;
	if (!PyArg_ParseTuple(args, "dddddddd", &pos[0],&pos[1],&pos[2],&dir[0],&dir[1],&dir[2],&r,&h)) return NULL;
	lastobj = heeksCAD->NewCylinderEx(pos,dir,r,h);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewCone(PyObject* self, PyObject* args)
{
	double c[3]={0,0,0};
	double r1=0;
	double r2=0;
	double h=0;
	if (!PyArg_ParseTuple(args, "dddddd", &c[0],&c[1],&c[2],&r1,&r2,&h)) return NULL;
	lastobj = heeksCAD->NewCone(c,r1,r2,h);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewSphere(PyObject* self, PyObject* args)
{
	double c[3]={0,0,0};
	double r=0;
	if (!PyArg_ParseTuple(args, "dddd", &c[0],&c[1],&c[2],&r)) return NULL;
	lastobj = heeksCAD->NewSphere(c,r);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	
	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}






static PyObject* NewGroup(PyObject* self, PyObject* args)
{
	lastobj = heeksCAD->NewGroup();
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Reorder(PyObject* self, PyObject* args)
{
	int oid;
	HeeksObj* obj;

    if (!PyArg_ParseTuple( args, "i", &oid)) return NULL;

    // Convert the PyCObject to a void pointer:
	obj = (HeeksObj*)heeksCAD->GetIDObject(oid>>16,oid&0xFFFF);
	heeksCAD->ReOrderSketch(obj,SketchOrderTypeCloseCW);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* ViewExtents(PyObject* self, PyObject* args)
{

	heeksCAD->ViewExtents(false);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* XYZview(PyObject* self, PyObject* args)
{

	heeksCAD->XYZView(true);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* NewSketch(PyObject* self, PyObject* args)
{
	lastobj = heeksCAD->NewSketch();
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* GetLastObj(PyObject* self, PyObject* args)
{
	return PyLong_FromLong(lastobj->m_id | lastobj->GetIDGroupType() << 16);
}

static PyObject* Rotate(PyObject* self, PyObject* args)
{
	HeeksObj *obj;
	int pyobj = 0;
	double p[3];
	double u[3];
	double r;

    if (!PyArg_ParseTuple( args, "iddddddd", &pyobj,&p[0],&p[1],&p[2],&u[0],&u[1],&u[2],&r)) return NULL;

    // Convert the PyCObject to a void pointer:
	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	heeksCAD->RotateObject(obj,p,u,r);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* Extrude(PyObject* self, PyObject* args)
{
	HeeksObj *obj;
	int pyobj = 0;
	double h;

    if (!PyArg_ParseTuple( args, "id", &pyobj,&h)) return NULL;

    // Convert the PyCObject to a void pointer:

	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	lastobj = heeksCAD->ExtrudeSketch(obj,h,true);



	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* Revolve(PyObject* self, PyObject* args)
{
	HeeksObj *obj;
	int pyobj = 0;
	double a;

    if (!PyArg_ParseTuple( args, "id", &pyobj,&a)) return NULL;

    // Convert the PyCObject to a void pointer:
	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	lastobj = heeksCAD->RevolveSketch(obj,a,true);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}



static PyObject* Translate(PyObject* self, PyObject* args)
{
	HeeksObj *obj;
	int pyobj = 0;
	double p[3];

    if (!PyArg_ParseTuple( args, "iddd", &pyobj,&p[0],&p[1],&p[2])) return NULL;

    // Convert the PyCObject to a void pointer:
    obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	heeksCAD->TranslateObject(obj,p);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Scale(PyObject* self, PyObject* args)
{
	HeeksObj *obj;
	int pyobj = 0;
	double p[3];
	double scale = 1.0;

    if (!PyArg_ParseTuple( args, "idddd", &pyobj,&p[0],&p[1],&p[2],&scale)) return NULL;

    // Convert the PyCObject to a void pointer:
    	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	heeksCAD->ScaleObject(obj,p,scale);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Add(PyObject* self, PyObject* args)
{
	HeeksObj *group, *obj;
	int pygroup,pyobj;

    if (!PyArg_ParseTuple( args, "ii", &pygroup, &pyobj)) return NULL;

    // Convert the PyCObject to a void pointer:
    obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	group = (HeeksObj*)heeksCAD->GetIDObject(pygroup>>16,pygroup&0xFFFF);
	obj->m_owner->Remove(obj);
	group->Add(obj,NULL);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Fuse(PyObject* self, PyObject* args)
{
	int pyobj1,pyobj2;

    if (!PyArg_ParseTuple( args, "ii", &pyobj1, &pyobj2)) return NULL;

    // Convert the PyCObject to a void pointer:
	std::list<HeeksObj*> list;
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj1>>16,pyobj1&0xFFFF));
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj2>>16,pyobj2&0xFFFF));
	lastobj = heeksCAD->Fuse(list);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* Common(PyObject* self, PyObject* args)
{
	int pyobj1,pyobj2;

    if (!PyArg_ParseTuple( args, "ii", &pyobj1, &pyobj2)) return NULL;

    // Convert the PyCObject to a void pointer:
	std::list<HeeksObj*> list;
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj1>>16,pyobj1&0xFFFF));
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj2>>16,pyobj2&0xFFFF));
	lastobj = heeksCAD->Common(list);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}



static PyObject* LineArc2Wire(PyObject* self, PyObject* args)
{
	int pyobj;

    if (!PyArg_ParseTuple( args, "i", &pyobj)) return NULL;

    // Convert the PyCObject to a void pointer:
	std::list<HeeksObj*> list;
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF));
	
	lastobj = heeksCAD->LineArcsToWire(list);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* Cut(PyObject* self, PyObject* args)
{
	int pyobj1,pyobj2;

    if (!PyArg_ParseTuple( args, "ii", &pyobj1, &pyobj2)) return NULL;

    // Convert the PyCObject to a void pointer:
	std::list<HeeksObj*> list;
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj1>>16,pyobj1&0xFFFF));
	list.push_back((HeeksObj*)heeksCAD->GetIDObject(pyobj2>>16,pyobj2&0xFFFF));	
	lastobj = heeksCAD->Cut(list);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);	
	//heeksCAD->Cut(list);		

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* NewCreateUndoPoint(PyObject* self, PyObject* args)
{
	
// todo if ever	heeksCAD->CreateUndoPoint();
	
	Py_INCREF(Py_None);
	return Py_None;
	

}

static PyObject* NewChanged(PyObject* self, PyObject* args)
{
	
	
	//todo if ever heeksCAD->Changed();
	
	Py_INCREF(Py_None);
	return Py_None;
	

}


static PyObject* Pipe(PyObject* self, PyObject* args)
{
	int pyobj1,pyobj2;
	HeeksObj *wire,*profile;

    if (!PyArg_ParseTuple( args, "ii", &pyobj1, &pyobj2)) return NULL;

    // Convert the PyCObject to a void pointer:
	wire = (HeeksObj*)heeksCAD->GetIDObject(pyobj1>>16,pyobj1&0xFFFF);
	profile = (HeeksObj*)heeksCAD->GetIDObject(pyobj2>>16,pyobj2&0xFFFF);
	lastobj = heeksCAD->MakePipe(wire,profile);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* SetColor(PyObject* self, PyObject* args)
{
	int r,g,b;

    if (!PyArg_ParseTuple( args, "iii", &r,&b,&g)) return NULL;

	heeksCAD->SetColor(r,b,g);

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Fillet2d(PyObject* self, PyObject* args)
{ //the lines definitely need to be trimmed first
	HeeksObj *obj;
	int pyobj = 0;
	double p[3];
	double r;

    if (!PyArg_ParseTuple( args, "idddd", &pyobj,&p[0], &p[1], &p[2], &r)) return NULL;
	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	heeksCAD->FilletSketchAtPoint(obj,p,r);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;

}

static PyObject* NewCoordinateSystem(PyObject* self, PyObject* args)
{
	double o[3]={0,0,0};
	double x[3]={1, 0, 0};
	double y[3]={0, 1, 0};
	if (!PyArg_ParseTuple(args, "ddddddddd",  &o[0],&o[1],&o[2],&x[0],&x[1],&x[2],&y[0],&y[1],&y[2])) return NULL;
	lastobj = heeksCAD->NewCoordinateSystem(o,x,y);
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}


static PyObject* PickPoint(PyObject* self, PyObject* args)
{	//get point in space, so to speak- not necessarily on an actual object
	//will return a point that is clicked in the graphicscanvas
	//the little spinner wheel will rotate until this is completed
	double pt1[3]={0,0,0};
	double px = 0;double py=0;double pz=0;
	heeksCAD->PickPosition(_("Pick something, please!"),pt1);
	
	px= pt1[0];py= pt1[1]; pz= pt1[2];
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	PyObject *pTuple = PyTuple_New(3);
	{
		PyObject *pValue = PyFloat_FromDouble(px);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 0, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(py);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 1, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(pz);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 2, pValue);
	}

	Py_INCREF(pTuple);
	return pTuple;
}



static PyObject* GetClickedPos(PyObject* self, PyObject* args)
{
	//will return last double clicked point in graphicscanvas
	//need to double click on a point object
	double pt1[3]={0,0,0};
	double px = 0;double py=0;double pz=0;
	heeksCAD->GetLastClickPosition(pt1);
	
	px= pt1[0];py= pt1[1]; pz= pt1[2];
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	PyObject *pTuple = PyTuple_New(3);
	{
		PyObject *pValue = PyFloat_FromDouble(px);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 0, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(py);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 1, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(pz);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 2, pValue);
	}

	Py_INCREF(pTuple);
	return pTuple;
}

static PyObject* GetPoint3d(PyObject* self, PyObject* args)
{
	//will return coordinates x,y,z of actual point object in graphicscanvas
	//need to pick point before calling function
	HeeksObj *obj;
	double pt1[3]={0,0,0};
	double px = 0;double py=0;double pz=0;
	obj= heeksCAD->GetFirstMarkedObject();
	if (!obj) return NULL;
	heeksCAD->VertexGetPoint(obj,pt1);
	px= pt1[0];py= pt1[1]; pz= pt1[2];
	heeksCAD->GetMainObject()->Add(lastobj,NULL);
	PyObject *pTuple = PyTuple_New(3);
	{
		PyObject *pValue = PyFloat_FromDouble(px);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 0, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(py);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 1, pValue);
	}
	{
		PyObject *pValue = PyFloat_FromDouble(pz);
		if (!pValue){
			Py_DECREF(pTuple);return NULL;
		}
		PyTuple_SetItem(pTuple, 2, pValue);
	}

	Py_INCREF(pTuple);
	return pTuple;
}


inline wxString _U(const char String[] = "")
{
    return wxString(String, wxConvUTF8);
}


static PyObject* NewText(PyObject* self, PyObject* args)
{	

	const char *text; //the text that gets input in python

	if (!PyArg_ParseTuple(args, "s",  &text)) return NULL; 
	
	heeksCAD->AddText(_U(text));

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;

}

static PyObject* AddMenu(PyObject* self, PyObject* args)
{	
	const char  *menu_name;
	if (!PyArg_ParseTuple(args, "s",  &menu_name)) return NULL;	

	wxFrame* frame = heeksCAD->GetMainFrame();
	wxMenu *newMenu = new wxMenu;
	frame->GetMenuBar()->Append(newMenu,  _U(menu_name));

	return PyLong_FromSize_t((size_t)newMenu);//size_t instead of unsigned int for 64 bit gcc
}

static PyObject* GetFrameHwnd(PyObject* self, PyObject* args)
{	
	wxFrame* frame = heeksCAD->GetMainFrame();
	return PyLong_FromSize_t((size_t)(frame->GetHandle()));//size_t instead of unsigned int for 64 bit gcc
}

static PyObject* GetFrameId(PyObject* self, PyObject* args)
{	
	wxFrame* frame = heeksCAD->GetMainFrame();
	return PyLong_FromLong(frame->GetId());
}

std::map<int, PyObject*> menu_item_map;

void OnMenuItem(wxCommandEvent &event)
{
	std::map<int, PyObject*>::iterator FindIt = menu_item_map.find(event.GetId());
	if(FindIt != menu_item_map.end())
	{
		// Execute the python code
		PyObject* python_callback = FindIt->second;

		// to do replace this commented line
		//PyEval_RestoreThread(theApp.m_console->m_mainTState);

		PyObject* result = PyEval_CallFunction(python_callback, "()");

		// Release the python objects we still have
		if (result)Py_DECREF(result);
		else PyErr_Print();

		PyEval_SaveThread();
	}
}

static PyObject* AddMenuItem(PyObject* self, PyObject* args)
{	
	long int_menu;
	const char *title;
	PyObject *python_callback;
	const char *bitmap_path;
	if (!PyArg_ParseTuple(args, "lsOs",  &int_menu, &title, &python_callback, &bitmap_path)) return NULL;	

	wxMenu *menu = (wxMenu*)int_menu;

	int id = heeksCAD->AddMenuItem(menu, wxString(_U(title)), ToolImage(_U(bitmap_path), true), OnMenuItem, NULL);

	menu_item_map.insert(std::make_pair(id, python_callback));

	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static std::list<wxWindow*> new_windows;

std::map<int, wxWindow*> window_map;

void OnWindow( wxCommandEvent& event )
{
	std::map<int, wxWindow*>::iterator FindIt = window_map.find(event.GetId());
	if(FindIt != window_map.end())
	{
		wxWindow* window = FindIt->second;
		wxAuiManager* aui_manager = heeksCAD->GetAuiManager();
		wxAuiPaneInfo& pane_info = aui_manager->GetPane(window);
		if(pane_info.IsOk()){
			pane_info.Show(event.IsChecked());
			aui_manager->Update();
		}
	}
}

void OnUpdateWindow( wxUpdateUIEvent& event )
{
	std::map<int, wxWindow*>::iterator FindIt = window_map.find(event.GetId());
	if(FindIt != window_map.end())
	{
		wxWindow* window = FindIt->second;
		wxAuiManager* aui_manager = heeksCAD->GetAuiManager();
		event.Check(aui_manager->GetPane(window).IsShown());
	}
}

static PyObject* AddWindow(PyObject* self, PyObject* args)
{	
	long int_window;
	if (!PyArg_ParseTuple(args, "l",  &int_window)) return NULL;	

	wxFrame* frame = heeksCAD->GetMainFrame();
	wxAuiManager* aui_manager = heeksCAD->GetAuiManager();

#ifdef WIN32
	wxWindow * new_window = new wxWindow();
	new_window->SetHWND((WXHWND)int_window);
	new_window->AdoptAttributesFromHWND();
	new_window->Reparent(frame);
#else
	wxWindow * new_window = wxWindow::FindWindowById(int_window);
	new_window->Reparent(frame);
#endif

	wxString label = new_window->GetLabel();

	new_windows.push_back(new_window);

	aui_manager->AddPane(new_window, wxAuiPaneInfo().Name(label).Caption(label).Bottom().BestSize(wxSize(600, 200)));

	bool window_visible;
	wxString config_name = label + wxString(_T("Visible"));
	PythonConfig config;

	config.Read(config_name, &window_visible);

	aui_manager->GetPane(new_window).Show(window_visible);

	wxMenu* view_menu = heeksCAD->GetWindowMenu();
	int id = heeksCAD->AddMenuItem(view_menu, label, wxBitmap(), OnWindow, OnUpdateWindow,0,true);
	heeksCAD->RegisterHideableWindow(new_window);
	window_map.insert(std::make_pair(id, new_window));

	return PyLong_FromLong(new_window->GetId());
}

static PyObject* DXFImport(PyObject* self, PyObject* args)
{	

	const char  *filepath;
	if (!PyArg_ParseTuple(args, "s",  &filepath)) return NULL;	

	heeksCAD->OpendxfFile(_U(filepath));	
	
		
	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
}

static PyObject* Redraw(PyObject* self, PyObject* args)
{
	
	
	heeksCAD->Repaint();
	PyObject *pValue = Py_None;
	Py_INCREF(pValue);
	return pValue;
	

}


static PyObject* GetSketch(PyObject* self, PyObject* args)
{
	//Allows the user to pick a single sketch 
	// it returns the sketch id, or 0 if none was picked
	
	PyObject *resultobj = 0;

	int result;

	result = heeksCAD->PickObjects(_("Select a Sketch"), MARKING_FILTER_SKETCH,true);

	int sketch_id = 0;

	for(HeeksObj* object = heeksCAD->GetFirstMarkedObject(); object; object = heeksCAD->GetNextMarkedObject())
	{
		if(object->GetType() == SketchType){
			sketch_id = object->GetID();
			break;
		}
	}

	resultobj = PyLong_FromLong(sketch_id);
	
	PyObject *pValue = resultobj;
	Py_INCREF(pValue);
	return pValue;

}

static PyObject* GetSketches(PyObject* self, PyObject* args)
{
	// Allows the user to pick multiple sketches
	// returns a python list of sketch ids
	int result = heeksCAD->PickObjects(_("Select Sketches"), MARKING_FILTER_SKETCH);

	PyObject* pList = PyList_New(0);
	for(HeeksObj* object = heeksCAD->GetFirstMarkedObject(); object; object = heeksCAD->GetNextMarkedObject())
	{
		if(object->GetType() == SketchType){
			PyList_Append(pList, PyLong_FromLong(object->GetID()));
		}
	}

	return pList;
}

static PyObject* GetSelectedSketches(PyObject* self, PyObject* args)
{
	// returns a python list of sketch ids
	PyObject* pList = PyList_New(0);
	for(HeeksObj* object = heeksCAD->GetFirstMarkedObject(); object; object = heeksCAD->GetNextMarkedObject())
	{
		if(object->GetType() == SketchType){
			PyList_Append(pList, PyLong_FromLong(object->GetID()));
		}
	}

	return pList;
}

static PyObject *callback_new_or_open = NULL;

void OnBeforeNewOrOpen(int open, int res) {
	if(callback_new_or_open)
	{
		// to do, replace this line
		//PyEval_RestoreThread(theApp.m_console->m_mainTState);
		PyObject* result = PyEval_CallFunction(callback_new_or_open, "ii", open, res);
		PyEval_SaveThread();
	}
}

static PyObject* RegisterCallbacks(PyObject* self, PyObject* args)
{
	PyObject *temp;
	if (!PyArg_ParseTuple(args, "O",  &temp)) return NULL;

	if (!PyCallable_Check(temp)) {
		PyErr_SetString(PyExc_TypeError, "parameter must be callable");
		return NULL;
	}
	Py_XINCREF(temp);         /* Add a reference to new callback */
	Py_XDECREF(callback_new_or_open);  /* Dispose of previous callback */
	callback_new_or_open = temp;       /* Remember new callback */

	static bool callbacks_registered = false;

	if(!callbacks_registered)
	{
		heeksCAD->RegisterOnBeforeNewOrOpen(OnBeforeNewOrOpen);
		callbacks_registered = true;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject* GetViewUnits(PyObject* self, PyObject* args)
{
	return PyFloat_FromDouble(heeksCAD->GetViewUnits());
}

static PyObject* GetFileFullPath(PyObject* self, PyObject* args)
{
	const wchar_t* str = heeksCAD->GetFileFullPath();
	if(str == NULL)
	{
		Py_INCREF(Py_None);
		return Py_None;
	}
	char conv_str[4096];
	wcstombs(conv_str, str, 4096);
	return PyBytes_FromString(conv_str);
}

static PyObject* GetSketchShape(PyObject* self, PyObject* args)
{
	int sketch_id = 0;
    if (!PyArg_ParseTuple( args, "i", &sketch_id)) return NULL;

	HeeksObj* object = heeksCAD->GetIDObject(SketchType, sketch_id);
	if (object == NULL)return PyBytes_FromString("");

	std::string sketch_str;

	HeeksObj* re_ordered_sketch = NULL;
	SketchOrderType order = heeksCAD->GetSketchOrder(object);
	if( (order != SketchOrderTypeCloseCW) &&
		(order != SketchOrderTypeCloseCCW) &&
		(order != SketchOrderTypeMultipleCurves) &&
		(order != SketchOrderHasCircles))
	{
		re_ordered_sketch = object->MakeACopy();
		heeksCAD->ReOrderSketch(re_ordered_sketch, SketchOrderTypeReOrder);
		object = re_ordered_sketch;
	}

	bool first = true;
	char str[1024];
	for(HeeksObj* child = object->GetFirstChild(); child; child = object->GetNextChild())
	{
		if(first)
		{
			double s[3];
			if(child->GetStartPoint(s))
			{
				sprintf(str, "x%gy%g\n", s[0], s[1]);
				sketch_str.append(str);
			}
			first = false;
		}

		double e[3];
		if(!child->GetEndPoint(e))continue;

		if(child->GetType() == ArcType)
		{
			double c[3];
			if(!child->GetCentrePoint(c))continue;
			double a[3];
			if(!heeksCAD->GetArcAxis(child, a))continue;
			sprintf(str, "%sx%gy%gi%gj%g\n", (a[2]>0)?"a":"t", e[0], e[1], c[0], c[1]);
			sketch_str.append(str);
		}
		else
		{
			sprintf(str, "x%gy%g\n", e[0], e[1]);
			sketch_str.append(str);
		}
	}

	if(re_ordered_sketch)
	{
		delete re_ordered_sketch;
	}

	return PyBytes_FromString(sketch_str.c_str());
}

static PyObject* RemoveObject(PyObject* self, PyObject* args)
{	
//remove object 
	HeeksObj *obj;
	int pyobj;

    if (!PyArg_ParseTuple( args, "i",  &pyobj)) return NULL;
	obj = (HeeksObj*)heeksCAD->GetIDObject(pyobj>>16,pyobj&0xFFFF);
	heeksCAD->Remove(obj);

	
	PyObject *pValue = Py_None;
	
	return pValue;
}

struct module_state {
	PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
error_out(PyObject *m) {
	struct module_state *st = GETSTATE(m);
	PyErr_SetString(st->error, "something bad happened");
	return NULL;
}


static PyMethodDef HeeksPythonMethods[] = {
	{ "sketch", NewSketch, METH_VARARGS, "sketch()" },
	//	{"wxhandle", WxHandle, METH_VARARGS , "wxhandle()"},
	{ "extrude", Extrude, METH_VARARGS, "extrude(sketch,height)" },
	{ "revolve", Revolve, METH_VARARGS, "revolve(sketch,angle)" },
	{ "reorder", Reorder, METH_VARARGS, "reorder(sketch)" },
	{ "point", NewPoint, METH_VARARGS, "point(x,y,z)" },
	{ "linearc2wire", LineArc2Wire, METH_VARARGS, "linearc2wire(linearc)" },
	{ "pipe", Pipe, METH_VARARGS, "pipe(wire,sketch)" },
	{ "arc", NewArc, METH_VARARGS, "arc(cx,cy,cz,radius,start_a,end_a,ux,uy,uz)" },
	{ "arc2", NewArc2, METH_VARARGS, "arc(sx,sy,sz,ex,ey,ez,cx,cy,cz,ux,uy,uz)" },
	{ "line", NewLine, METH_VARARGS, "line(start_x, start_y, end_x, end_y)" },
	{ "line3d", NewLine3d, METH_VARARGS, "line3d(start_x, start_y, start_z, end_x, end_y, end_z)" },
	{ "circle", NewCircle, METH_VARARGS, "circle(centre_x, centre_y, radius)" },
	{ "cuboid", NewCuboid, METH_VARARGS, "cuboid(centre_x, centre_y, centre_z, length, width, height)" },
	{ "cylinder", NewCylinder, METH_VARARGS, "cylinder(centre_x, centre_y, centre_z, radius, height)" },
	{ "directedcylinder", NewCylinderEx, METH_VARARGS, "directedcylinder(centre_x, centre_y, centre_z, dir_x, dir_y, dir_z, radius, height)" },
	{ "cone", NewCone, METH_VARARGS, "cylinder(centre_x, centre_y, centre_z, radius1, radius2, height)" },
	{ "sphere", NewSphere, METH_VARARGS, "sphere(centre_x, centre_y, centre_z, radius)" },
	{ "group", NewGroup, METH_VARARGS, "group()" },
	{ "add", Add, METH_VARARGS, "add(group,obj)" },
	{ "fuse", Fuse, METH_VARARGS, "fuse(obj1,obj2)" },
	{ "common", Common, METH_VARARGS, "common(obj1,obj2)" },
	{ "cut", Cut, METH_VARARGS, "cut(obj1,obj2)" },
	{ "getlastobj", GetLastObj, METH_VARARGS, "getlastobj()" },
	{ "rotate", Rotate, METH_VARARGS, "rotate(object,p_x,p_y,p_z,u_x,u_y,u_z,r)" },
	{ "translate", Translate, METH_VARARGS, "translate(object,p_x,p_y,p_z)" },
	{ "scale", Scale, METH_VARARGS, "scale(object,p_x,p_y,p_z,scale)" },
	{ "setcolor", SetColor, METH_VARARGS, "setcolor(int r, int b, int g)" },
	{ "fillet2d", Fillet2d, METH_VARARGS, "fillet2d(obj,point,radius)" },
	{ "coordinate", NewCoordinateSystem, METH_VARARGS, "coordinate(position,x_vec,y_vec)" },
	{ "pickpoint", PickPoint, METH_VARARGS, "pickpoint()" },
	{ "lastclicked", GetClickedPos, METH_VARARGS, "lastclicked()" },
	{ "view_extents", ViewExtents, METH_VARARGS, "view_extents()" },
	{ "ve", ViewExtents, METH_VARARGS, "ve()" },
	{ "xyzview", XYZview, METH_VARARGS, "xyzview()" },
	{ "getpoint", GetPoint3d, METH_VARARGS, "getpoint()" },
	{ "addtext", NewText, METH_VARARGS, "addtext('string')" },
	{ "importdxf", DXFImport, METH_VARARGS, "importdxf('/filepath/filename.dxf')" },
	{ "addmenu", AddMenu, METH_VARARGS, "menu = addmenu('string')" },
	{ "add_menu_item", AddMenuItem, METH_VARARGS, "add_menu_item(menu, 'string', callback, icon)" },
	{ "add_window", AddWindow, METH_VARARGS, "add_window(hwnd)" },
	{ "get_frame_hwnd", GetFrameHwnd, METH_VARARGS, "hwnd = get_frame_hwnd()" },
	{ "get_frame_id", GetFrameId, METH_VARARGS, "hwnd = get_frame_id()" },
	{ "redraw", Redraw, METH_VARARGS, "redraw()" },
	{ "getsketch", GetSketch, METH_VARARGS, "getsketch()" },
	{ "getsketches", GetSketches, METH_VARARGS, "getsketches()" },
	{ "get_selected_sketches", GetSelectedSketches, METH_VARARGS, "get_selected_sketches()" },
	{ "register_callbacks", RegisterCallbacks, METH_VARARGS, "register_callbacks(on_new_or_open)" },
	{ "get_view_units", GetViewUnits, METH_VARARGS, "units = get_view_units()" },
	{ "GetFileFullPath", GetFileFullPath, METH_VARARGS, "file_path = GetFileFullPath()" },
	{ "GetSketchShape", GetSketchShape, METH_VARARGS, "s = GetSketchShape(2)" },
	{ "remove", RemoveObject, METH_VARARGS, "remove(object)" },
	{ "undopt", NewCreateUndoPoint, METH_VARARGS, "undopt()" },
	{ "changed", NewChanged, METH_VARARGS, "changed()" },
	{ "error_out", (PyCFunction)error_out, METH_NOARGS, NULL },
	{ NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3

static int HeeksPython_traverse(PyObject *m, visitproc visit, void *arg) {
	Py_VISIT(GETSTATE(m)->error);
	return 0;
}

static int HeeksPython_clear(PyObject *m) {
	Py_CLEAR(GETSTATE(m)->error);
	return 0;
}


static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"HeeksPython",
	NULL,
	sizeof(struct module_state),
	HeeksPythonMethods,
	NULL,
	HeeksPython_traverse,
	HeeksPython_clear,
	NULL
};

#define INITERROR return NULL

PyObject *
PyInit_HeeksPython(void)

#else
#define INITERROR return

void
initHeeksPython(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
	PyObject *module = PyModule_Create(&moduledef);
#else
	PyObject *module = Py_InitModule("HeeksPython", HeeksPythonMethods);
#endif

	if (module == NULL)
		INITERROR;
	struct module_state *st = GETSTATE(module);

	st->error = PyErr_NewException("HeeksPython.Error", NULL, NULL);
	if (st->error == NULL) {
		Py_DECREF(module);
		INITERROR;
	}

#if PY_MAJOR_VERSION >= 3
	return module;
#endif
}
