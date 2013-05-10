"""We do not perform thorough error/exception checking.

"""

import unittest

# This import assumes that the opensim wrapping has been installed,
# and we're importing opensim from its installed location in site-packages (or
# dist-packages?)
import opensim

class TestValueTypes(unittest.TestCase):
    """Ensures the proper conversion of std::string and std::string * to python
    str's.

    """

    def test_string(self):
        """Ensures that strings work in OpenSim/version.h."""

        # TODO this test will need to be updated when the version
        # changes...silly.
        assert opensim.GetVersion() == '3.0.0'

    def test_ArrayDouble(self):
        """Ensures proper construction and use of OpenSim::Array<double>.

        """
        # TODO using getitem() versus get()?
        a = opensim.ArrayDouble(5, 2)
        assert a.getitem(0) == 5
        assert a.size() == 2
        assert a.getCapacity() == 4

    def test_PropertyGroup(self):
        pg = opensim.PropertyGroup("hello")
        assert pg.getName() == "hello"

        pg2 = opensim.PropertyGroup()
        pg2.setName("pg_name")
        assert pg2.getName() == "pg_name"

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
        assert v.get(0) == 1.5

        assert v[0] == 1.5
        v.set(1, 3)
        assert v[1] == 3

class TestFunctions(unittest.TestCase):
    """Ensures the proper construction of Function's."""

    def test_Constant(self):
        f = opensim.Constant()
        f.setName("fcn1")
        assert f.getName() == "fcn1"

        assert f.getClassName() == "Constant"

        f.setValue(3.5)
        assert f.getValue() == 3.5

        g = opensim.Constant(2.5)
        assert g.getValue() == 2.5

    def test_SimmSpline(self):
        f = opensim.SimmSpline()

        g = opensim.SimmSpline(5, [0, 2, 4, 6, 8], [1, 2, 1, 2, 3])
        assert g.calcValue(8) == 3

        x = np.array([0, 2, 4, 6, 8])
        y = np.array([1, 2, 1, 2, 4])
        g2 = opensim.SimmSpline(5, x, y)
        assert g2.calcValue(8) == 4

        h = opensim.SimmSpline(5, [0, 2, 4, 6, 8], [1, 2, 1, 2, 3], "fcn")
        assert h.getName() == "fcn"

    def test_PiecewiseLinearFunction(self):
        f = opensim.PiecewiseLinearFunction()
        f.setName("fcn1")
        assert f.getName() == "fcn1"

        f.addPoint(0, 1)
        f.addPoint(1, 1.5)
        f.addPoint(2, 2)
        assert f.getSize() == 3

        v = opensim.Vector()
        v.resize(1)
        v.set(0, 1.5)
        # TODO this fails now but it shouldn't.
        # assert f.calcValue(v) == 1.75

        # Using tuple typemap(in) for const SimTK::Vector&'s.
        assert f.calcValue((1.5, )) == 1.75

        # Using list typemap(in) for const SimTK::Vector&'s.
        # TODO

        # Using numpy array typemap(in) for const SimTK::Vector&'s.
        # TODO
