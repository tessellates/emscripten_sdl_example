# Emscripten SDL2 Example Project

This project provides an example of how to set up and use Emscripten with SDL2. It includes instructions for building and running the project in a web browser.

## Prerequisites

Before you start, make sure you have Python 3 installed.

## Setting Up the Project

### 1. Clone the Repository

```bash
git clone https://github.com/tessellates/emscripten_sdl_example
cd emscripten-sdl2-example
```


### 2. Build the Project

The build.py script is used to build the project. It supports several command-line arguments:
- `-ns, --no-setup`: Skip setup.
- `-em, --emscripten`: Enable Emscripten — compile to WebAssembly, JavaScript, and HTML file instead of a binary.
- `-ro, --run-only`: Run only — launches your application.
- `-cb, --clean-build`: Perform a clean build.

If you want to build with emscripten you type:
```bash 
python3 build.py --emscripten
```
or  on windows
```console
py build.py --emscripten
```
This is expected to take over 30 minutes the first time you run this. Because it is installing a lot of things. If emscripten doesn't work, you might need to install clang. However it should be shipped with emscripten.
### 3. Appendix
You need to clean the build if switch between emscripten/not emscripten. 