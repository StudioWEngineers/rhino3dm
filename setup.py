import os
import sys
import subprocess as sp
import glob
import shutil
import struct
from typing import List
from pathlib import Path
from setuptools import setup, find_packages, Extension
from setuptools.command.build_ext import build_ext

pyexec = Path(sys.executable).resolve()

print(f"Using Python executable: {pyexec}")

def system(cmd : List, **kwargs):
    print(f"Running {' '.join(cmd)}")
    if "cwd" in kwargs.keys():
        print(f"Using 'cwd'={kwargs['cwd']}")
    try:
        cmd_out = sp.run(cmd, encoding='utf-8', check=True, stdout=sp.PIPE, stderr=sp.PIPE, **kwargs)
    except sp.CalledProcessError as e:
        print(e.stderr)
        print(e.output)
        raise RuntimeError(f"Command execution failed.\n\n{e.stderr}\n\n{e.output}")
    print(cmd_out.stdout)


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = sp.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            self.build_extension(ext)

        if self.inplace:
            self.copy_extensions_to_source()

    def build_extension(self, ext):
        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())
        build_dir = Path(self.build_temp).resolve()
        build_dir.mkdir(parents=True, exist_ok=True)
        draco_static_dir = build_dir / "draco_static"
        draco_static_dir.mkdir(parents=True, exist_ok=True)
        draco_src_dir = Path(ext.sourcedir) / "src" / "lib" / "draco"
        build_temp_dir = Path(self.build_temp).resolve()

        current_dir = Path.cwd()

        bitness = 8 * struct.calcsize("P")
        osplatform = "win32" if bitness == 32 else "x64"


        command = ['cmake', '-A', osplatform, "-DPYTHON_BINDING_LIB=NANOBIND", f"{draco_src_dir}"]
        system(command, cwd=draco_static_dir)
        system(["cmake", "--build", ".", "--config", "Release"], cwd=draco_static_dir)

        command = ['cmake', '-A',
                    f"{osplatform}",
                    f'-DPYTHON_EXECUTABLE:FILEPATH={pyexec}',
                    "-DPYTHON_BINDING_LIB=NANOBIND",
                    ext.sourcedir+"/src"]
        system(command, cwd=build_temp_dir)

        _rhino3dmvcxproj = build_temp_dir / "_rhino3dm.vcxproj"
        opennurbs_staticvcxproj = build_temp_dir / "opennurbs_static.vcxproj"
        _rhino3dmvcxproj.write_text(_rhino3dmvcxproj.read_text().replace("WIN32;", "WIN64;"))
        opennurbs_staticvcxproj.write_text(opennurbs_staticvcxproj.read_text().replace("WIN32;", "WIN64;"))
        system(["cmake","--build",".", "--config","Release","--target","_rhino3dm"], cwd=build_temp_dir)

        os.chdir(current_dir)
        if not os.path.exists(self.build_lib + "/rhino3dm"):
            os.makedirs(self.build_lib + "/rhino3dm")
        for file in glob.glob(self.build_temp + "/Release/*.pyd"):
            shutil.copy(file, self.build_lib + "/rhino3dm")
        for file in glob.glob(self.build_temp + "/*.so"):
            shutil.copy(file, self.build_lib + "/rhino3dm")
        print()  # Add an empty line for cleaner output


setup(
    name='rhino3dm',
    version='8.17.1',
    author='Robert McNeel & Associates',
    author_email='steve@mcneel.com',
    description='Python library based on OpenNURBS with a RhinoCommon style',
    long_description=
"""# rhino3dm.py
CPython package based on OpenNURBS with a RhinoCommon style

""",
    long_description_content_type="text/markdown",
    packages=find_packages('src'),
    package_dir={'': 'src'},
    ext_modules=[CMakeExtension('rhino3dm._rhino3dm')],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
    include_package_data=True
)
