"""
LayerTestSuite
--------------

Tests for the `Layer` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import Layer

# local library specific imports


class LayerTestSuite(TestCase):
    """Tests for the `Layer` class.
    """
    def setUp(self) -> None:
        self.layer = Layer()

    def test_get_and_plot_color(self) -> None:
        """Tests for the `get_plot_color` and `set_plot_color` methods.
        """
        with self.subTest(msg="Layer plot color before assignment"):
            self.assertEqual(self.layer.plot_color, (0, 0, 0, 255))

        self.layer.plot_color = (100, 50, 10, 255)

        with self.subTest(msg="Layer plot color after assignment"):
            self.assertEqual(self.layer.plot_color, (100, 50, 10, 255))

    def test_get_and_set_name(self) -> None:
        """Tests for the `get_name` and `set_name` methods.
        """
        with self.subTest(msg="Layer name before assignment"):
            self.assertEqual(self.layer.name, "")

        self.layer.name = "My new layer"

        with self.subTest(msg="Layer name after assignment"):
            self.assertEqual(self.layer.name, "My new layer")

    def test_get_full_path(self) -> None:
        """Tests for the `get_full_path` method.
        """
        with self.subTest(msg="Layer name before assignment"):
            self.assertEqual(self.layer.full_path, "")

        self.layer.name = "My new layer"

        with self.subTest(msg="Layer name after assignment"):
            self.assertEqual(self.layer.full_path, "My new layer")
