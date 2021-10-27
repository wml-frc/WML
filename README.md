<p align="center">
  <img src="https://avatars1.githubusercontent.com/u/58220426?s=200&v=4" alt=""/>
</p>



## A modularity-based library designed for use in the FIRST Robotics Competition.

### Build Status
[![Build Status](https://dev.azure.com/ConnorBuchel0890/WML/_apis/build/status/wml-frc.WML?branchName=master)](https://dev.azure.com/ConnorBuchel0890/WML/_build/latest?definitionId=7&branchName=master)

### Setting up WML in your own project
- First you will need to 'install' the submodule to your root directory. Navigate to your root dir and install via `git submodule add https://github.com/wml-frc/WML.git`.

- Once complete you will need to apply the project to your own codebase. Every team has their own style of programming, building & deploying. But in general most will have a `build.gradle` and `settings.gradle`, and you would apply the library via appending the the two.

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

- And include the wml gradle file in the bottom line of your `settings.gradle`:
```gradle
include 'wml', '4788' // replace with your teamnumber, or however you have gradle setup
```

### Doxygen
- You can view the generated documentation by going to [azure](https://dev.azure.com/ConnorBuchel0890/WML/_build?definitionId=17&_a=summary) slecting the latest successful build. Then clicking the published artifact and downloading the zip folder.

### Library examples
- Added to the library is an [example folder](/examples/). More examples are planned, however, I am aware that there are not many examples currently (especially compared to the breadth of the content in the library).

- I recommend looking at code that uses the library to get a better idea of what to do. (e.g. The Build environment we use for testing [Src](src/main))


<sub><sup>readme written by [@CJBuchel](https://github.com/CJBuchel), 27/10/21</sup></sub>
