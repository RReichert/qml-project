# QML Project

Overview
--------

The intention of this projec is to setup a template CMake project structure of
a QML project. It serves as an alternative to the QMake build generator system.

The project tries to provide the most common functionalities that QMake easily
makes available, such as:

* Unit Testing
* MOC Generation
* Qt Resource System
* Internationalization

In addition to this, this will offer the ability to generate Doxygen
documentation quite easily as well.

The one major different between the functionality that QMake offers over this
project is the unit testing framework. This project was made using the **GTest**
over **QUnitTest**.

Dependencies
------------

* Qt5
* Boost C++ Library
* Qrc Editor (https://github.com/RReichert/qrc-editor)
* Doxygen
* GTest

Documentation
-------------

As this project isn't finalized, this will be left to the final stages of the
project.

Future Features
---------------

I hope to develop the template to include CTest, CDash, and CPackage, however
that isn't a priority as of now.
