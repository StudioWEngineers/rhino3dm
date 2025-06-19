"""
OpenNURBSObjectTestSuite
------------------------

Tests for the `OpenNURBSObject` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import OpenNURBSObject, TextLog

# local library specific imports


class OpenNURBSObjectTestSuite(TestCase):
    """Tests for the `OpenNURBSObject` class.
    """
    def setUp(self):
        self.obj = OpenNURBSObject()

    def test_is_corrupt(self) -> None:
        """Test for the `is_corrupt` method.
        """
        self.assertFalse(self.obj.is_corrupt(False, True, TextLog.null()))


