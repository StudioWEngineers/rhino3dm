"""
ModelTestSuite
--------------

Tests for the `Model` class.


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from unittest import TestCase

# third party library imports
from rhino3dm import Model

# local library specific imports


class NewModelTestSuite(TestCase):
    """Tests for the `Model` class.
    """
    def setUp(self) -> None:
        self.model = Model()

    def test_application_details(self) -> None:
        """Tests for the `application_details` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.application_details, "")

        self.model.application_details = "custom string"

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.application_details, "custom string")

    def test_application_name(self) -> None:
        """Tests for the `application_name` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.application_name, "")

        self.model.application_name = "custom string"

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.application_name, "custom string")

    def test_application_url(self) -> None:
        """Tests for the `application_url` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.application_url, "")

        self.model.application_url = "custom string"

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.application_url, "custom string")

    def test_archive_version(self) -> None:
        """Tests for the `archive_version` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.archive_version, 0)

        self.model.archive_version = 7

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.archive_version, 7)

    def test_created_by(self) -> None:
        """Tests for the `created_by` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.created_by, "")

        self.model.created_by = "StudioWEngineers"

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.created_by, "StudioWEngineers")

    def test_last_edited_by(self) -> None:
        """Tests for the `last_edited_by` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.last_edited_by, "")

        self.model.last_edited_by = "StudioWEngineers"

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.last_edited_by, "StudioWEngineers")

    def test_revision(self) -> None:
        """Tests for the `revision` property.
        """
        with self.subTest(msg="Before assignment"):
            self.assertEqual(self.model.revision, 0)

        with self.subTest(msg="Assignment"):
            self.assertEqual(self.model.new_revision(), 1)

        with self.subTest(msg="After assignment"):
            self.assertEqual(self.model.revision, 1)
