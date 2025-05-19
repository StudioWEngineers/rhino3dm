"""
LayerTableTestSuite
-------------------

Tests for the `LayerTable` class.


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


class LayerTableTestSuite(TestCase):
    """Tests for the `LayerTable` class.
    """
    def test_add(self) -> None:
        """Tests for the `add` method.
        """
        model = Model()

        layer1 = Layer()
        layer1.name = "Layer A"
        layer1.color = (255, 0, 255, 255)

        layer2 = Layer()
        layer2.name = "layer 2"

        model.LayerTable.add(layer1)
        model.LayerTable.add(layer2)

        with self.subTest(msg="Number of layers with using Count"):
            self.assertEqual(model.LayerTable.count(), 2)

        with self.subTest(msg="Number of layers with using __len__"):
            self.assertEqual(len(model.LayerTable), 2)

        with self.subTest(msg="Name of 1st layer"):
            self.assertEqual(model.LayerTable.get_by_index(0).name, "Layer A")

        with self.subTest(msg="Name of 2nd layer"):
            self.assertEqual(model.LayerTable.get_by_index(1).name, "layer 2")

        with self.subTest(msg="Color of 1st layer"):
            self.assertEqual(model.LayerTable.get_by_index(0).color, (255, 0, 255, 255))

    def test_count(self) -> None:
        """Tests for the `count` method.
        """
        model = Model()

        with self.subTest(msg="Number of layers for an empty model"):
            self.assertEqual(model.LayerTable.count(), 0)

        model.LayerTable.add(Layer())

        with self.subTest(msg="Current number of layers"):
            self.assertEqual(model.LayerTable.count(), 1)

    def test_delete_by_name(self) -> None:
        """Tests for the `delete_by_name` method.
        """
        model = Model()

        layer_1 = Layer()
        layer_2 = Layer()
        layer_1.name = "New layer 1"
        layer_2.name = "New layer 2"
        model.LayerTable.add(layer_1)
        model.LayerTable.add(layer_2)

        with self.subTest("Successfull delete"):
            self.assertTrue(model.LayerTable.delete_by_name("New layer 1"))

        with self.subTest("Unsuccessfull delete"):
            self.assertFalse(model.LayerTable.delete_by_name("New layer 3"))

        with self.subTest(msg="Current number of layers"):
            self.assertEqual(model.LayerTable.count(), 1)

    def test_delete_by_uuid(self) -> None:
        """Tests for the `delete_by_uuid` method.
        """
        model = Model()

        layer_1 = Layer()
        layer_2 = Layer()
        layer_1.name = "New layer 1"
        layer_2.name = "New layer 2"
        model.LayerTable.add(layer_1)
        model.LayerTable.add(layer_2)

        layer_1_uuid = model.LayerTable.get_layer_uuid("New layer 1")

        with self.subTest("Successfull delete"):
            self.assertTrue(model.LayerTable.delete_by_uuid(layer_1_uuid))

        with self.subTest("Unsuccessfull delete"):
            self.assertFalse(model.LayerTable.delete_by_uuid(UUID(int=0)))

        with self.subTest(msg="Current number of layers"):
            self.assertEqual(model.LayerTable.count(), 1)

    def test_getitem(self) -> None:
        """Tests for the `__getitem__` method.
        """
        model = Model()

        model.LayerTable.add(Layer())
        model.LayerTable.add(Layer())

        with self.subTest(msg="Negative index"):
            self.assertIsNone(model.LayerTable[-1])

        with self.subTest(msg="Not existing index"):
            self.assertIsNone(model.LayerTable[3])

        with self.subTest(msg="Existing index"):
            self.assertEqual(model.LayerTable[1].name, "Layer 02")

    def test_get_by_index(self) -> None:
        """Tests for the `get_by_index` method.
        """
        model = Model()

        layer_1 = Layer()
        layer_1.name = "Layer A"
        layer_1.color = (255, 0, 255, 255)

        layer_2 = Layer()
        layer_2.name = "layer 2"

        index_layer_1 = model.LayerTable.add(layer_1)
        index_layer_2 = model.LayerTable.add(layer_2)

        layer_view_1 = model.LayerTable.get_by_index(index_layer_1)
        layer_view_2 = model.LayerTable.get_by_index(index_layer_2)

        with self.subTest(msg="Retrieving not existing layer"):
            self.assertIsNone(model.LayerTable.get_by_index(3))

        with self.subTest(msg="Name of 2nd layer"):
            self.assertEqual(layer_view_2.name, "layer 2")

        with self.subTest(msg="Color of 1st layer"):
            self.assertEqual(layer_view_1.color, (255, 0, 255, 255))

    def test_get_by_name(self) -> None:
        """Tests for the `get_by_name` method.
        """
        model = Model()

        layer_1 = Layer()
        layer_1.name = "Layer A"
        layer_1.color = (255, 0, 255, 255)

        layer_2 = Layer()
        layer_2.name = "layer 2"

        model.LayerTable.add(layer_1)
        model.LayerTable.add(layer_2)

        layer_view_1 = model.LayerTable.get_by_name("Layer A")
        layer_view_2 = model.LayerTable.get_by_name("layer 2")

        with self.subTest(msg="Retrieving not existing layer"):
            self.assertIsNone(model.LayerTable.get_by_name("not existing"))

        with self.subTest(msg="Name of 2nd layer"):
            self.assertEqual(layer_view_2.name, "layer 2")

        with self.subTest(msg="Color of 1st layer"):
            self.assertEqual(layer_view_1.color, (255, 0, 255, 255))

    def test_get_by_uuid(self) -> None:
        """Tests for the `get_by_uuid` method.
        """
        model = Model()

        layer_1 = Layer()
        layer_1.name = "Layer A"
        layer_1.color = (255, 0, 255, 255)

        layer_2 = Layer()
        layer_2.name = "layer 2"

        model.LayerTable.add(layer_1)
        model.LayerTable.add(layer_2)

        layer_view_1 = model.LayerTable.get_by_uuid(
            model.LayerTable.get_layer_uuid("Layer A")
        )
        layer_view_2 = model.LayerTable.get_by_uuid(
            model.LayerTable.get_layer_uuid("layer 2")
        )

        with self.subTest(msg="Retrieving not existing layer"):
            self.assertIsNone(model.LayerTable.get_by_uuid(UUID(int=0)))

        with self.subTest(msg="Name of 2nd layer"):
            self.assertEqual(layer_view_2.name, "layer 2")

        with self.subTest(msg="Color of 1st layer"):
            self.assertEqual(layer_view_1.color, (255, 0, 255, 255))

    def test_get_layer_index(self) -> None:
        """Tests for the `get_layer_index` method.
        """
        model = Model()

        layer_0_index = model.LayerTable.add(Layer())
        layer_1_index = model.LayerTable.add(Layer())

        with self.subTest(msg="Retrieving index of not existing layer"):
            self.assertEqual(model.LayerTable.get_layer_index(""), -2147483647)

        with self.subTest(msg="Index of 1st layer"):
            self.assertEqual(model.LayerTable.get_layer_index("Layer 01"), layer_0_index)

        with self.subTest(msg="Index of 2nd layer"):
            self.assertEqual(model.LayerTable.get_layer_index("Layer 02"), layer_1_index)

    def test_get_layer_uuid(self) -> None:
        """Tests for the `get_layer_uuid` method.
        """
        model = Model()

        model.LayerTable.add(Layer())
        model.LayerTable.add(Layer())

        layer_1_uuid = model.LayerTable.get_layer_uuid("Layer 01")
        layer_2_uuid = model.LayerTable.get_layer_uuid("Layer 02")

        with self.subTest(msg="Retrieving uuid of not existing layer"):
            self.assertEqual(model.LayerTable.get_layer_uuid("Not existing"), UUID(int=0))

        with self.subTest(msg="Index of 1st layer"):
            self.assertEqual(model.LayerTable.get_layer_uuid("Layer 01"), layer_1_uuid)

        with self.subTest(msg="Index of 2nd layer"):
            self.assertEqual(model.LayerTable.get_layer_uuid("Layer 02"), layer_2_uuid)

    def test_has(self) -> None:
        """Tests for the `has` method.
        """
        model = Model()

        model.LayerTable.add(Layer())

        with self.subTest(msg="Not existing layer"):
            self.assertFalse(model.LayerTable.has("Not existing"))

        with self.subTest(msg="1st layer"):
            self.assertTrue(model.LayerTable.has("Layer 01"))

    def test_iter(self) -> None:
        """Tests for the `__iter__` method.
        """
        model = Model()

        model.LayerTable.add(Layer())
        model.LayerTable.add(Layer())

        for layer_index, layer in enumerate(model.LayerTable):
            with self.subTest(layer_index = layer_index):
                self.assertEqual(layer.name, f"Layer 0{layer_index + 1}")

            with self.subTest(layer_index = layer_index):
                self.assertEqual(layer.index, layer_index)

    def test_max_index(self) -> None:
        """Tests for the `max_index` method.
        """
        model = Model()

        with self.subTest(msg="max_index before adding layers to model"):
            self.assertEqual(model.LayerTable.max_index(), 0)

        model.LayerTable.add(Layer())
        model.LayerTable.add(Layer())

        with self.subTest(msg="max_index after adding layers to model"):
            self.assertEqual(model.LayerTable.max_index(), 2)

    def test_replace(self) -> None:
        """Tests for the `replace` method.
        """
        model = Model()

        model.LayerTable.add(Layer())
        model.LayerTable.add(Layer())

        layer_1_index = model.LayerTable.get_layer_index("Layer 01")
        layer_1_uuid = model.LayerTable.get_layer_uuid("Layer 01")

        new_layer = Layer()
        new_layer.name = "New layer"
        new_layer.color = (1, 2, 3, 255)

        with self.subTest(msg="Successfull replace"):
            self.assertTrue(model.LayerTable.replace("Layer 01", new_layer))

        # replacement operation preserves index, uuid and number of layers
        with self.subTest(msg="Check uuid"):
            self.assertEqual(model.LayerTable.get_layer_uuid("New layer"), layer_1_uuid)

        with self.subTest(msg="Check index"):
            self.assertEqual(model.LayerTable.get_layer_index("New layer"), layer_1_index)

        with self.subTest(msg="Check number of layer"):
            self.assertEqual(model.LayerTable.count(), 2)

        # replacement operation does not preserve max_index
        with self.subTest(msg="Check max_index"):
            self.assertEqual(model.LayerTable.max_index(), 3)

        # check has method implementation after replacement
        with self.subTest(msg="has method"):
            self.assertFalse(model.LayerTable.has("not existing"))

        with self.subTest(msg="has method"):
            self.assertTrue(model.LayerTable.has("New layer"))
