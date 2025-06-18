"""
TextLogTestSuite
-----------------

Tests for the `TextLog` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import TextLog, Point3d

# local library specific imports


class TextLogTestSuite(TestCase):
    """Tests for the `TextLog` class.
    """
    def setUp(self) -> None:
        self.text_log = TextLog()

    def test_decrease_level_of_detail(self) -> None:
        """Tests for the `decrease_level_of_detail` method.
        """
        with self.subTest(msg="Test return value"):
            self.assertEqual(
                self.text_log.decrease_level_of_detail(),
                TextLog.LevelOfDetail.Medium
        )

        with self.subTest(msg="Test updated value"):
            self.assertEqual(
                self.text_log.get_level_of_detail(),
                TextLog.LevelOfDetail.Minimum
        )

    def test_get_level_of_detail(self) -> None:
        """Test for the `get_level_of_detail` method.
        """
        self.assertEqual(
            self.text_log.get_level_of_detail(),
            TextLog.LevelOfDetail.Medium
        )

    def test_increase_level_of_detail(self) -> None:
        """Tests for the `increase_level_of_detail` method.
        """
        with self.subTest(msg="Test return value"):
            self.assertEqual(
                self.text_log.increase_level_of_detail(),
                TextLog.LevelOfDetail.Medium
        )

        with self.subTest(msg="Test updated value"):
            self.assertEqual(
                self.text_log.get_level_of_detail(),
                TextLog.LevelOfDetail.Maximum
        )

    def test_is_null(self) -> None:
        """Tests for the `is_null` method.
        """
        with self.subTest(msg="Test not null TextLog"):
            self.assertFalse(self.text_log.is_null())

        with self.subTest(msg="Test null TextLog"):
            self.assertTrue(TextLog.null().is_null())

    def test_level_of_detail_is_at_least(self) -> None:
        """Test for the `level_of_detail_is_at_least` method.
        """
        self.assertTrue(
            self.text_log.level_of_detail_is_at_least(TextLog.LevelOfDetail.Medium)
        )

    def test_null(self) -> None:
        """Test for the `null` method.
        """
        self.assertIsInstance(self.text_log.null(), TextLog)

    def test_set_level_of_detail(self) -> None:
        """Test for the `set_level_of_detail` method.
        """
        self.text_log.set_level_of_detail(TextLog.LevelOfDetail.Minimum)
        self.assertEqual(
            self.text_log.get_level_of_detail(),
            TextLog.LevelOfDetail.Minimum
        )

        #print("\n")
        #print(TextLogLevelOfDetail.Minimum)
        #print(self.text_log.print(Point3d(1,1,0)))
        #print(self.text_log.get_level_of_detail())
        #print("\n")
