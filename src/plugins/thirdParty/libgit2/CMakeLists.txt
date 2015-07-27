PROJECT(libgit2Plugin)

MACRO(RETRIEVE_LIBGIT2_SETTINGS)
    # Retrieve some libgit2 settings

    IF(WIN32)
        SET(LIBGIT2_DEFINITIONS
            _CRT_NONSTDC_NO_DEPRECATE
            _CRT_SECURE_NO_DEPRECATE
            _SCL_SECURE_NO_WARNINGS
            _WIN32_WINNT=0x0501

            GIT_WINHTTP
            WIN32
            WIN32_SHA1
        )
    ELSEIF(APPLE)
        SET(LIBGIT2_DEFINITIONS
            GIT_COMMON_CRYPTO
            GIT_OPENSSL
        )
    ELSE()
        SET(LIBGIT2_DEFINITIONS
            GIT_OPENSSL
            OPENSSL_SHA1
        )
    ENDIF()

    LIST(APPEND LIBGIT2_DEFINITIONS
        _FILE_OFFSET_BITS=64

        GIT_THREADS
        STDC
    )

    IF(${ARCHITECTURE} EQUAL 32)
        LIST(APPEND LIBGIT2_DEFINITIONS
            GIT_ARCH_32
        )
    ELSE()
        LIST(APPEND LIBGIT2_DEFINITIONS
            GIT_ARCH_64
        )
    ENDIF()
ENDMACRO()

# Make sure that OpenSSL is available on Linux and OS X

IF(NOT WIN32)
    FIND_PACKAGE(OpenSSL REQUIRED QUIET)
ENDIF()

# Determine to which external binaries we need access

IF(WIN32)
    LINK_LIBRARIES(winhttp rpcrt4 crypt32)
ELSE()
    LINK_LIBRARIES(${OPENSSL_LIBRARIES})
ENDIF()

# Include the directories of the dependencies that we need access
# Note: we don't want them to be included as part of ADD_PLUGIN() or
#       ADD_PLUGIN_BINARY() since they would then be available to the rest of
#       the proejct, which could be a problem with the zlib plugin, for example,
#       since it is one of our dependencies...

SET(DEPENDENCIES_INCLUDE_DIRS
    deps/http-parser
    deps/zlib
)

IF(WIN32)
    LIST(APPEND DEPENDENCIES_INCLUDE_DIRS
        deps/regex
    )
ENDIF()

INCLUDE_DIRECTORIES(${DEPENDENCIES_INCLUDE_DIRS})

# Use our pre-built version unless instructed otherwise

IF(USE_PREBUILT_LIBGIT2_PLUGIN)
    # Retrieve the plugin's binary file(s)

    STRING(REPLACE "${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/" "" RELATIVE_PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/bin/${DISTRIB_BINARY_DIR}")

    IF(WIN32)
        IF(${ARCHITECTURE} EQUAL 32)
            IF(RELEASE_MODE)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.dll d229b79ceab39e6c59ac45c696594a8422b6953e)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.lib b4f29985e8f48ffb667f523cb4f979f948927966)
            ELSE()
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.dll 533e082b6f1e3989777956022bfc5d27db0067f0)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.lib 48ccd0221e60d6591992d1abe11c476e35069d67)
            ENDIF()
        ELSE()
            IF(RELEASE_MODE)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.dll 6fe35def0df3019df91f766f1069856468e04415)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.lib d6d4a94ab323502962df8e513f8e93af2918ef83)
            ELSE()
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.dll d5b943d1aa251c71d15ffced237f3cd936c0dae8)
                RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} libgit2.lib eed79650459069bc831b9a5b681f185bfda5babf)
            ENDIF()
        ENDIF()
    ELSEIF(APPLE)
        RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} liblibgit2.dylib d91be4e2f42a9b3fa7ab777ba33190d59f543777)
    ELSE()
        IF(${ARCHITECTURE} EQUAL 32)
            RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} liblibgit2.so bd671a594ef7fbc12a111d01bf3dc6b89e5d9a19)
        ELSE()
            RETRIEVE_BINARY_FILE(${RELATIVE_PROJECT_SOURCE_DIR} liblibgit2.so dcc7574b49f9cc8ea745252a151fcfbecb060e79)
        ENDIF()
    ENDIF()

    # Add the plugin as a binary
    # Note: in the case of Windows, we must refer to the distribution directory
    #       as opposed to the plugins directory since we need the .lib file and
    #       it's only there...

    IF(WIN32)
        SET(LIBGIT2_PLUGIN_BINARY ${PROJECT_SOURCE_DIR}/bin/${DISTRIB_BINARY_DIR}/${CMAKE_IMPORT_LIBRARY_PREFIX}libgit2${CMAKE_IMPORT_LIBRARY_SUFFIX} PARENT_SCOPE)
    ELSE()
        SET(LIBGIT2_PLUGIN_BINARY ${DEST_PLUGINS_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}libgit2${CMAKE_SHARED_LIBRARY_SUFFIX} PARENT_SCOPE)
    ENDIF()

    ADD_PLUGIN_BINARY(libgit2
        INCLUDE_DIRS
            include
            src
    )
ELSE()
    # Retrieve some libgit2 settings

    RETRIEVE_LIBGIT2_SETTINGS()

    # Ignore some warnings on Windows and OS X

    IF(WIN32)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4133 /wd4244 /wd4267")
    ELSEIF(APPLE)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
    ENDIF()

    # Determine which dependencies we must build

    SET(DEPENDENCIES_SOURCES
        deps/http-parser/http_parser.c

        deps/zlib/adler32.c
        deps/zlib/crc32.c
        deps/zlib/crc32.h
        deps/zlib/deflate.c
        deps/zlib/infback.c
        deps/zlib/inffast.c
        deps/zlib/inflate.c
        deps/zlib/inftrees.c
        deps/zlib/trees.c
        deps/zlib/zutil.c
    )

    IF(WIN32)
        LIST(APPEND DEPENDENCIES_SOURCES
            deps/regex/regex.c
        )
    ENDIF()

    # Determine which additional files to build, if any

    IF(WIN32)
        SET(ADDITIONAL_SOURCES
            src/hash/hash_win32.c

            src/win32/buffer.c
            src/win32/dir.c
            src/win32/error.c
            src/win32/findfile.c
            src/win32/map.c
            src/win32/path_w32.c
            src/win32/path_w32.h
            src/win32/posix_w32.c
            src/win32/precompiled.c
            src/win32/pthread.c
            src/win32/utf-conv.c
            src/win32/w32_util.c
        )
    ELSE()
        SET(ADDITIONAL_SOURCES
            src/unix/map.c
            src/unix/realpath.c
        )
    ENDIF()

    # Add the plugin

    SET(LIBGIT2_PLUGIN libgit2 PARENT_SCOPE)

    ADD_PLUGIN(libgit2
        THIRD_PARTY
        SOURCES
            ../../plugininfo.cpp

            ${DEPENDENCIES_SOURCES}

            src/annotated_commit.c
            src/attr.c
            src/attr_file.c
            src/attrcache.c
            src/blame.c
            src/blame_git.c
            src/blob.c
            src/branch.c
            src/buf_text.c
            src/buffer.c
            src/cache.c
            src/checkout.c
            src/cherrypick.c
            src/clone.c
            src/commit.c
            src/commit_list.c
            src/config.c
            src/config_cache.c
            src/config_file.c
            src/crlf.c
            src/curl_stream.c
            src/date.c
            src/delta-apply.c
            src/delta.c
            src/describe.c
            src/diff.c
            src/diff_driver.c
            src/diff_file.c
            src/diff_patch.c
            src/diff_print.c
            src/diff_stats.c
            src/diff_tform.c
            src/diff_xdiff.c
            src/errors.c
            src/fetch.c
            src/fetchhead.c
            src/filebuf.c
            src/fileops.c
            src/filter.c
            src/fnmatch.c
            src/global.c
            src/graph.c
            src/hash.c
            src/hashsig.c
            src/ident.c
            src/ignore.c
            src/index.c
            src/indexer.c
            src/iterator.c
            src/libgit2plugin.cpp
            src/merge.c
            src/merge_file.c
            src/message.c
            src/mwindow.c
            src/netops.c
            src/notes.c
            src/object.c
            src/object_api.c
            src/odb.c
            src/odb_loose.c
            src/odb_mempack.c
            src/odb_pack.c
            src/oid.c
            src/oidarray.c
            src/openssl_stream.c
            src/pack-objects.c
            src/pack.c
            src/path.c
            src/pathspec.c
            src/pool.c
            src/posix.c
            src/pqueue.c
            src/push.c
            src/rebase.c
            src/refdb.c
            src/refdb_fs.c
            src/reflog.c
            src/refs.c
            src/refspec.c
            src/remote.c
            src/repository.c
            src/reset.c
            src/revert.c
            src/revparse.c
            src/revwalk.c
            src/settings.c
            src/sha1_lookup.c
            src/signature.c
            src/socket_stream.c
            src/sortedcache.c
            src/stash.c
            src/status.c
            src/stransport_stream.c
            src/strmap.c
            src/submodule.c
            src/sysdir.c
            src/tag.c
            src/thread-utils.c
            src/tls_stream.c
            src/trace.c
            src/transaction.c
            src/transport.c
            src/tree-cache.c
            src/tree.c
            src/tsort.c
            src/util.c
            src/vector.c
            src/zstream.c

            src/transports/auth_negotiate.c
            src/transports/auth.c
            src/transports/cred_helpers.c
            src/transports/cred.c
            src/transports/git.c
            src/transports/http.c
            src/transports/local.c
            src/transports/smart_pkt.c
            src/transports/smart_protocol.c
            src/transports/smart.c
            src/transports/ssh.c
            src/transports/winhttp.c

            src/xdiff/xdiffi.c
            src/xdiff/xemit.c
            src/xdiff/xhistogram.c
            src/xdiff/xmerge.c
            src/xdiff/xpatience.c
            src/xdiff/xprepare.c
            src/xdiff/xutils.c

            ${ADDITIONAL_SOURCES}
        HEADERS_MOC
            src/libgit2plugin.h
        INCLUDE_DIRS
            include
            src
        DEFINITIONS
            ${LIBGIT2_DEFINITIONS}
        QT_MODULES
            Core
    )
ENDIF()