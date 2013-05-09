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



