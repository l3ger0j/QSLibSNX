# QSLibSNX

QSLibSNX (long name QSLibSonnix) is a new iteration of the [QSP engine version 5.8.0](https://gitlab.com/Sonnix1/Qqsp/-/tree/77ce918e8c2f2bdde8ef389adca9e6b69624f572/) specifically for [QSPlugin](https://github.com/l3ger0j/QSPlugin)

## Changes

The main changes relate to JVM bindings and are necessary to enable the library to be used in Android OS applications. The build system has also been modified, with the addition of auto-generation of certain files and the replacement of the keyword 'static' with 'INLINE' in some instances.