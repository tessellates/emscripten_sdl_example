#!/usr/bin/python3
from scripts import script_utils
import os
import platform
import argparse
import subprocess

profiles = {"Darwin":'MacosProfile.txt', "Windows":'WindowsProfile.txt', "Linux":'LinuxProfile.txt'}
build_type = 'Debug'

def main(setup = True, emscripten=False, runonly=True):
    venv_context = script_utils.VenvContext("emex_venv")
    os.environ['REPO_DIR'] = os.getcwd()
    
    if not runonly:
        if setup:
            script_utils.create_venv(venv_context)
        if setup:
            script_utils.initialize_venv(venv_context, os.path.join('data', 'requirements.txt'))

        profile = 'default'
        hostprofile = profile
        if emscripten:
            profile_path = os.path.join('data', 'emprofile')
            if not os.path.exists(profile_path):
                script_utils.generate_emscripten_profile(profile_path)
            hostprofile = profile_path

        if setup:
            try:
                venv_context.run_command('conan', 'profile', 'detect')
            except: 
                pass
            
            command_args = ['install', '.', '-of=build', '-s', f'build_type={build_type}', '--build=missing', f"-pr:b={profile}", f"-pr:h={hostprofile}"]
            if emscripten:
                command_args += ['-o', 'emscripten=True']
            venv_context.run_command('conan', *command_args)

        venv_context.run_command('conan', 'build', '.',  '-of=build', '-s', f'build_type={build_type}', f"-pr:b={profile}", f"-pr:h={hostprofile}")
    
    if emscripten:
        script_utils.append_os_env(script_utils.get_conan_env_file('build', build_type))
        with script_utils.cwd('runtime'):
            script_utils.start_up(8000, 'index.html')

    else:
        if platform.system() == 'Windows':
            subprocess.check_call([os.path.join('install', 'run', 'main.exe')])
        else:
            subprocess.check_call([f'./build/bin/emex'])
    print('-- end build script --')
    return
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('-ns', action='store_true', help='no setup')
    parser.add_argument('-em', action='store_true', help='enable emscripten -- compile wasm, js and html file instead of binary')
    parser.add_argument('-ro', action='store_true', help='run only -- launches your application')
    argsparsed = parser.parse_args()
    main(not argsparsed.ns, argsparsed.em,  argsparsed.ro)
