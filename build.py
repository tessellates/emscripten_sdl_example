#!/usr/bin/python3
import scripts.virtual_env_tools as vtool
import scripts.env_tools as et
import os
import platform
import argparse
import subprocess
import shutil
from contextlib import contextmanager

profiles = {"Darwin":'MacosProfile.txt', "Windows":'WindowsProfile.txt', "Linux":'LinuxProfile.txt'}
build_type = 'Debug'

@contextmanager
def cwd(path):
    oldpwd = os.getcwd()
    os.chdir(path)
    try:
        yield
    finally:
        os.chdir(oldpwd)

def copy_files(src, dest):
    if not os.path.exists(src):
        print(f"Source directory {src} does not exist.")
        return
    if not os.path.exists(dest):
        os.makedirs(dest)
        print(f"Created destination directory {dest}")
    for filename in os.listdir(src):
        src_file = os.path.join(src, filename)
        dest_file = os.path.join(dest, filename)
        shutil.copy(src_file, dest_file)
        print(f"Copied {src_file} to {dest_file}")

def main(setup = True, emscripten=False):
    venv_context = vtool.VenvContext("kai_o_venv")
    os.environ['REPO_DIR'] = os.getcwd()
    if setup:
        vtool.create_venv(venv_context)
    if setup:
        vtool.initialize_venv(venv_context, os.path.join('data', 'requirements.txt'))

    profile = 'default'
    hostprofile = profile
    if emscripten:
        hostprofile = os.path.join('data', 'emprofile')

    if setup:
        try:
            venv_context.run_command('conan', 'profile', 'detect')
        except: 
            pass

        venv_context.run_command('conan', 'install', '.', '-of=build', '-s', f'build_type={build_type}', '--build=missing', f"-pr:b={profile}", f"-pr:h={hostprofile}")

    venv_context.run_command('conan', 'build', '.',  '-of=build', '-s', f'build_type={build_type}', f"-pr:b={profile}", f"-pr:h={hostprofile}")
    process = None
    if platform.system() == 'Darwin':
        et.append_os_env('build/build/Debug/generators/conanbuildenv-debug-wasm.sh')
        with cwd('runtime'):
            process = subprocess.run(['emrun', '--no_browser', '--port', '8080', '.'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    return
    if platform.system() == 'Windows':
        subprocess.check_call([os.path.join('install', 'run', 'main.exe')])
    else:
        subprocess.check_call(['./build/build/Release/bin/main'])

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('-bo', action='store_true', help='Execute "conan create"')
    parser.add_argument('-em', action='store_true', help='Execute "conan create"')
    argsparsed = parser.parse_args()
    main(not argsparsed.bo, argsparsed.em)
