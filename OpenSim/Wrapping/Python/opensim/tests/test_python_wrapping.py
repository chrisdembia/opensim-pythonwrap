"""We do not perform thorough error/exception checking.

"""

from cStringIO import StringIO
import sys
import unittest

import numpy as np

# This import assumes that the opensim wrapping has been installed,
import opensim

class TestSuper(unittest.TestCase):
    """Tests changes (%extend's and %rename's) to superclasses like Object,
    etc. that should affect all/most classes.

    """
    def test___str__(self):
        """Ensures that all Object's toString() method is mapped to __str__()
        correctly.

        """
        a = opensim.Model()
        a.setName('model1')

        old_stdout = sys.stdout
        sys.stdout = mystdout = StringIO()

        print a
        sys.stdout = old_stdout

        self.assertEquals(mystdout.getvalue(), 'model1\n')

        b = opensim.Manager()
        b.setName('managerA')

        old_stdout = sys.stdout
        sys.stdout = mystdout = StringIO()

        print b
        sys.stdout = old_stdout

        self.assertEquals(mystdout.getvalue(), 'managerA\n')

    def test_printToFile(self):
        a = opensim.Model()
        a.setName('model1')

        a.printToFile('test_printToFile.xml')

        fidout = open('test_printToFile.xml', 'r')
        fiddes = open('test_printToFile_des.xml', 'r')

        self.assertEquals(fidout.read(), fiddes.read())

        fidout.close()
        fiddes.close()


class TestSet(unittest.TestCase):
    """We've added some methods to template<class T> class Set, particularly
    magic/special/dunder methods, that should work for all sets.

    """
    def setUp(self):
        # Functions.
        self.s = opensim.FunctionSet()
        self.f1 = opensim.Constant(1.5)
        self.f1.setName('fcn1')
        self.f2 = opensim.PiecewiseLinearFunction()
        self.f2.setName('fcn2')
        self.f2.addPoint(1.5, 3.0)
        self.f2.addPoint(2.0, 4.0)
    
        # DisplayGeometry.
        self.gs = opensim.GeometrySet()
        self.g1 = opensim.DisplayGeometry()
        self.g1.setName('gA')
        self.g2 = opensim.DisplayGeometry()
        self.g2.setName('gB')

    def test___contains__(self):
        """Ensures that "value in set" works."""

        def helper(the_set, item1, item2):
            # Actually does the check for a given set and items to put in set.
            self.assertFalse(item1 in the_set)
            the_set.setSize(1)
            the_set.insert(0, item1)
            self.assertTrue(item1 in the_set)

            self.assertFalse(item2 in the_set)
            the_set.adoptAndAppend(item2)
            self.assertTrue(item2 in the_set)

        # Functions.
        helper(self.s, self.f1, self.f2)
    
        # DisplayGeometry.
        helper(self.gs, self.g1, self.g2)

        # TODO what if the items in the set do not have a name?

    def test___setitem__(self):
        """One can insert elements in the Set, given that it has the adequate
        size.

        """
        # TODO the syntax using setSize does not work.
        #self.s.setSize(1)
        #self.s[0] = self.f1
        self.s.adoptAndAppend(self.f1)
        # adoptAndAppend seems to be making a copy? or something like that.
        self.assertIs(opensim.Constant.safeDownCast(self.s.get(0)), self.f1)
        with self.assertRaises(Exception):
            # Not big enough.
            self.s[1] = self.f2

        self.gs.setSize(2)
        self.gs[0] = self.g1
        self.gs[1] = self.g2
        self.assertIs(self.gs.get(0), self.g1)
        self.assertIs(self.gs.get(1), self.g2)

    def test___getitem__(self):
        """One can access elements in the Set by either providing an int index,
        or by providing a string name of one of the elements in the Set.

        """
        self.s.adoptAndAppend(self.f1)
        self.assertEquals(self.s[0].getName(), self.f1.getName())

    def test___len__(self):
        """Ensures that the user can getSize() using built-in len()."""
        self.assertEquals(len(self.s), 0)
        self.s.adoptAndAppend(self.f1)
        self.assertEquals(len(self.s), 1)

    def test_dict(self):
        """Method that returns a dict of all entries in the Set."""
        # TODO references or pointers or what?
        # TODO may not work well if entries don't all have names.
        pass

    def test_list(self):
        """Method that returns a list of all entries in the Set."""
        pass

    def test_getNames(self):
        """Instead of passing a SimTK::Array<std::string> by reference as in
        the C++ API, a list of str's is returned.
        
        """
        # TODO haven't been able to get this to work yet.
        self.s.adoptAndAppend(self.f1)
        self.s.adoptAndAppend(self.f2)
        names = self.s.getNames()
        self.assertTrue(type(names) == list)
        for i in range(len(self.s.getNames())):
            self.assertEquals(names[i], self.s[i].getName())


class TestValueTypes(unittest.TestCase):
    """Ensures the proper conversion of std::string and std::string * to python
    str's.

    """
    def test_string(self):
        """Ensures that strings work in OpenSim/version.h."""

        # TODO this test will need to be updated when the version
        # changes...silly.
        self.assertEquals(opensim.GetVersion(), '3.0.0')

    def test_ArrayDouble(self):
        """Ensures proper construction and use of OpenSim::Array<double>.

        """
        # TODO using getitem() versus get()?
        a = opensim.ArrayDouble(5, 2)
        self.assertEquals(a.getitem(0), 5)
        self.assertEquals(a.size(), 2)
        self.assertEquals(a.getCapacity(), 4)

    def test_PropertyGroup(self):
        pg = opensim.PropertyGroup("hello")
        self.assertEquals(pg.getName(), "hello")

        pg2 = opensim.PropertyGroup()
        pg2.setName("pg_name")
        self.assertEquals(pg2.getName(), "pg_name")

    def test_Geometry(self):
        # TODO

        # Renamed enum Geometry::None to Geometry::NoneType.
        self.assertEquals(opensim.Geometry.NoneType, 0)

        # Renamed DisplayGoemetry::None to DisplayGeometry::NonePreference.
        self.assertEquals(opensim.DisplayGeometry.NonePreference, 0)


    def test_Vector(self):
        """Creates a vector, sets its size, sets some values, uses the indexing
        operator (e.g., a[0])

        """
        v = opensim.Vector()
        v.resize(2)
        v.set(0, 1.5)
        self.assertEquals(v.get(0), 1.5)

        self.assertEquals(v[0], 1.5)
        v.set(1, 3)
        self.assertEquals(v[1], 3)

        # __setitem__().
        v[0] = 4.5
        self.assertEquals(v[0], 4.5)

        # out of range.
        with self.assertRaises(Exception):
            v[8] = 6.2

        # Check length of vector with __len__().
        self.assertEquals(len(v), 2)

        # -- Tests the constructor using numpy array input.
        w = opensim.Vector(np.array([1, 2, 3]))
        self.assertEquals(w[0], 1)
        self.assertEquals(w[1], 2)
        self.assertEquals(w[2], 3)

        # In fact, other types of input should work as well. lists:
        x = opensim.Vector([5, 3, 4])
        self.assertEquals(x[0], 5)
        self.assertEquals(x[1], 3)
        self.assertEquals(x[2], 4)

        # ... and tuples:
        z = opensim.Vector((7, 4, 1))
        self.assertEquals(z[0], 7)
        self.assertEquals(z[1], 4)
        self.assertEquals(z[2], 1)


class TestFunctions(unittest.TestCase):
    """Ensures the proper construction of Function's."""

    def test_Constant(self):
        f = opensim.Constant()
        f.setName("fcn1")
        self.assertEquals(f.getName(), "fcn1")

        self.assertEquals(f.getClassName(), "Constant")

        f.setValue(3.5)
        self.assertEquals(f.getValue(), 3.5)

        g = opensim.Constant(2.5)
        self.assertEquals(g.getValue(), 2.5)

    def test_SimmSpline(self):
        f = opensim.SimmSpline()

        g = opensim.SimmSpline(5, [0, 2, 4, 6, 8], [1, 2, 1, 2, 3])
        self.assertEquals(g.calcValue(8), 3)

        x = np.array([0, 2, 4, 6, 8])
        y = np.array([1, 2, 1, 2, 4])
        # TODO default arguments in the constructor not converted
        # to keyword arguments
        g2 = opensim.SimmSpline(5, x, y)
        self.assertEquals(g2.calcValue(8), 4)

        h = opensim.SimmSpline(5, [0, 2, 4, 6, 8], [1, 2, 1, 2, 3], "fcn")
        self.assertEquals(h.getName(), "fcn")

    def test_PiecewiseLinearFunction(self):
        f = opensim.PiecewiseLinearFunction()
        f.setName("fcn1")
        self.assertEquals(f.getName(), "fcn1")

        f.addPoint(0, 1)
        f.addPoint(1, 1.5)
        f.addPoint(2, 2)
        self.assertEquals(f.getSize(), 3)

        v = opensim.Vector()
        v.resize(1)
        v.set(0, 1.5)
        self.assertEquals(f.calcValue(v), 1.75)

        # Using tuple typemap(in) for const SimTK::Vector&'s.
        self.assertEquals(f.calcValue((1.5, )), 1.75)

        # Using list typemap(in) for const SimTK::Vector&'s.
        self.assertEquals(f.calcValue([1.5]), 1.75)

        # Using numpy array typemap(in) for const SimTK::Vector&'s.
        # TODO