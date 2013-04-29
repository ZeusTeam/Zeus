file(GLOB NMESSAGE_SRCS "*.cpp" "MsgDataValue/*.cpp")
add_library(nmessage STATIC ${NMESSAGE_SRCS})
