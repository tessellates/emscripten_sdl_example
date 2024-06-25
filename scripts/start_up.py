import subprocess
import signal
import sys
import webbrowser
import time
import threading

server_running = True

def start_emrun(port, output_html):
    try:
        # Call emrun to start the server without opening the browser
        emrun_process = subprocess.Popen(
            ['emrun', '--port', str(port), '.'],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        print(f"emrun started, serving at http://localhost:{port}/{output_html}")

        return emrun_process
    except FileNotFoundError:
        print("emrun not found. Ensure Emscripten is installed and environment is set up.")
        sys.exit(1)

# Function to handle termination signal and shut down the server
def signal_handler(emrun_process):
    global server_running
    if server_running:
        print("Shutting down the server...")
        emrun_process.terminate()
        emrun_process.wait()
        print("Shut down server")
        server_running = False

def start_up(port, output_html):
    # Start emrun server
    emrun_process = start_emrun(port, output_html)

    # Set up signal handling to catch termination signals
    signal.signal(signal.SIGINT, lambda s, f: signal_handler(emrun_process))
    signal.signal(signal.SIGTERM, lambda s, f: signal_handler(emrun_process))
    global server_running
    # Keep the main thread running until terminated
    try:
        while server_running:
            pass
    except (KeyboardInterrupt, SystemExit):
        print("\nCtrl+C received. The server will be stopped, but the script will keep running.")
        signal_handler(emrun_process)

    print("The script continues to run. Perform any other tasks here.")