"""
Type hints
----------


__author__ = "Studio W Engineers"

__version__ = "0.1.0"

__maintainer__ = "Studio W Engineers"

__email__ = "studio.w.engineers@gmail.com"

__status__ "Release"
"""
# standard library imports
from enum import Enum
from typing import Iterator
from uuid import UUID

# third party library imports

# local library specific imports


class Geometry:
    """Python wrapper for the openNURBS `ON_Geometry` class.
    """
    def __init__(self) -> None: ...

    def dimension(self) -> int:
        """Returns the dimension of the object.

        Remarks:
        The dimension is typically three. For parameter space trimming curves the
        dimension is two. In rare cases the dimension can be one or greater than three.
        """
        ...

    def is_deformable(self) -> bool:
        """Returns `True` if object can be accurately modified with "squishy"
        transformations like projections, shears, an non-uniform scaling.
        """
        ...

    def is_valid(self, text_log: TextLog | None = None) -> bool:
        """The base implementation returns `False`.
        """
        ...


class Layer:
    """Python wrapper for the openNURBS `ON_Layer` class.
    """
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...

    @property
    def color(self) -> tuple[int, int, int, int]: ...
    @color.setter
    def color(self, color: tuple[int, int, int, int]) -> None: ...

    @property
    def full_path(self) -> str: ...

    @property
    def iges_level(self) -> int: ...
    @iges_level.setter
    def iges_level(self, level: int) -> None: ...

    @property
    def index(self) -> int: ...

    @property
    def is_expanded(self) -> bool: ...
    @is_expanded.setter
    def is_expanded(self, is_expanded: bool) -> None: ...

    @property
    def is_locked(self) -> bool: ...
    @is_locked.setter
    def is_locked(self, is_locked: bool) -> None: ...

    def is_valid(self, text_log: TextLog | None = None) -> bool: ...

    @property
    def is_visible(self) -> bool: ...
    @is_visible.setter
    def is_visible(self, is_visible: bool) -> None: ...

    @property
    def layer_uuid(self) -> UUID: ...
    @layer_uuid.setter
    def layer_uuid(self, layer_uuid: UUID) -> None: ...

    @property
    def line_type_index(self) -> int: ...
    @line_type_index.setter
    def line_type_index(self, index: int) -> None: ...

    @property
    def name(self) -> str: ...
    @name.setter
    def name(self, name: str) -> None: ...

    @property
    def path_separator(self) -> str: ...

    @property
    def parent_uuid(self) -> UUID: ...
    @parent_uuid.setter
    def parent_uuid(self, parent_uuid: UUID) -> None: ...

    @property
    def parent_uuid_is_not_null(self) -> bool: ...

    @property
    def parent_uuid_is_null(self) -> bool: ...

    @property
    def persistent_locking(self) -> bool: ...
    @persistent_locking.setter
    def persistent_locking(self, persistent_locking: bool) -> None: ...

    @property
    def persistent_visibility(self) -> bool: ...
    @persistent_visibility.setter
    def persistent_visibility(self, persistent_visibility: bool) -> None: ...

    @property
    def plot_color(self) -> tuple[int, int, int, int]: ...
    @plot_color.setter
    def plot_color(self, plot_color: tuple[int, int, int, int]) -> None: ...

    @property
    def plot_weight(self) -> float: ...
    @plot_weight.setter
    def plot_weight(self, plot_weight: float) -> None: ...

    @property
    def render_material_index(self) -> int: ...
    @render_material_index.setter
    def render_material_index(self, index: int) -> None: ...


class LayerTable:
    def __getitem__(self, index: int) -> Layer:...

    def __iter__(self) -> Iterator[Layer]: ...

    def __len__(self) -> int: ...

    def add(self, layer: Layer) -> int: ...

    def count(self) -> int: ...

    def delete_by_name(self, layer_name: str) -> bool: ...

    def delete_by_uuid(self, layer_uuid: UUID) -> bool: ...

    def get_by_index(self, layer_index: int) -> Layer: ...

    def get_by_name(self, layer_name: str) -> Layer: ...

    def get_by_uuid(self, layer_uuid: UUID) -> Layer: ...

    def get_layer_index(self, full_name: str) -> int: ...

    def get_layer_uuid(self, full_name: str) -> UUID: ...

    def has(self, layer_name: str) -> bool: ...

    def max_index(self) -> int: ...


class Line:
    """Python bindings for openNURBS `ON_Line` class.
    """
    def __getitem__(self, index: int) -> Point3d: ...

    def __init__(self) -> None: ...

    def __setitem__(self, index: int, value: Point3d) -> None: ...


class Model:
    def __init__(self) -> None: ...

    def write(self, path: str, version: int = 7) -> bool: ...

    @property
    def LayerTable(self) -> LayerTable: ...

    @staticmethod
    def read(path: str) -> Model: ...

    @staticmethod
    def read_archive_version(path: str) -> int: ...

    @staticmethod
    def read_notes(path: str) -> str: ...


class OpenNURBSObject:
    """Python bindings for the openNURBS `ON_Object` class.

    `ON_Object`: pure virtual base class for all classes that must provide runtime class
    id or support object level 3DM serialization. Returns
    """
    def get_user_string(self, key: str) -> str:
        """Get the user string from the object.

        Parameters
        ----------
        key: `str`
            the key used to retrieve the user string.

        Returns
        -------
        value: `str`
            the `str` to be returned if the `key` has been found. Empty `str` is returned
            otherwise.
        """
        ...

    def is_corrupt(self, repair: bool, silent_error: bool, text_log: TextLog) -> bool:
        """Check for corrupt data values that are likely to cause crashes.

        Parameters
        ----------
        repair: `bool`
            If `True`, `const_cast<>` will be used to change the corrupt data so that
            crashes are less likely.

        silent_error: `bool`
            If `True`, ON_ERROR will not be called when corruption is detected.

        text_log: `TextLog`
            If text_log is not null, then a description of corruption is printed using
            text_log.

        Notes
        -----
        Ideally, `is_corrupt` would be a virtual function on `ON_Object`, but doing that
        at this point would break the public SDK.
        """
        ...

    def is_valid(self, text_log: TextLog | None = None) -> bool:
        """Tests an object to see if its data members are correctly initialized.

        Parameters
        ----------
        text_log: `TextLog`, optional
            If the object is not valid and `text_log` is not `None`, then a brief english
            description of the reason the object is not valid is appended to the log.
            The information appended to `text_log` is suitable for low-level debugging
            purposes by programmers and is not intended to be useful as a high level user
            interface tool.

        Returns
        -------
        `True` if the object is valid or `False` if the object is invalid, uninitialized,
        etc.
        """
        ...



    #.def("get_user_string_keys", &ON_Object::GetUserStringKeys)

    #.def("get_user_strings", &ON_Object::GetUserStrings)

    def remove_user_string(self, key: str) -> bool:
        """Remove a user string in the form of a `key`-`value` string pair from the
        object.

        Parameters
        ----------
        key: `str`
            key component of the string pair.

        Returns
        -------
        `True` if successful.
        """
        ...

    def set_user_string(self, key: str, value: str) -> bool:
        """Attach a user string in the form of a `key`-`value` string pair to the object.
        This information will persist through copy construction, operator `=`, and file IO.

        Parameters
        ----------
        key: `str`
            key component of the string pair.

        value: `str`
            value component of the string pair.

        Returns
        -------
        `True` if successful.
        """
        ...

    #.def("set_user_strings", &ON_Object::SetUserStrings)

    def user_string_count(self) -> int:
        """Returns the number of user strings on the object.
        """
        ...


class PointGeometry(Geometry):
    """Python wrapper for the openNURBS `ON_Point` class.
    """
    def __init__(self) -> None: ...


class Point3d:
    """Python wrapper for the openNURBS `ON_3dPoint` class.
    """
    def __add__(self, other: Point3d) -> Point3d: ...

    def __eq__(self, other: object) -> bool: ...

    def __init__(self, x: float, y: float, z: float) -> None: ...

    def __mul__(self, other: float) -> Point3d: ...

    def __ne__(self, other: object) -> bool: ...

    @property
    def x(self) -> float: ...
    @x.setter
    def x(self, value: float) -> None: ...

    @property
    def y(self) -> float: ...
    @y.setter
    def y(self, value: float) -> None: ...

    @property
    def z(self) -> float: ...
    @z.setter
    def z(self, value: float) -> None: ...

    def distance_to(self, point: Point3d) -> float: ...

    def is_coincident(self, point: Point3d) -> bool: ...


class TextLog:
    """Python bindings for openNURBS `ON_TextLog` class.
    """
    def __init__(self) -> None: ...

    def decrease_level_of_detail(self) -> LevelOfDetail:
        """Decrease the level of detail.

        Returns
        -------
        LevelOfDetail
            Level of detail to restore when this scope of decreased detail is finished.
        """
        ...

    def get_level_of_detail(self) -> LevelOfDetail:
        """Returns the level of detail.

        Returns
        -------
        LevelOfDetail
            Level of detail to print.
        """
        ...

    def increase_level_of_detail(self) -> LevelOfDetail:
        """Increase the level of detail.

        Returns
        -------
        LevelOfDetail
            Level of detail to restore when this scope of increased detail is finished.
        """
        ...

    def is_null(self) -> bool:
        """Returns `True` if this `TextLog` is `ON_TextLog::Null`.
        """
        ...

    def set_level_of_detail(self, level: LevelOfDetail) -> None:
        """Sets the level of detail.
        """
        ...

    @staticmethod
    def null() -> TextLog:
        """`ON_TextLog::Null` is a silent `TextLog` and can be used when no output is
        desired but an `ON_TextLog` parameter is required.
        """
        ...

    class LevelOfDetail(Enum):
        """`ON_TextLog::LevelOfDetail` determines how much detail is printed. Functions
        that have an `ON_TextLog` parameter, like the `dump` functions, may use the level
        of detail to tailor their output.
        """
        Minimum = 0

        Medium = 1

        Maximum = 2
