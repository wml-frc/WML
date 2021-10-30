<p align="center">
  <img src="https://avatars1.githubusercontent.com/u/58220426?s=200&v=4" alt=""/>
</p>



## A modularity-based library designed for use in the FIRST Robotics Competition.

### Build Status
[![Build Status](https://dev.azure.com/ConnorBuchel0890/WML/_apis/build/status/wml-frc.WML?branchName=master)](https://dev.azure.com/ConnorBuchel0890/WML/_build/latest?definitionId=7&branchName=master)

## WML As FRC Vendor
- WML Supports being included as a shared library.

- Follow the documentation provided by FRC for adding 3rd party libraries https://docs.wpilib.org/pt/latest/docs/software/vscode-overview/3rd-party-libraries.html.

- The vendordep JSON files come in multiple parts and all are optional. E.g `WML-Core` for the core components. `WML-Rev` for Rev support (Neo Motor's). And `UDP_TransferNT`, used for point to point networking with UDP. Mainly used for communications to and from [CJ-Vision](https://github.com/wml-frc/CJ-Vision) platforms.

- JSON URLS
	- WML-Core: http://buchel.family/repository/wml/first/WML-Core/WML-Core-Deps/latest/WML-Core-Deps-latest.json
	- WML-Rev: http://buchel.family/repository/wml/first/WML-Rev/WML-Rev-Deps/latest/WML-Rev-Deps-latest.json
	- UDP_TransferNT: http://buchel.family/repository/wml/first/UDP_TransferNT/UDP_TransferNT-Deps/latest/UDP_TransferNT-Deps-latest.json

- Replace both occurrences of `latest` with a version for a specific version. E.g http://buchel.family/repository/wml/first/WML-Core/WML-Core-Deps/2021.3.1/WML-Core-Deps-2021.3.1.json

- Note that when adding the vendordeps through vscode it must be `http` not `https`. As this may cause security issues on some devices. If downloading manually by placing the vendordep json into the `vendordep` folder then this does not apply.

## WML As Submodule

### Setting up WML in your own project
- First you will need to 'install' the submodule to your root directory. Navigate to your root dir and install via `git submodule add https://github.com/wml-frc/WML.git`.

- Once complete you will need to apply the project to your own codebase. Every team has their own style of programming, building & deploying. But in general most will have a `build.gradle` and `settings.gradle`, and you would apply the library via appending the two.

### Adding WML to your project's gradle config

- First we need to link the directories in `settings.gradle`
- WML currently consists of two section (`WML-Core` & `WML-Rev`) and may soom be seperated further for efficiency.
```gradle
// WML
include 'WML-Core', 'WML-Rev'
project(':WML-Core').projectDir = file('WML/WML-Core')
project(':WML-Rev').projectDir = file('WML/WML-Rev')
```

- Inside your project file (e.g. `build.gradle`) append the libraries:
```gradle

model {
	components {
		frcUserProgram(NativeExecutableSpec) {
			// ...
			binaries.all {
				lib project: ':WML-Core', library: 'WML-Core', linkage: 'shared' // can also be static
				lib project: ':WML-Rev', library: 'WML-Core', linkage: 'shared' // can also be static
			}
			// ...
		}
	}

	testSuites {
		frcUserProgramTest(GoogleTestTestSuiteSpec) {
			// ...
			binaries.all {
				lib project: ':WML-Core', library: 'WML-Core', linkage: 'shared'
				lib project: ':WML-Rev', library: 'WML-Core', linkage: 'shared'
			}
			// ...
		}
	}
}

```
- Note that `:WML-Rev` is not required if you are not using Rev products (Neo Motor) 

### Doxygen
- You can view the generated documentation for each project via `https://buchel.family/repository/wml/first/<library>/<library>-Docs/<version>/<library>-<version>-documentation.zip`
- E.g https://buchel.family/repository/wml/first/WML-Core/WML-Core-Docs/latest/WML-Core-Docs-latest-documentation.zip

- You can naviage these docs and files manually too via https://buchel.family/repository/wml/first/

### Library examples
- Added to the library is an [example folder](/examples/). More examples are planned, however, I am aware that there are not many examples currently (especially compared to the breadth of the content in the library).

- I recommend looking at code that uses the library to get a better idea of what to do. (e.g. The Build environment we use for testing [Src](Robot/src/main))


## Contributing to WML
[CONTRIBUTING.md](CONTRIBUTING.md)


<sub><sup>readme written by [@CJBuchel](https://github.com/CJBuchel), 30/10/21</sup></sub>
