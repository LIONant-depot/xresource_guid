cmake_minimum_required(VERSION 3.10)

# Define as an interface library
if(NOT TARGET xresource)
    add_library(xresource INTERFACE)
   
    #set the root for this project
    set(ROOT "${CMAKE_SOURCE_DIR}/dependencies/xresource")

    # path to xerr for the include files
    set(XRESOURCE_INCLUDE_LIST "${ROOT}"
    )
    
    # Define file list
    set(XRESOURCE_FILES_LIST "${ROOT}/source/xresource_guid.h"
                             "${ROOT}/source/xresource_guid_properties.h"
                             "${ROOT}/readme.md"
    )

    # Set global properties
    set_property(GLOBAL PROPERTY XRESOURCE_GROUP "dependencies/xcore/xresource")
    set_property(GLOBAL PROPERTY XRESOURCE_FILES "${XRESOURCE_FILES_LIST}")
    set_property(GLOBAL PROPERTY XRESOURCE_INCLUDES "${XRESOURCE_INCLUDE_LIST}")
    set_property(GLOBAL APPEND PROPERTY COMPONENT_REGISTRY "XRESOURCE")
endif()
