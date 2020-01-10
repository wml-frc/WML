<p align="center">
  <img src="https://avatars1.githubusercontent.com/u/58220426?s=200&v=4" alt=""/>
</p>

## A Modularised library designed for use in the First Robotics Competition.

### Setting up WML in your own project
- First you will need to install the submodule to your root directory. Navigate to your root dir and install via `git submodule add https://github.com/wml-frc/WML/`.

- Once complete you will need to apply the project to your own codebase. Every team has their own style of programming, building & deploying. But in general most will have a build.gradle and settings.gradle, And you would apply the library via using one of the two. You can do this, our style is using 3 files. 2 of the same build.gradle & settings.gradle files. And then a teams.gradle file. This is left over from when our team used to be both 5663 & 5333, and both files would share wml. Our code is still setup this way (mostly because it just cuts down on the amount of lines in build.gradle) But you don't have to call it teams.gradle nor use 3 files.

- Below you will find an example of adding the project to your own gradle project

- inside teams.gradle or whatever you choose to call it
```gradle
// Included by team projects (:4788)

apply plugin: 'cpp'
apply plugin: 'google-test-test-suite'
apply plugin: 'edu.wpi.first.GradleRIO'

deploy {
  targets {
    roboRIO('roborio') {
      team = project.hasProperty("team") ? project.team.toInteger() : project.name.toInteger()
      
      // For VSCode Debugging - we won't be able to deploy to every target!
      if (project.hasProperty("debugMode"))
        failOnMissing = false
    }
  }

  artifacts {
    frcNativeArtifact('frcCpp') {
      targets << 'roborio'
      component = "frcUserProgram${project.name}"
      // Debug can be overridden by command line, for use with VSCode (with -PdebugMode)
      debug = frc.getDebugOrDefault(false)
    }
    fileTreeArtifact('frcStaticFileDeploy') {
      targets << 'roborio'
      files = fileTree(dir: 'src/main/deploy')
      // Deploy to RoboRIO target, into /home/lvuser/deploy
      directory = '/home/lvuser/deploy'
    }
  }
}

dependencies {
  // The 2019.2.1 release of halsim_ds_socket is broken on windows, so we built a fixed version ourselves while
  // we wait for 2019.3.1
  if (wpi.platforms.desktop == 'windowsx86-64') {
    simulation rootProject.files('libs/halsim_ds_socketd.dll')
  } else if (wpi.platforms.desktop == 'osxx86-64') {
    simulation rootProject.files('libs/libhalsim_ds_socketd.dylib')
  } else if (wpi.platforms.desktop == 'linuxx86-64') {
    simulation rootProject.files('libs/libhalsim_ds_socketd.so')
  } else {
    simulation "edu.wpi.first.halsim:halsim_ds_socket:${wpi.wpilibVersion}:${wpi.platforms.desktop}debug@zip"
  }
}

wpi.deps.vendor.loadFrom(project(':common'))
wpi.deps.vendor.loadFrom(project(':wml'))

model {
  components {
    "frcUserProgram${project.name}"(NativeExecutableSpec) {
      targetPlatform wpi.platforms.roborio
      targetPlatform wpi.platforms.desktop

      sources.cpp {
        source {
          srcDir 'src/main/cpp'
        }
        exportedHeaders {
          srcDir 'src/main/include'
        }
      }

      binaries.all {
        lib project: ':common', library: 'curtinFrcCommon', linkage: 'static'
        lib project: ':wml', library: 'wml', linkage: 'static'
      }

      useLibrary(it, "wpilib")
      wpi.deps.vendor.cpp(it)
    }
  }

  testSuites {
    "frcUserProgramTest${project.name}"(GoogleTestTestSuiteSpec) {
      testing $.components.get("frcUserProgram${project.name}")

      sources.cpp {
        source {
          srcDir 'src/test/cpp'
          include '**/*.cpp'
        }
      }

      binaries.all {
        lib project: ':common', library: 'curtinFrcCommon', linkage: 'static'
        lib project: ':wml', library: 'wml', linkage: 'static'
      }

      useLibrary(it, "wpilib", "googletest")
      wpi.deps.vendor.cpp(it)
    }
  }
}

task "sim${project.name}"(dependsOn: "simulateFrcUserProgram${project.name}${wpi.platforms.desktop.capitalize()}DebugExecutable")

if (!project.hasProperty('no-common-check'))
  tasks.check.dependsOn(':common:check')

if (!project.hasProperty('no-wml-check'))
  tasks.check.dependsOn(':wml:check') 
```

- Then add the .gradle file inside settings.gradle
```gradle
import org.gradle.internal.os.OperatingSystem

pluginManagement {
    repositories {
        mavenLocal()
        gradlePluginPortal()
        String frcYear = '2020'
        File frcHome
        if (OperatingSystem.current().isWindows()) {
            String publicFolder = System.getenv('PUBLIC')
            if (publicFolder == null) {
                publicFolder = "C:\\Users\\Public"
            }
            frcHome = new File(publicFolder, "frc${frcYear}")
        } else {
            def userFolder = System.getProperty("user.home")
            frcHome = new File(userFolder, "frc${frcYear}")
        }
        def frcHomeMaven = new File(frcHome, 'maven')
        maven {
            name 'frcHome'
            url frcHomeMaven
        }
    }
}

rootProject.name = 'CurtinFRC2020'
include 'common', 'wml', '4788', 'Testbot', '4788:src:coprocessor'
```

- Then you can have your build.gradle file simplified to
```gradle
apply plugin: 'cpp'
apply plugin: 'google-test-test-suite'
apply plugin: 'edu.wpi.first.GradleRIO'
apply plugin: "org.ysb33r.doxygen"

model {
  components {
    wml(NativeLibrarySpec) {
      targetPlatform wpi.platforms.desktop
      targetPlatform wpi.platforms.roborio

      binaries.all {
        sources {
          cpp(CppSourceSet) {
            def target = targetPlatform.name == wpi.platforms.roborio ? 'robot' : 'simulation'
            source {
              srcDir 'src/main/cpp'
              srcDir "src/${target}/cpp"
              include '**/*.cpp'
            }
            exportedHeaders {
              srcDir 'src/main/include'
              srcDir "src/${target}/include"
            }
          }
        }
      }

      useLibrary(it, 'wpilib')
      wpi.deps.vendor.cpp(it)
    }
  }

  testSuites {
    wmlTest(GoogleTestTestSuiteSpec) {
      testing $.components.wml

      sources.cpp {
        source {
          srcDir 'src/test/cpp'
        }
      }

      useLibrary(it, 'wpilib', 'googletest')
      wpi.deps.vendor.cpp(it)
    }
  }
}

doxygen {
  executables {
      doxygen version : '1.8.13'
  }

  generate_html true
  javadoc_autobrief true
  source project.file('src/main/include')
}

```

### To see a working example of the wml library [WML](https://github.com/CJBuchel/2020CodeBase)



### Using the library [Examples](wml/src/example/)
- Added to the library is an example folder that overtime will have more and more examples inside of it. But i'm aware that there are not many examples. Compared to the size of the entire library.

- So I recommend looking at code that uses the library to get a better idea of what your doing. e.g [CurtinFrc2020CodeBase](https://github.com/CJBuchel/2020CodeBase)

Or read the source code of the library, it has a few comments inside there. But uhhhhh, i don't reccomend it. Even i don't know what half the stuff is...

That being said, if you have an issue or question feel free to contact us. We don't have lives... we're programmers.