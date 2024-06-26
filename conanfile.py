from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, CMakeDeps
import os

class Emex(ConanFile):
    name = "emex"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"emscripten": [True, False]}
    default_options = {"emscripten": False}

    def requirements(self):
        #self.requires("sdl/2.30.3")
        self.requires("sdl_image/2.6.3", options={"shared": False})
        self.requires("sdl_ttf/2.22.0", options={"shared": False})
        self.requires("glm/cci.20230113")
        if self.options.emscripten:
            self.tool_requires("emsdk/3.1.50")
        self.tool_requires("cmake/[>=3.25]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        install_dir = os.environ['REPO_DIR']
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        self.run(f"cmake --install . --prefix={install_dir} --config {self.settings.build_type}")
