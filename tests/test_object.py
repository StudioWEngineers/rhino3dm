"""
OpenNURBSObjectTestSuite
------------------------

Tests for the `OpenNURBSObject` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import OpenNURBSObject, TextLog

# local library specific imports


class OpenNURBSObjectTestSuite(TestCase):
    """Tests for the `OpenNURBSObject` class.
    """
    def setUp(self) -> None:
        self.obj = OpenNURBSObject()

    def test_get_user_string(self) -> None:
        """Test for the `get_user_string` method.
        """
        self.assertEqual(self.obj.get_user_string("not existing key"), "")

    def test_is_corrupt(self) -> None:
        """Test for the `is_corrupt` method.
        """
        self.assertFalse(self.obj.is_corrupt(False, True, TextLog.null()))

    def test_is_valid(self) -> None:
        """Tests for the `is_valid` method.
        """
        with self.subTest("Test with default argument"):
            self.assertTrue(self.obj.is_valid())

        with self.subTest("Test with explicit None argument"):
            self.assertTrue(self.obj.is_valid(None))

        with self.subTest("Test with explicit TextLog argument"):
            self.assertTrue(self.obj.is_valid(TextLog.null()))

    def test_remove_user_string(self) -> None:
        """Tests for the `remove_user_string` method.
        """
        with self.subTest(msg="Unsuccessful removal"):
            self.assertFalse(self.obj.remove_user_string("new key"))

        self.obj.set_user_string("new key", "1")

        with self.subTest(msg="Successful removal"):
            self.assertTrue(self.obj.remove_user_string("new key"))

        with self.subTest(msg="Successful removal"):
            self.assertFalse(self.obj.get_user_string("new key"))

    def test_set_user_string(self) -> None:
        """Tests for the `set_user_string` method.
        """
        with self.subTest(msg="Successful assignment"):
            self.assertTrue(self.obj.set_user_string("new key", "1"))

        with self.subTest(msg="Successful retrievement"):
            self.assertEqual(self.obj.get_user_string("new key"), "1")

    def test_user_string_count(self) -> None:
        """Tests for the `user_string_count` method.
        """
        with self.subTest(msg="Before any assignment"):
            self.assertEqual(self.obj.user_string_count(), 0)

        self.obj.set_user_string("new key", "1")

        with self.subTest(msg="After 1st assignment"):
            self.assertEqual(self.obj.user_string_count(), 1)
