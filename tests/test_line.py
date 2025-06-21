"""
LineTestSuite
-------------

Tests for the `Line` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from math import sqrt
from unittest import TestCase, expectedFailure

# third party library imports
from rhino3dm import Line, Point3d

# local library specific imports


class LineTestSuite(TestCase):
    """Tests for the `Line` class.
    """
    def setUp(self) -> None:
        self.line = Line(Point3d(0, 0, 0), Point3d(1, 1, 1))

    def test_create(self) -> None:
        """Tests for the `create` method.
        """
        with self.subTest(msg="Successful create"):
            self.assertTrue(self.line.create(Point3d(1, 2, 3), Point3d(0, 0, 0)))

        with self.subTest(msg="Successful create"):
            self.assertEqual(self.line[0], Point3d(1, 2, 3))

        with self.subTest(msg="Unsuccessful create"):
            self.assertFalse(self.line.create(Point3d(1, 2, 3), Point3d(1, 2, 3)))
    @expectedFailure
    def test_distance_to(self) -> None:
        """Test for the `distance_to` method.
        """
        self.assertEqual(self.line.distance_to(Point3d(1, 0, 1)), sqrt(3) / 2)

    def test_getitem(self) -> None:
        """Tests for the `__getitem__` method.
        """
        with self.subTest(msg="Successful getitem"):
            self.assertEqual(self.line[0], Point3d(0, 0, 0))

        with self.assertRaises(IndexError):
            self.line[2]

    def test_equal(self) -> None:
        """Tests for the `__eq__` and `__ne__` methods.
        """
        with self.subTest(msg="Negative check"):
            self.assertFalse(self.line == Line())

        with self.subTest(msg="Positive check"):
            self.assertTrue(self.line == Line(Point3d(0, 0, 0), Point3d(1, 1, 1)))

    def test_is_valid(self) -> None:
        """Tests for the `is_valid` method.
        """
        with self.subTest(msg="Positive check"):
            self.assertTrue(self.line.is_valid())

        with self.subTest(msg="Negative check"):
            self.assertFalse(Line().is_valid())

    def test_length(self) -> None:
        """Test for the `length` method.
        """
        self.assertEqual(self.line.length(), sqrt(3))

    def test_point_at(self) -> None:
        """Test for the `point_at` method.
        """
        self.assertEqual(self.line.point_at(0.5), Point3d(0.5, 0.5, 0.5))

    def test_setitem(self) -> None:
        """Tests for the `__setitem__` method.
        """
        self.line[0] = Point3d(-1, 0, 0)

        with self.subTest(msg="Successful getitem"):
            self.assertEqual(self.line[0], Point3d(-1, 0, 0))

        with self.assertRaises(IndexError):
            self.line[2] = Point3d(0, 0, 0)
