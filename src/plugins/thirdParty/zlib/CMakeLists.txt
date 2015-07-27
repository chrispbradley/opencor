PROJECT(zlibPlugin)

MACRO(RETRIEVE_ZLIB_SETTINGS)
    # Retrieve some zlib settings

    IF(WIN32)
        SET(ZLIB_DEFINITIONS
            ZLIB_DLL
        )
    ELSE()
        SET(ZLIB_DEFINITIONS)
    ENDIF()
ENDMACRO()

# Retrieve some header files that were generated on each of our target platforms

RETRIEVE_CONFIG_FILES(
    src/DISTRIB_DIR/zconf.h
)

# Use our pre-built version unless instructed otherwise

IF(USE_PREBUILT_ZLIB_PLUGIN)
    # Retrieve the plugin's binary file(s)

    STRING(REPLACE "${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/" "" RELATIVE_PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/bin/${DISTRIB_BINARY_DIR}")

    IF(WIN32)
        IF(${ARCHITECTURE} EQUAL 32)
            IF(RELEASE_MODE)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.dll 6639fa3c46567d8e46d6a8fb566392117ee5067d)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.lib fe327abcd31e4cf0098a17de474ed2e92d9d6620)
            ELSE()
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.dll 54f1c8c97e3c2b424b61a559e4f18e7f62e8195a)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.lib 6d4ae21c1e81dfbafeb365cece942ae92e4209a8)
            ENDIF()
        ELSE()
            IF(RELEASE_MODE)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.dll 785669ffea770b09e6137700a3b100cdb3f8b61e)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.lib 68c3cb7e84165f51315b12fb0147236080f8812f)
            ELSE()
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.dll da1694eb9d98a42cb4d8aa2f5f093bce7c7e6fc0)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} zlib.lib efbaa4fe28169de8c152adf4b0fc4b4d49d3f4e9)
            ENDIF()
        ENDIF()
    ELSEIF(APPLE)
        RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libzlib.dylib 84d62ff9185205d4857567a151114405c032592c)
    ELSE()
        IF(${ARCHITECTURE} EQUAL 32)
            RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libzlib.so b76599807e11050fa1a08ac6600e445d700458ea)
        ELSE()
            RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libzlib.so 65ea98ef7fb4834b4df716b4150ab4412a6b2dd2)
        ENDIF()
    ENDIF()

    # Add the plugin as a binary
    # Note: in the case of Windows, we must refer to the distribution directory
    #       as opposed to the plugins directory since we need the .lib file and
    #       it's only there...

    IF(WIN32)
        SET(ZLIB_PLUGIN_BINARY ${PROJECT_SOURCE_DIR}/bin/${DISTRIB_BINARY_DIR}/${CMAKE_IMPORT_LIBRARY_PREFIX}zlib${CMAKE_IMPORT_LIBRARY_SUFFIX} PARENT_SCOPE)
    ELSE()
        SET(ZLIB_PLUGIN_BINARY ${DEST_PLUGINS_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}zlib${CMAKE_SHARED_LIBRARY_SUFFIX} PARENT_SCOPE)
    ENDIF()

    ADD_PLUGIN_BINARY(zlib
        INCLUDE_DIRS
            src
    )
ELSE()
    # Retrieve some zlib settings

    RETRIEVE_ZLIB_SETTINGS()

    # Ignore some warnings on Windows and OS X

    IF(WIN32)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4996")
    ENDIF()

    # Add the plugin

    SET(ZLIB_PLUGIN zlib PARENT_SCOPE)

    ADD_PLUGIN(zlib
        THIRD_PARTY
        SOURCES
            ../../plugininfo.cpp

            src/adler32.c
            src/compress.c
            src/crc32.c
            src/deflate.c
            src/gzclose.c
            src/gzlib.c
            src/gzread.c
            src/gzwrite.c
            src/infback.c
            src/inffast.c
            src/inflate.c
            src/inftrees.c
            src/trees.c
            src/uncompr.c
            src/zlibplugin.cpp
            src/zutil.c
        HEADERS_MOC
            src/zlibplugin.h
        INCLUDE_DIRS
            src
        DEFINITIONS
            ${ZLIB_DEFINITIONS}
        QT_MODULES
            Core
    )
ENDIF()