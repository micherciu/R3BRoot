# Create a library called "libR3B" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${BASE_INCLUDE_DIRECTORIES}
${R3BROOT_SOURCE_DIR}/fairtools
${R3BROOT_SOURCE_DIR}/MbsAPI
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/field
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/r3bgen
${R3BROOT_SOURCE_DIR}/passive
${R3BROOT_SOURCE_DIR}/tracker
${R3BROOT_SOURCE_DIR}/xball
${R3BROOT_SOURCE_DIR}/cal
${R3BROOT_SOURCE_DIR}/gfi
${R3BROOT_SOURCE_DIR}/gui
${R3BROOT_SOURCE_DIR}/land
${R3BROOT_SOURCE_DIR}/r3bdata/landData
${R3BROOT_SOURCE_DIR}/startracker
${R3BROOT_SOURCE_DIR}/dch
${R3BROOT_SOURCE_DIR}/tof
${R3BROOT_SOURCE_DIR}/mtof
${R3BROOT_SOURCE_DIR}/mfi
${R3BROOT_SOURCE_DIR}/psp
#${R3BROOT_SOURCE_DIR}/mcstack 
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BGui.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF R3BGuiLinkDef.h)
Set(LIBRARY_NAME R3BGui)
Set(DEPENDENCIES
    R3Bbase Field GeoBase ParBase Core Geom GenVector Physics Matrix MathCore FairTools)

GENERATE_LIBRARY()

