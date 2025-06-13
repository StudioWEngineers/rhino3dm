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
from uuid import UUID, uuid4

# third party library imports
from rhino3dm import Layer

# local library specific imports


class LayerTestSuite(TestCase):
    """Tests for the `Layer` class.
    """
    def setUp(self) -> None:
        self.layer = Layer()

    def test_get_and_set_color(self) -> None:
        """Tests for the `color` property.
        """
        with self.subTest(msg="Layer color before assignment"):
            self.assertEqual(self.layer.color, (0, 0, 0, 255))

        self.layer.color = (100, 50, 10, 255)

        with self.subTest(msg="Layer color after assignment"):
            self.assertEqual(self.layer.color, (100, 50, 10, 255))

    def test_get_and_set_iges_level(self) -> None:
        """Tests for the `iges_level` property.
        """
        with self.subTest(msg="Layer iges_level before assignment"):
            self.assertEqual(self.layer.iges_level, -1)

        self.layer.iges_level = 10

        with self.subTest(msg="Layer iges_level after assignment"):
            self.assertEqual(self.layer.iges_level, 10)

    def test_get_index(self) -> None:
        """Tests for the `index` property.
        """
        self.assertEqual(self.layer.index, -2147483647)

    def test_get_and_set_is_expanded(self) -> None:
        """Tests for the `is_expanded` property.
        """
        with self.subTest(msg="Layer is_expanded before assignment"):
            self.assertTrue(self.layer.is_expanded)

        self.layer.is_expanded = False

        with self.subTest(msg="Layer is_expanded after assignment"):
            self.assertFalse(self.layer.is_expanded)

    def test_get_and_set_is_locked(self) -> None:
        """Tests for the `is_locked` property.
        """
        with self.subTest(msg="Layer is_locked before assignment"):
            self.assertFalse(self.layer.is_locked)

        self.layer.is_locked = True

        with self.subTest(msg="Layer is_locked after assignment"):
            self.assertTrue(self.layer.is_locked)

    def test_get_and_set_is_visible(self) -> None:
        """Tests for the `is_visible` property.
        """
        with self.subTest(msg="Layer is_visible before assignment"):
            self.assertTrue(self.layer.is_visible)

        self.layer.is_visible = False

        with self.subTest(msg="Layer is_visible after assignment"):
            self.assertFalse(self.layer.is_visible)

    def test_get_and_set_layer_uuid(self) -> None:
        """Tests for the `layer_uuid` property.
        """
        with self.subTest(msg="Layer layer_uuid before assignment"):
            self.assertEqual(self.layer.layer_uuid, UUID(int=0))

        new_id = uuid4()
        self.layer.layer_uuid = new_id

        with self.subTest(msg="Layer layer_uuid after assignment"):
            self.assertEqual(self.layer.layer_uuid, new_id)

    def test_get_and_set_line_type_index(self) -> None:
        """Tests for the `line_type_index` property.
        """
        with self.subTest(msg="Layer line_type_index before assignment"):
            self.assertEqual(self.layer.line_type_index, -1)

        self.layer.line_type_index = 3

        with self.subTest(msg="Layer line_type_index after assignment"):
            self.assertEqual(self.layer.line_type_index, 3)

    def test_get_and_set_name(self) -> None:
        """Tests for the `name` property.
        """
        with self.subTest(msg="Layer name before assignment"):
            self.assertEqual(self.layer.name, "")

        self.layer.name = "My new layer"

        with self.subTest(msg="Layer name after assignment"):
            self.assertEqual(self.layer.name, "My new layer")

    def test_get_and_set_parent_uuid(self) -> None:
        """Tests for the `parent_uuid` property.
        """
        with self.subTest(msg="Layer parent_uuid before assignment"):
            self.assertEqual(self.layer.parent_uuid, UUID(int=0))

        self.layer.parent_uuid = UUID(int=3)

        with self.subTest(msg="Layer parent_uuid after assignment"):
            self.assertEqual(self.layer.parent_uuid, UUID(int=3))

    def test_get_and_set_persistent_locking(self) -> None:
        """Tests for the `persistent_locking` property.
        """
        with self.subTest(msg="Layer persistent_locking before assignment"):
            self.assertFalse(self.layer.persistent_locking)

        # NOTE: persistent_locking has effect only if parent_uuid is not null and
        # is_locked is True. In this case the following set has no effect and
        # persistent_locking is False
        self.layer.persistent_locking = True
        with self.subTest(msg="Layer persistent_locking after assignment"):
            self.assertFalse(self.layer.persistent_locking)

        self.layer.parent_uuid = uuid4()
        self.layer.is_locked = True
        self.layer.persistent_locking = True
        with self.subTest(msg="Layer persistent_locking after assignment"):
            self.assertTrue(self.layer.persistent_locking)

    def test_get_and_set_persistent_visibility(self) -> None:
        """Tests for the `persistent_visibility` property.
        """
        with self.subTest(msg="Layer persistent_visibility before assignment"):
            self.assertTrue(self.layer.persistent_visibility)

        # NOTE: persistent_visibility has effect only if parent_uuid is not null and
        # is_visible is False. In this case the following set has no effect and
        # persistent_visibility is False
        self.layer.persistent_visibility = False
        with self.subTest(msg="Layer persistent_visibility after assignment"):
            self.assertTrue(self.layer.persistent_visibility)

        self.layer.parent_uuid = uuid4()
        self.layer.is_visible = False
        self.layer.persistent_visibility = False
        with self.subTest(msg="Layer persistent_locking after assignment"):
            self.assertFalse(self.layer.persistent_visibility)

    def test_get_and_set_plot_color(self) -> None:
        """Tests for the `plot_color` property.
        """
        with self.subTest(msg="Layer plot_color before assignment"):
            self.assertEqual(self.layer.plot_color, (0, 0, 0, 255))

        self.layer.plot_color = (100, 50, 10, 255)

        with self.subTest(msg="Layer plot_color after assignment"):
            self.assertEqual(self.layer.plot_color, (100, 50, 10, 255))

    def test_get_and_set_plot_weight(self) -> None:
        """Tests for the `plot_weight` property.
        """
        with self.subTest(msg="Layer plot_weight before assignment"):
            self.assertEqual(self.layer.plot_weight, 0)

        self.layer.plot_weight = 1.1

        with self.subTest(msg="Layer plot_weight after assignment"):
            self.assertEqual(self.layer.plot_weight, 1.1)

    def test_get_and_set_render_material_index(self) -> None:
        """Tests for the `render_material_index` property.
        """
        with self.subTest(msg="Layer render_material_index before assignment"):
            self.assertEqual(self.layer.render_material_index, -1)

        self.layer.render_material_index = 2

        with self.subTest(msg="Layer render_material_index after assignment"):
            self.assertEqual(self.layer.render_material_index, 2)

    def test_get_parent_uuid_is_not_null(self) -> None:
        """Tests for the `parent_uuid_is_not_null` read-only property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertFalse(self.layer.parent_uuid_is_not_null)

        self.layer.parent_uuid = uuid4()

        with self.subTest(msg="After assignment"):
            self.assertTrue(self.layer.parent_uuid_is_not_null)

    def test_get_parent_uuid_is_null(self) -> None:
        """Tests for the `parent_uuid_is_null` read-only property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertTrue(self.layer.parent_uuid_is_null)

        self.layer.parent_uuid = uuid4()

        with self.subTest(msg="After assignment"):
            self.assertFalse(self.layer.parent_uuid_is_null)

    def test_get_path_separator(self) -> None:
        """Tests for the `path_separator` read-only property.
        """
        self.assertEqual(self.layer.path_separator, "::")

    def test_repr(self) -> None:
        """Tests for the `__repr__` method.
        """
        expected_repr = (
            "Layer with properties:\n"
            "\tcolor = (0, 0, 0, 255)\n"
            "\tiges_level = -1\n"
            "\tindex = -2147483647\n"
            "\tis_expanded = true\n"
            "\tis_locked = false\n"
            "\tis_visible = true\n"
            f"\tlayer_uuid = {UUID(int=0)}\n"
            "\tline_type_index = -1\n"
            "\tname = ''\n"
            f"\tparent_uuid = {UUID(int=0)}\n"
            "\tpath separator = ::\n"
            "\tpersistent_locking = false\n"
            "\tpersistent_visibility = true\n"
            "\tplot_color = (0, 0, 0, 255)\n"
            "\tplot_weight = 0\n"
            "\trender_material_index = -1\n"
        )

        self.assertEqual(str(self.layer), expected_repr)
