"""
LineCurveTestSuite
------------------

Tests for the `LineCurve` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import LineCurve, Point3d

# local library specific imports


class LineCurveTestSuite(TestCase):
    """Tests for the `LineCurve` class.
    """
    def setUp(self) -> None:
        self.line = LineCurve(Point3d(0, 0, 0), Point3d(1, 1, 2))

    def test_dimension(self) -> None:
        """Test for the `dimension` method.
        """
        self.assertEqual(self.line.dimension(), 3)

    def test_is_valid(self) -> None:
        """Tests for the `is_valid` method.
        """
        with self.subTest(msg="Positive check"):
            self.assertTrue(self.line.is_valid())

        with self.subTest(msg="Negative check"):
            self.assertFalse(LineCurve().is_valid())

    def test_reverse(self) -> None:
        """Test for the `reverse` method.
        """
        self.assertTrue(self.line.reverse())

    def test_set_end_point(self) -> None:
        """Test for the `set_end_point` method.
        """
        self.line.set_end_point(Point3d(1, 1, 1.2))

        self.assertTrue(self.line.line.point_at(1) == Point3d(1, 1, 1.2))

    def test_set_start_point(self) -> None:
        """Test for the `set_start_point` method.
        """
        self.line.set_start_point(Point3d(1, 1, 1.2))

        self.assertTrue(self.line.line.point_at(0) == Point3d(1, 1, 1.2))

    def test_swap_coordinates(self) -> None:
        """Tests for the `swap_coordinates` method.
        """
        with self.subTest(msg="Positive swap"):
            self.assertTrue(self.line.swap_coordinates(1, 2))

        with self.subTest(msg="Check updated cooridnates"):
            self.assertTrue(self.line.line.point_at(1) == Point3d(1, 2, 1))
