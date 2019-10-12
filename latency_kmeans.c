//#include <stdio.h>
#include <Python.h>
#include "fast_code_utils.h"
int main(int argc, char *argv[])
{
    PyObject *pName, *pModule; 
    PyObject *pFunc, *pArgs, *pValue;
    PyObject *pClass, *pInst;
    PyObject *pClassd, *pInstd;
    int n_clusters = 2;
    long long int start, end;

    //Py_SetProgramName(argv[0]);
    Py_Initialize();
    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("sys.path.append(\"./\")\n");
    PyRun_SimpleString("from time import time,ctime\n"
                     "print('Today is', ctime(time()))\n");
    pName = PyUnicode_FromString(argv[1]);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if(pModule != NULL)
    {
        pClass = PyObject_GetAttrString(pModule, "KMeans");
        pArgs = PyTuple_New(1);
        pValue = PyLong_FromLong(n_clusters);
        PyTuple_SetItem(pArgs, 0, pValue);
        Py_DECREF(pValue);
        pInst  = PyEval_CallObject(pClass, pArgs);
        Py_DECREF(pArgs);

        pClassd = PyObject_GetAttrString(pModule, "load_digits");
        pArgs = PyTuple_New(0);
        //pValue = PyLong_FromLong(n_clusters);
        //PyTuple_SetItem(pArgs, 0, pValue);
        //Py_DECREF(pValue);
        pInstd  = PyEval_CallObject(pClassd, pArgs);
        Py_DECREF(pArgs);


        pFunc = PyObject_GetAttrString(pModule, "hello");
        if(pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(2);
            //pValue = PyLong_FromLong(n_clusters);
            //PyTuple_SetItem(pArgs, 0, pValue);
            //Py_DECREF(pValue);
            PyTuple_SetItem(pArgs, 0, pInst);
            PyTuple_SetItem(pArgs, 1, pInstd);
            start = rdtsc(); 
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            pValue = PyObject_CallObject(pFunc, pArgs);
            //printf("Result of call: %ld\n", PyLong_AsLong(pValue));
            end = rdtsc(); 
            printf("Run Time = %f\n",(end-start)/(1.8*10000000000));

        }
        else
        {
            printf("Not Callable\n");
        }
       
    }
    else
    {
        printf ("Module Not Found\n");
    }
    Py_Finalize();
    return 0;
}
