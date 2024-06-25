import subprocess

def run_env_and_command(env_script, command):
    # Construct the command to source the env_script and then execute the command
    full_command = f"source {env_script} && {command}"
    
    # Run the command in a shell
    process = subprocess.Popen(full_command, shell=True, executable='/bin/bash', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    # Capture the output and error
    stdout, stderr = process.communicate()

    # Print the output and error
    print("Output:")
    print(stdout.decode('utf-8'))

    print("Error:")
    print(stderr.decode('utf-8'))

    # Return the exit code
    return process.returncode

def append_os_env(sh_file):
    import re
    import os
    with open(sh_file, 'r') as sh_script:
        # Parse the script and set the environment variables
        for line in sh_script:
            if line.startswith("export"):
                key_value = re.match(r'export (\w+)=(.*)', line)
                if key_value:
                    key = key_value.group(1)
                    value = key_value.group(2).strip('"')
                    
                    if key in os.environ:
                        # Append the new value to the existing value
                        os.environ[key] += f':{value}'
                        print(f'Appended {value} to {key}, now {key}={os.environ[key]}')
                    else:
                        # Set the new value if the key does not exist
                        os.environ[key] = value
                        print(f'Set {key}={value}')
                        