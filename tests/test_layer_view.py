"""
LayerViewTestSuite
------------------

Tests for the `LayerView` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase
from uuid import UUID

# third party library imports
from rhino3dm import Layer, Model

# local library specific imports


class LayerViewTestSuite(TestCase):
    """Tests for the `LayerView` class.
    """
    def setUp(self) -> None:
        self.model = Model()

        layer = Layer()
        layer.color = (1, 2, 3, 255)
        layer.plot_color = (10, 20, 30, 255)
        layer.name = "my new layer"
        self.model.LayerTable.add(layer)

        self.layer = self.model.LayerTable.get_by_name("my new layer")

    def test_get_color(self) -> None:
        """Tests for the `color` property.
        """
        self.assertEqual(self.layer.color, (1, 2, 3, 255))

    def test_get_full_path(self) -> None:
        """Tests for the `full_path` property.
        """
        self.assertEqual(self.layer.full_path, "my new layer")

    def test_get_iges_level(self) -> None:
        """Tests for the `iges_level` property.
        """
        self.assertEqual(self.layer.iges_level, -1)

    def test_get_index(self) -> None:
        """Tests for the `index` property.
        """
        self.assertEqual(self.layer.index, 0)

    def test_get_is_expanded(self) -> None:
        """Tests for the `is_expanded` property.
        """
        self.assertTrue(self.layer.is_expanded)

    def test_get_is_locked(self) -> None:
        """Tests for the `is_locked` property.
        """
        self.assertFalse(self.layer.is_locked)

    def test_get_is_visible(self) -> None:
        """Tests for the `is_visible` property.
        """
        self.assertTrue(self.layer.is_visible)

    def test_get_line_type_index(self) -> None:
        """Tests for the `line_type_index` property.
        """
        self.assertEqual(self.layer.line_type_index, -1)

    def test_get_name(self) -> None:
        """Tests for the `name` property.
        """
        self.assertEqual(self.layer.name, "my new layer")

    def test_get_parent_uuid(self) -> None:
        """Tests for the `parent_uuid` property.
        """
        self.assertEqual(self.layer.parent_uuid, UUID(int=0))

    def test_get_persistent_locking(self) -> None:
        """Tests for the `persistent_locking` property.
        """
        self.assertFalse(self.layer.persistent_locking)

    def test_get_persistent_visibility(self) -> None:
        """Tests for the `persistent_visibility` property.
        """
        self.assertTrue(self.layer.persistent_visibility)

    def test_get_plot_color(self) -> None:
        """Tests for the `plot_color` property.
        """
        self.assertEqual(self.layer.plot_color, (10, 20, 30, 255))

    def test_get_plot_weight(self) -> None:
        """Tests for the `plot_weight` property.
        """
        self.assertEqual(self.layer.plot_weight, 0)

    def test_get_render_material_index(self) -> None:
        """Tests for the `render_material_index` property.
        """
        self.assertEqual(self.layer.render_material_index, -1)

    def test_repr(self) -> None:
        """Tests for the `__repr__` method.
        """
        expected_repr = (
            "LayerView with properties:\n"
            "\tcolor = (1, 2, 3, 255)\n"
            "\tfull_path = 'my new layer'\n"
            "\tiges_level = -1\n"
            "\tindex = 0\n"
            "\tis_expanded = true\n"
            "\tis_locked = false\n"
            "\tis_visible = true\n"
            f"\tlayer_uuid = {self.model.LayerTable.get_layer_uuid('my new layer')}\n"
            "\tline_type_index = -1\n"
            "\tname = 'my new layer'\n"
            f"\tparent_uuid = {UUID(int=0)}\n"
            "\tpath separator = ::\n"
            "\tpersistent_locking = false\n"
            "\tpersistent_visibility = true\n"
            "\tplot_color = (10, 20, 30, 255)\n"
            "\tplot_weight = 0\n"
            "\trender_material_index = -1\n"
        )

        self.assertEqual(str(self.layer), expected_repr)
