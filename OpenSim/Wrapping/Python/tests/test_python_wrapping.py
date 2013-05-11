"""We do not perform thorough error/exception checking.

"""

from cStringIO import StringIO
import sys
import unittest

import numpy as np

# This import assumes that the opensim wrapping has been installed,
# and we're importing opensim from its installed location in site-packages (or
# dist-packages?)
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

    def test_printToXML(self):
        a = opensim.Model()
        a.setName('model1')

        a.printToXML('test_printToXML.xml')

        fidout = open('test_printToXML.xml', 'r')
        fiddes = open('test_printToXML_des.xml', 'r')

        self.assertEquals(fidout.read(), fiddes.read())

        fidout.close()
        fiddes.close()


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
        pass

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
            v[4] = 6.2

        # Check length of vector with __len__().
        self.assertEquals(len(v), 2)


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
