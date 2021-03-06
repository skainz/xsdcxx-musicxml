XSDCXX based MusicXML bindings for C++
======================================

.. _xsdcxx: http://codesynthesis.com/projects/xsd/

xsdcxx-musicxml is a MusicXML binding for C++11 based on xsdcxx_.
The bulk of the source code is automatically generated from the MusicXML
W3C XML Schema Definition (XSD).  Parsing, manipulation, and serialization
of MusicXML documents is supported.

This library handles both, partwise *and* timewise MusicXML documents in a
uniform way.  Client code is free to work with either of the two object models,
and MusicXML documents are automatically converted to the requested format
during parsing.

.. code-block:: c++

    auto timewise = musicxml::parse<musicxml::score_timewise>(std::cin, "-");
    for (auto &measure: timewise.measure()) {
      for (auto &part: measure.part()) {
        std::clog << measure.number() << ": " << part.id()->part_name()
                  << std::endl;
        //...
      }
    }
    musicxml::serialize(std::cout, timewise);

or

.. code-block:: c++

    auto partwise = musicxml::parse<musicxml::score_partwise>(std::cin, "-");
    for (auto &part: partwise.part()) {
      for (auto &measure: part.measure()) {
        std::clog << part.id()->part_name() << ": " << measure.number()
                  << std::endl;
        //...
      }
    }
    musicxml::serialize(std::cout, partwise);

Alternatively, if you want to save to a different format as you have worked with,
you can use the musicxml::convert function to flip formats:

.. code-block:: c++

    // Serialize a score-partwise document.
    musicxml::serialize(std::cout, musicxml::convert(timewise));
    
Both, `musicxml::score_partwise::part_type::measure_type` and
`musicxml::score_timewise::measure_type::part_type` use `boost::variant` to
store the different allowed element types in a heterogeneous container.  This
container can be accessed and set with the `music_data()` accessors, and its
type is available as member type `music_data_sequence`.

`IDREF` attributes are configured to point directly to the referenced
element type(s).  Some IDREF's are optional though, so be sure to not
dereference those unconditionally.

Building
--------

CMake and XSDCXX are required to build this library.

See generate.cpp, partiwse.cpp and timewise.cpp for very simple usage examples.

To use this library in your project,

.. code-block:: c++

   #include "xsdcxx-musicxml/musicxml.hpp"

and link with the `xsdcxx-musicxml` library.  If you prefer static linking, use
`xsdcxx-musicxml-static`.

.. _ADD_SUBDIRECTORY: http://www.cmake.org/cmake/help/v3.0/command/add_subdirectory.html

You can also use the CMake ADD_SUBDIRECTORY_ command to directly
include this library as a subproject in your CMake based project.

Parent project
--------------

.. _BMC: https://github.com/mlang/bmc

This library is being developed as a sub-project of BMC_, the Braille Music Compiler.

