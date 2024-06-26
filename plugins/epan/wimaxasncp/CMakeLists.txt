# CMakeLists.txt
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 1998 Gerald Combs
#
# SPDX-License-Identifier: GPL-2.0-or-later
#

include(WiresharkPlugin)

# Plugin name and version info (major minor micro extra)
set_module_info(wimaxasncp 0 0 1 0)

set(DISSECTOR_SRC
	packet-wimaxasncp.c
)

set(PLUGIN_FILES
	plugin.c
	${DISSECTOR_SRC}
)

add_lex_files(LEX_FILES PLUGIN_FILES
	wimaxasncp_dict.l
)

set_source_files_properties(
	${DISSECTOR_SRC}
	PROPERTIES
	COMPILE_FLAGS "${WERROR_COMMON_FLAGS}"
)

register_plugin_files(plugin.c
	plugin
	"WiMAX ASN Control Plane dissection"
	${DISSECTOR_SRC}
)

add_wireshark_epan_plugin_library(wimaxasncp)

target_link_libraries(wimaxasncp epan)

install_plugin(wimaxasncp epan)

file(GLOB DISSECTOR_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")
CHECKAPI(
	NAME
	  wimaxasncp
	SWITCHES
	  --group dissectors-prohibited
	  --group dissectors-restricted
	SOURCES
	  ${DISSECTOR_SRC}
	  ${DISSECTOR_HEADERS}
# LEX files commented out due to use of malloc, free etc.
#	  ${LEX_FILES}
)

#
# Editor modelines  -  https://www.wireshark.org/tools/modelines.html
#
# Local variables:
# c-basic-offset: 8
# tab-width: 8
# indent-tabs-mode: t
# End:
#
# vi: set shiftwidth=8 tabstop=8 noexpandtab:
# :indentSize=8:tabSize=8:noTabs=false:
#
