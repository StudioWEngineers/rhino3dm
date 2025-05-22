"""
PointTestSuite
--------------

Tests for the `Point` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from math import sqrt
from unittest import TestCase

# third party library imports
from rhino3dm import Point

# local library specific imports


class PointTestSuite(TestCase):
    """Tests for the `Point` class.
    """
    def test_distance_to(self) -> None:
        """Tests for the `distance_to` method.
        """
        point = Point(0, 0, 0)
        self.assertEqual(point.distance_to(Point(1, 1, 1)), sqrt(3))

    def test_equal(self) -> None:
        """Tests for the `==` operator.
        """
        point_0 = Point(0, 0, 1.1)
        point_1 = Point(0, 0, 1.1)

        self.assertTrue(point_0 == point_1)

    def test_equal_not(self) -> None:
        """Tests for the `!=` operator.
        """
        point_0 = Point(0, 0, 1.1)
        point_1 = Point(1, 0, 1.1)

        self.assertTrue(point_0 != point_1)

    def test_get_and_set_x_coordinate(self) -> None:
        """Tests for the `x`, `y` and `z` property.
        """
        point = Point(0, 0, 0)

        with self.subTest(msg="Get x-coordinate"):
            self.assertEqual(point.x, 0)

        point.x = 3.1

        with self.subTest(msg="Get x-coordinate after set"):
            self.assertEqual(point.x, 3.1)

    def test_get_and_set_y_coordinate(self) -> None:
        """Tests for the `y` property.
        """
        point = Point(0, 0, 0)

        with self.subTest(msg="Get y-coordinate"):
            self.assertEqual(point.y, 0)

        point.y = 3.1

        with self.subTest(msg="Get y-coordinate after set"):
            self.assertEqual(point.y, 3.1)

    def test_get_and_set_z_coordinate(self) -> None:
        """Tests for the `z` property.
        """
        point = Point(0, 0, 1.1)

        with self.subTest(msg="Get z-coordinate"):
            self.assertEqual(point.z, 1.1)

        point.z = 3.1

        with self.subTest(msg="Get z-coordinate after set"):
            self.assertEqual(point.z, 3.1)

    def test_is_coincident(self) -> None:
        """Tests for the `is_coincident` method.
        """
        point = Point(1, 2, 3.1)
        self.assertTrue(point.is_coincident(Point(1, 2, 3.1)))

    def test_multiplication(self) -> None:
        """Tests for the `*` operator.
        """
        point = Point(0, 0, 1.1) * 2.1

        with self.subTest(msg="x-coordinate"):
            self.assertEqual(point.x, 0)

        with self.subTest(msg="y-coordinate"):
            self.assertEqual(point.y, 0)

        with self.subTest(msg="z-coordinate"):
            self.assertEqual(point.z, 1.1 * 2.1)

    def test_sum(self) -> None:
        """Tests for the `+` operator.
        """
        point = Point(0, 0, 1.1) + Point(1, 2, 3)

        with self.subTest(msg="x-coordinate"):
            self.assertEqual(point.x, 1)

        with self.subTest(msg="y-coordinate"):
            self.assertEqual(point.y, 2)

        with self.subTest(msg="z-coordinate"):
            self.assertEqual(point.z, 4.1)
