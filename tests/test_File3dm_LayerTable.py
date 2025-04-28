import rhino3dm
from unittest import TestCase
from os import remove
from os.path import dirname

#objective: to test creating file with layers and reading a file with layers
class TestFile3dmLayerTable(TestCase):
    def test_createFileWithLayers(self) -> None:

        file3dm = rhino3dm.File3dm()

        #create layers
        layer1 = rhino3dm.Layer()
        layer1.Name = 'layer1'
        layer1.Color = (255,0,255,255)

        layer2 = rhino3dm.Layer()
        layer2.Name = 'layer2'

        file3dm.layers.Add(layer1)
        file3dm.layers.Add(layer2)

        qtyLayers = len(file3dm.layers)

        file3dm.write("test_createFileWithLayers.3dm")

        file = rhino3dm.File3dm.Read('test_createFileWithLayers.3dm')
        qtyLayers2 = len(file.layers)

        self.assertTrue(qtyLayers == 2 and qtyLayers2 == 2)

        remove(dirname(__file__) + "/test_createFileWithLayers.3dm")

    #objective: to test creating file with layers and deleting a layer
    def test_deleteLayer(self) -> None:
        file3dm = rhino3dm.File3dm()

        #create layers
        layer1 = rhino3dm.Layer()
        layer1.Name = 'layer1'
        layer1.Color = (255,0,255,255)

        layer2 = rhino3dm.Layer()
        layer2.Name = 'layer2'

        index1 = file3dm.layers.Add(layer1)
        file3dm.layers.Add(layer2)

        qtyLayers = len(file3dm.layers)

        id1 = file3dm.layers[index1].Id

        #print(id1)
        #print(type(id1))
        #print(str(id1))

        file3dm.layers.Delete(id1)

        qtyLayers2 = len(file3dm.layers)

        self.assertTrue(qtyLayers == 2 and qtyLayers2 == 1)

    def test_Add(self) -> None:
        """Test for the Add method of File3dmLayerTable.
        """
        file3dm = rhino3dm.File3dm()

        # create layer
        layer_index_0 = rhino3dm.Layer()
        # add the layer to the table the update the index accordingly
        index = file3dm.layers.Add(layer_index_0)

        l0 = file3dm.layers.FindIndex(index)

        self.assertEqual(l0.Index, 0)

    def test_ReadFileWithLayers(self) -> None:
        file = rhino3dm.File3dm.Read(dirname(__file__) + "/models/file3dm_stuff.3dm")
        qtyLayers = len(file.layers)
        self.assertTrue(qtyLayers == 6)
