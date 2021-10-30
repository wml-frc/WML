# Contributing to WML

- WML is free [MIT](LICENSE) licensed software for the use of the public, developed by the public.

- Templates for Pull Requesting and creating issues are native to this project for contributing.

## Project Setup

- WML wraps around WPIlib and requires the same installments.

### All Platforms
1. Follow the guide for installing wpilibsuite https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html. Be aware of the version you install, as it must be the same as the version for this project, (E.g, `2021.3.1`)

- Note, this is not required if you already have a compiler (VisualCpp/Clang/Gcc) & Java already installed as gradle will download the necessary dependencies for you

### Windows
1. Download Java (JDK 11 for best support https://www.oracle.com/java/technologies/javase-jdk11-downloads.html)


2. "Desktop development with C++" from VS required for local debugging and simulation support https://visualstudio.microsoft.com/downloads/

3. After this is complete you can clone the project recursivly to grab the submodules needed for this project. `git clone --recurse-submodules https://github.com/wml-frc/WML.git`

### Linux
1. Linux requires the build-essentials (GCC, CMake, etc...)

2. After this is complete you can clone the project recursivly to grab the submodules needed for this project. `git clone --recurse-submodules https://github.com/wml-frc/WML.git`

### Mac
1. Download Xcode from the app store https://apps.apple.com/au/app/xcode/id497799835?mt=12

2. After this is complete you can clone the project recursivly to grab the submodules needed for this project. `git clone --recurse-submodules https://github.com/wml-frc/WML.git`

## Project Install/Build

1. Next we will need to download the roborio toolchain to cross compile the program for linuxathena. (All code in this project by a minimum must compile linuxathena)
	- Navigate to the root directory of this project and run `./gradlew installRoboRioToolchain`

2. Build the project
	- Run `./gradlew build` to build and compile all gradle projects
	- (Note: you can run `./gradlew <PROJECT>:build` to build a single project)

3. Inside each projects `build.gradle` (I.e [build.gradle](WML-Core/build.gradle)) consists of options on how that project should compile. If desktop support is disabled then the project will only compile and publish shared and static linuxathena builds. If enabled, the project will build for both linuxathena and the current platform. I.e `windowsx86-64` & `linuxathena`.


## Publishing

1. The project compiles binaries, source files and header files for supporting platforms. This is then eventually sent to the maven repository for release. To test publishing run `./gradlew publish`. This will publish supporting platforms in .zip formats to [maven](build/maven) inside our build directory. 

2. Running with options e.g `./gradlew publish -PazureBuild` will publish as if it's running on azure, for certain platforms this enables and disables options.

3. Running with option `-PmasterPublish` will also publish documentation to our local [maven](build/maven) directory.

4. Release publish. Azure will automatically compile and build each project for every platform and provide the required outputs before publishing to the maven repository. Release publish will run only for the master branch (pull requests to the master branch will not run this function). For all other branches and PR's, azure will build, compile and test without publishing.