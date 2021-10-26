<p align="center">
  <img src="https://avatars1.githubusercontent.com/u/58220426?s=200&v=4" alt=""/>
</p>


#### Build Status
[![Build Status](https://dev.azure.com/ConnorBuchel0890/WML/_apis/build/status/wml-frc.WML?branchName=master)](https://dev.azure.com/ConnorBuchel0890/WML/_build/latest?definitionId=7&branchName=master)

## A modularity-based library designed for use in the FIRST Robotics Competition.

### Setting up WML in your own project
- First you will need to 'install' the submodule to your root directory. Navigate to your root dir and install via `git submodule add https://github.com/wml-frc/WML.git`.

- Once complete you will need to apply the project to your own codebase. Every team has their own style of programming, building & deploying. But in general most will have a `build.gradle` and `settings.gradle`, and you would apply the library via using one of the two. Our style utilises 3 files; the build.gradle and settings.gradle files,as well as a `teams.gradle` file. This is left over from when our team used to be both 5663 & 5333, and allowed multiple projects with different team numbers to easily co-exist in the same root project. Our code is still setup this way (partially for customary reasons), however it is definately not a requirement to use a `teams.gradle` file, or 3-file structure.

#### Adding WML to your project's gradle config
- Add the doxygen plugin to top of your `build.gradle` file (required by WML currently - hopefully will be optional soon):
```gradle
plugins {
  id 'org.ysb33r.doxygen' version '0.5' apply false
}
```

- Inside your project file (e.g. `teams.gradle`) add:
```gradle
def includeSrcInIncludeRoot = false
def includeDesktopSupport = false

def includeWMLRevSupport = false

project(':wml').ext.setProperty('includeSrcInIncludeRoot', includeSrcInIncludeRoot)
project(':wml').ext.setProperty('includeDesktopSupport', includeDesktopSupport)
project(':wml').ext.setProperty('includeWMLRevSupport', includeWMLRevSupport)

// ...

wpi.deps.vendor.loadFrom(project(':wml'))

// ...

model {
  components {
    frcUserProgram(NativeExecutableSpec) {
      // ...
      binaries.all {
        lib project: ':wml', library: 'wml', linkage: 'static'
      }
      // ...
    }
  }
  testSuites {
    frcUserProgramTest(GoogleTestTestSuiteSpec) {
      // ...
      binaries.all {
        lib project: ':wml', library: 'wml', linkage: 'static'
      }
      // ...
    }
  }
}

// ...

// optional:
if (!project.hasProperty('no-wml-check'))
  tasks.check.dependsOn(':wml:check') 
```

- And include the wml gradle file in the bottom line of your `settings.gradle`:
```gradle
include 'wml', '4788' // replace with your teamnumber, or however you have gradle setup
```


### Library examples
- Added to the library is an [example folder](/examples/). More examples are planned, however I am aware that there are not many examples currently (especially compared to the breadth of the content in the library).

- I recommend looking at code that uses the library to get a better idea of what to do. (e.g. the CurtinFRC [2020 CodeBase](https://github.com/CurtinFRC/2020-InfiniteRecharge))

Or read the source code of the library; it has a few comments inside there. But uhhhhh, I don't recommend it. Even I don't know what half the stuff is...

That being said, if you have an issue or question feel free to contact us. We don't have lives... we're programmers.


<sub><sup>readme written by [@CJBuchel](https://github.com/CJBuchel), 4/03/20</sup></sub>
