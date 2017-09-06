#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nanopb::libprotobuf-nanopb" for configuration ""
set_property(TARGET nanopb::libprotobuf-nanopb APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(nanopb::libprotobuf-nanopb PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblibprotobuf-nanopb.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS nanopb::libprotobuf-nanopb )
list(APPEND _IMPORT_CHECK_FILES_FOR_nanopb::libprotobuf-nanopb "${_IMPORT_PREFIX}/lib/liblibprotobuf-nanopb.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
