
/* From Java .i file: #pragma SWIG nowarn=822,451,503,516,325 */
// warning 314: print is a python keyword, renaming to _print.
// TODO #pragma SWIG nowarn=314
// warning 451: Setting a const char * variable may leak memory. 
// TODO typemap this away.
#pragma SWIG nowarn=451
// warning 362: operator= ignored.
// TODO #pragma SWIG nowarn=362

%feature("autodoc", "3");

/*
// TODO ideally would not be redefining exceptions. Temporary so I can move
// forward.
namespace std {
    class exception {
        public:
            exception();
            exception(const exception& rhs);
            virtual ~exception();
            virtual const char *what(void);
    };
}
*/

%include "exception.i"
%include "cpointer.i"
%include "std_string.i"
%include "typemaps.i"

%include "numpy.i"
%init %{
    import_array()
%}

// Ignore certain operator overloads.
// TODO could maybe use __copy__() to achieve copies.
%ignore *::operator=;
%ignore *::operator--;
%ignore *::operator++;

// To avert warning 314.
// %rename(printToXML) OpenSim::Object::print(const std::string &);
// TODO the autodoc is not working.
%feature("autodoc", "This function is the same as print(), but has been renamed for the Python wrapping since `print` is a python keyword.") printToFile;
%rename(printToFile) print;

// Exceptions.
// TODO could create multiple exception types.
// SWIG_exception comes from exception.i.
// TODO std::exception is being ignored.
// TODO see 'except' for swig.
%exception {
    try {
        $action
    }
    catch(std::exception& _ex){
        SWIG_exception(SWIG_RuntimeError, _ex.what());
    }
}

/*
%include "pythonWrapOpenSimCommon.i"
%include "pythonWrapOpenSimSimulation.i"
%include "pythonWrapOpenSimAnalyses.i"
%include "pythonWrapOpenSimActuators.i"
%include "pythonWrapOpenSimTools.i"

1. Array.getitem() instead of get(), is this the expected use case?
2. Property::operator[]
3. Property::operator=
4. Set up a normal python package, with setup.py, etc.
5. implement __str__() as toString().
6. For Vec3, use np.array, etc.
7. Object class does not exist? virtual?
8. Geometry should be virtual.
9. Can extend and add a __iter__ method to allow for python iteration.
10. Inertia.getMoments()[0] "Vec3 object does not support indexing"
11. numpy/doc/swig/test has good examples of using SWIG!
12. typemap const char * to string.
13. ignore warning 503: 'can't wrap '' unless renamed to a valid identifier.'
14. print() -> printToXML()
15. optional arguments.
16. Convert all Set* to _Set* (like SetJoints to _SetJoints).
17. Extend Set to have an iter() method!!! or dict() or something!!!
18. Tests would be performed in the build directory, not in the source tree.
19. exception handling. see numpy.
20. can maybe remove NumPy_Backward_Compatibility
21. make sets easy to iterate through.
22. use __copy__ to take care of operator=.
23. adoptAndAppend seems to be making a copy.
24. safeDownCast() in documentation.
*/
