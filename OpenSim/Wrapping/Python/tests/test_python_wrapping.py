import unittest

# This importing assumes that the opensim wrapping has been installed,
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
        """Creates a vector, sets its size, and some values."""

        v = opensim.Vector()
        v.resize(1)
        v.set(0, 1.5)
        assert v.get(0) == 1.5

    def test_Function(self):
        """Creates a piecewise linear function, adds points to it, and
        calculates its value.

        """
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
        assert f.calcValue(v) == 1.75
