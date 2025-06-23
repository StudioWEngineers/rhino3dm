"""
PointGeometryTestSuite
----------------------

Tests for the `PointGeometry` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import PointGeometry, Point3d

# local library specific imports


class PointGeometryTestSuite(TestCase):
    """Tests for the `PointGeometry` class.
    """
    def test_constructor(self) -> None:
        """Tests for the `__init__` method.
        """
        with self.subTest(msg="Default constructor"):
            self.assertEqual(PointGeometry().point, Point3d(0, 0, 0))

        with self.subTest(msg="Constructor with coordinates"):
            self.assertEqual(PointGeometry(1, 2, 1.1).point, Point3d(1, 2, 1.1))

        with self.subTest(msg="Constructor with Point3d"):
            self.assertEqual(PointGeometry(Point3d(1, 2, 1.1)).point, Point3d(1, 2, 1.1))

    def test_is_valid(self) -> None:
        """Test for the `is_valid` method.
        """
        self.assertTrue(PointGeometry().is_valid())

    def test_point_member_variable(self) -> None:
        """Test for the `point` member variable.
        """
        self.assertIsInstance(PointGeometry().point, Point3d)
