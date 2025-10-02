include(${CMAKE_BINARY_DIR}/_deps/xcmake_tools/Common.cmake)

DefineInterfaceComponent(xresource_guid "dependencies/xcore"
  "source/xresource_guid.h"
  "readme.md"
  "**bridges"
  "source/bridges/xresource_xproperty_bridge.h"
)