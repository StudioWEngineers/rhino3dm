# setup.py
# created: January 15, 2020
#
# Uses the CMake (https://cmake.org) tools to generate the platform-specific rhino3dm projects
# See related scripts in this folder for other steps in the process.
#
# This script is inspired by - but deviates from - the "Scripts To Rule Them All" pattern:
# https://github.com/github/scripts-to-rule-them-all

import subprocess
import sys
import os
import argparse
from sys import platform as _platform
import shlex
import shutil
import fileinput
from importlib.machinery import SourceFileLoader
import time

# ---------------------------------------------------- Globals ---------------------------------------------------------

xcode_logging = False
verbose = False
overwrite = False
popen_shell_mode = False
valid_platform_args = ["windows", "python"]
platform_full_names = {'windows':'Windows'}
script_folder = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
src_folder = os.path.abspath(os.path.join(script_folder, "..", "src"))
build_folder = os.path.abspath(os.path.join(src_folder, "build"))
librhino3dm_native_folder = os.path.abspath(os.path.join(src_folder, "librhino3dm_native"))

bootstrap = SourceFileLoader('bootstrap', os.path.join(script_folder, "bootstrap.py")).load_module()

# ---------------------------------------------------- Logging ---------------------------------------------------------
# colors for terminal reporting
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def print_warning_message(warning_message):
    warning_prefix = " warning: "
    if xcode_logging:
        print(warning_prefix + warning_message)
    else:
        print(bcolors.BOLD + bcolors.FAIL + warning_prefix.upper() + bcolors.ENDC + bcolors.FAIL + warning_message +
              bcolors.ENDC)


def print_error_message(error_message):
    error_prefix = " error: "
    if xcode_logging:
        print(error_prefix + error_message)
    else:
        print(bcolors.BOLD + bcolors.FAIL + error_prefix.upper() + bcolors.ENDC + bcolors.FAIL + error_message +
              bcolors.ENDC)


def print_ok_message(ok_message):
    ok_prefix = " ok: "
    if xcode_logging:
        print(ok_prefix + ok_message)
    else:
        print(bcolors.BOLD + bcolors.OKBLUE + ok_prefix.upper() + bcolors.ENDC + bcolors.OKBLUE + ok_message +
              bcolors.ENDC)


# ------------------------------------------------ Command Runner ------------------------------------------------------

def run_command(command, suppress_errors=False):
    print(command)
    verbose = True #we don't yet have a command-line switch for this, if we ever need one.
    if suppress_errors:
        dev_null = open(os.devnull, 'w')
        stderr = dev_null
    else:
        stderr = subprocess.PIPE

    if _platform == "win32" or _platform == "win64":
            process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=stderr)
    else:
            process = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE, stderr=stderr)

    while True:
        line = process.stdout.readline()
        if process.poll() is not None and not line:
            break
        if line:
            if verbose:
                line = line.decode('utf-8').strip()
                print(line)
        elif not suppress_errors:
            error = process.stderr.readline()
            if error:
                error = error.decode('utf-8').strip()
                print_error_message(error)
                delete_cache_file()
                sys.exit(1)
            else:
                continue

    rc = process.poll()
    return rc


# ---------------------------------------------- Platform Setup --------------------------------------------------------
def print_platform_preamble(platform_target_name):
    print("")
    if xcode_logging:
        print("Setting up " + platform_target_name + "...")
    else:
        print(bcolors.BOLD + "Setting up " + platform_target_name + "..." + bcolors.ENDC)


def check_or_create_path(target_path):
    try:
        if not os.path.exists(target_path):
            os.mkdir(target_path)
    except:
        return ''

    return target_path


def overwrite_check(item_to_check):
    if os.path.exists(item_to_check):
        if not overwrite:
            print_warning_message("A configuration already appears in " + item_to_check +
                                  ". Use --overwrite to replace.")
            return False
        if overwrite:
            if os.path.isfile(item_to_check):
                os.remove(item_to_check)
            if os.path.isdir(item_to_check):
                shutil.rmtree(item_to_check)
                time.sleep(2) # avoid any race-conditions with large folders
            return True
    else:
        return True


def setup_did_succeed(item_to_check):
    if os.path.exists(item_to_check):
        print_ok_message("successfully wrote: " + item_to_check)
        return True
    else:
        print_error_message("failed to configure and generate " + item_to_check)
        return False


def build_methodgen():
    if xcode_logging:
        print(" Building MethodGen...")
    else:
        print(bcolors.BOLD + " Building MethodGen..." + bcolors.ENDC)

    path_to_methodgen_csproj = os.path.abspath(os.path.join(src_folder, 'methodgen', 'methodgen.csproj'))

    # On Linux and macOS, we compile methodgen with dotnet core SDK
    if _platform == "linux" or _platform == "linux2" or _platform == "darwin":
        methodgen_build_dir = check_or_create_path(os.path.abspath(os.path.join(build_folder, "methodgen")))
        methodgen_src_path = os.path.abspath(os.path.join(src_folder, 'methodgen'))
        src_files = os.listdir(methodgen_src_path)
        for file_name in src_files:
            if file_name.endswith('.cs') or file_name.endswith('csproj'):
                full_path = os.path.abspath(os.path.join(methodgen_src_path, file_name))
                if os.path.isfile(full_path):
                    shutil.copy(full_path, methodgen_build_dir)
        command = "dotnet build " + methodgen_build_dir
        run_command(command)

        item_to_check = os.path.join(methodgen_build_dir, "bin", "Debug", "MethodGen.dll")
    else:
        msbuild_path = 'msbuild'
        # On Windows, call bootstrap to get msbuild's path and flip the path separators to appease run_command()
        if _platform == "win32" or _platform == "win64":
            build_tools = bootstrap.read_required_versions()
            msbuild_path = bootstrap.check_msbuild(build_tools["msbuild"]).replace('\\', '//')
            path_to_methodgen_csproj = path_to_methodgen_csproj.replace('\\', '//')

        command = msbuild_path + ' ' + path_to_methodgen_csproj +' /t:restore,build /p:RestorePackagesConfig=true /p:Configuration=Release'
        #print(command)
        run_command(command)

        # Check to see if the MethodGen.exe was written...
        item_to_check = os.path.abspath(os.path.join(src_folder, 'MethodGen.exe'))

    if os.path.exists(item_to_check):
        print_ok_message("successfully built: " + item_to_check)
    else:
        print_error_message("failed to build " + item_to_check)

    return True


def run_methodgen():
    if xcode_logging:
        print(" Running MethodGen...")
    else:
        print(bcolors.BOLD + " Running MethodGen..." + bcolors.ENDC)

    path_to_cpp = librhino3dm_native_folder
    path_to_cs = os.path.abspath(os.path.join(src_folder, 'dotnet'))
    # On Windows, we need to flip the path separators to appease run_command()
    if _platform == "win32" or _platform == "win64":
        path_to_cpp = path_to_cpp.replace('\\', '//')
        path_to_cs = path_to_cs.replace('\\', '//')
    path_to_replace = '../lib/opennurbs'
    item_to_check = os.path.abspath(os.path.join(path_to_cs, 'AutoNativeMethods.cs'))

    # On Linux, we execute methodgen with dotnet core SDK
    if _platform == "linux" or _platform == "linux2" or _platform == "darwin":
        methodgen_build_dir = check_or_create_path(os.path.abspath(os.path.join(build_folder, "methodgen")))
        path_to_methodgen_executable = os.path.join(methodgen_build_dir, "methodgen.csproj")
        if not os.path.exists(path_to_methodgen_executable):
            print_error_message(path_to_methodgen_executable + " not found.")
            return False

        command = 'dotnet run --no-build --project '
    else:
        path_to_methodgen_executable = os.path.abspath(os.path.join(src_folder, "MethodGen.exe"))
        # On Windows, we need to flip the path separators to appease run_command()
        if _platform == "win32" or _platform == "win64":
            path_to_methodgen_executable = path_to_methodgen_executable.replace('\\', '//')

        if not os.path.exists(path_to_methodgen_executable):
            print_error_message("MethodGen.exe not found.")
            return False

        command = ''
        if _platform == "darwin":
            command = command + 'mono '

    # remove any older file there...
    if os.path.exists(item_to_check):
        os.remove(item_to_check)

    command = command + path_to_methodgen_executable + " " + path_to_cpp + " " + path_to_cs + " " + path_to_replace + " rhino3dm"
    #print("--------------------")
    #print(command)
    run_command(command)

    # Check to see if methodgen succeeded
    if os.path.exists(item_to_check):
        print_ok_message("successfully generated: " + item_to_check)
    else:
        print_error_message("failed to generate " + item_to_check)
        return False

    return True


def setup_windows():
    if _platform != "win32" and _platform != "win64":
        print_error_message("Generating project file for Windows requires that you run this script on Windows")
        return False

    global librhino3dm_native_folder

    # 32 bit version...
    target_path = check_or_create_path(os.path.join(build_folder, platform_full_names.get("windows").lower()))
    target_path = check_or_create_path(os.path.join(build_folder, platform_full_names.get("windows").lower(), "win32"))
    target_file_name = "librhino3dm_native.vcxproj"

    item_to_check = os.path.abspath(os.path.join(target_path, target_file_name))
    if not overwrite_check(item_to_check):
        return False

    os.chdir(target_path)

    # generate the project files
    print("")
    if xcode_logging:
        print("Generating vcxproj files for Windows 32-bit native build...")
    else:
        print(bcolors.BOLD + "Generating vcxproj files for Windows 32-bit native build..." + bcolors.ENDC)
    librhino3dm_native_folder = librhino3dm_native_folder.replace('\\', '//')
    command = ("cmake -G \"Visual Studio 17 2022\" -Tv142 -A Win32 " + librhino3dm_native_folder)
    run_command(command)

    # 64 bit version...
    target_path = check_or_create_path(os.path.join(build_folder, platform_full_names.get("windows").lower(), "win64"))
    target_file_name = "librhino3dm_native.vcxproj"

    item_to_check = os.path.abspath(os.path.join(target_path, target_file_name))
    if not overwrite_check(item_to_check):
        return False

    os.chdir(target_path)

    # generate the project files
    print("")
    if xcode_logging:
        print("Generating vcxproj files for Windows 64-bit native build...")
    else:
        print(bcolors.BOLD + "Generating vcxproj files for Windows 64-bit native build..." + bcolors.ENDC)
    librhino3dm_native_folder = librhino3dm_native_folder.replace('\\', '//')
    command = ("cmake -G \"Visual Studio 17 2022\" -Tv142 -A x64 " + librhino3dm_native_folder)
    run_command(command)

    # Munge the project file to support 64 bit
    for line in fileinput.input("librhino3dm_native.vcxproj", inplace=1):
        print(line.replace("WIN32;", "WIN64;"))
    #TODO: [dan]: it is unclear how opennurbs_static.vcxproj is generated
    #build_dotnet.py fails in the same way
    #for line in fileinput.input("opennurbs_static.vcxproj", inplace=1):
    #   print(line.replace("WIN32;", "WIN64;"))

    # methogen
    if not lib:
        build_methodgen()
        run_methodgen()

    return setup_did_succeed(item_to_check)

def setup_handler(platform_target):
    if not os.path.exists(build_folder):
        os.mkdir(build_folder)

    did_succeed = []

    if platform_target == "all":
        for target in valid_platform_args:
            print_platform_preamble(platform_full_names.get(target))
            rv = getattr(sys.modules[__name__], 'setup_' + target)()
            did_succeed.append(rv)
    else:
        print_platform_preamble(platform_full_names.get(platform_target))
        rv = getattr(sys.modules[__name__], 'setup_' + platform_target)()
        did_succeed.append(rv)

    return all(item == True for (item) in did_succeed)


def delete_cache_file():
    # delete the bootstrapc cache file
    path_to_bootstrapc_file = os.path.join(script_folder, "bootstrap.pyc")
    if os.path.exists(path_to_bootstrapc_file):
        os.remove(path_to_bootstrapc_file)


# --------------------------------------------------- Main -------------------------------------------------------------
def main():
    global valid_platform_args

    # cli metadata
    description = "generate the project files for rhino3dm"
    epilog = "supported platforms: " + ", ".join(valid_platform_args)

    # Parse arguments
    parser = argparse.ArgumentParser(description=description, epilog=epilog)
    parser.add_argument('--platform', '-p', metavar='<platform>', nargs='+',
                        help="generates the project files for the platform(s) specified. valid arguments: all, "
                             + ", ".join(valid_platform_args) + ".")
    parser.add_argument('--verbose', '-v', action='store_true',
                        help="show verbose logging messages")
    parser.add_argument('--overwrite', '-o', action='store_true',
                        help="overwrite existing configurations (if found)")
    parser.add_argument('--xcodelog', '-x', action='store_true',
                        help="generate Xcode-compatible log messages (no colors or other Terminal-friendly gimmicks)")
    parser.add_argument('--debug', '-d', action='store_true',
                        help="generate a debug build (wasm only)")
    parser.add_argument('--module', '-m', action='store_true',
                        help="generate a ES6 module build (wasm only)")
    parser.add_argument('--library', '-l', action='store_true',
                        help="skip building and running .net projects (methodgen). Useful for generating librhino3dm_native in release workflow")

    args = parser.parse_args()

    # User has not entered any arguments...
    if len(sys.argv) == 1:
        parser.print_help(sys.stderr)
        delete_cache_file()
        sys.exit(1)

    global xcode_logging
    xcode_logging = args.xcodelog

    global popen_shell_mode
    if _platform == "win32" or _platform == "win64":
        xcode_logging = True
        popen_shell_mode = True

    global verbose
    verbose = args.verbose

    global overwrite
    overwrite = args.overwrite

    global debug
    debug = args.debug

    global module
    module = args.module

    global node
    node = False
    if "nodejs" in args.platform:
        node = True

    global lib
    lib = args.library

    os.chdir(script_folder)

    # setup platform(s)
    did_succeed = []
    if args.platform is not None:
        for platform_target in args.platform:
            if (platform_target != "all") and (platform_target not in valid_platform_args):
                print_error_message(platform_target + " is not a valid platform argument. valid tool arguments: all, "
                                    + ", ".join(valid_platform_args) + ".")
                delete_cache_file()
                sys.exit(1)
            rv = setup_handler(platform_target)
            did_succeed.append(rv)

    delete_cache_file()

    sys.exit(0) if all(item == True for (item) in did_succeed) else sys.exit(1)


if __name__ == "__main__":
    main()
