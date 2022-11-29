/* Do not modify this file. Changes will be overwritten.                      */
/* Generated automatically by the ASN.1 to Wireshark dissector compiler       */
/* packet-rtse.h                                                              */
/* asn2wrs.py -b -L -p rtse -c ./rtse.cnf -s ./packet-rtse-template -D . -O ../.. rtse.asn */

/* Input file: packet-rtse-template.h */

#line 1 "./asn1/rtse/packet-rtse-template.h"
/* packet-rtse.h
 * Routines for RTSE packet dissection
 * Graeme Lunt 2005
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef PACKET_RTSE_H
#define PACKET_RTSE_H


/*--- Included file: packet-rtse-exp.h ---*/
#line 1 "./asn1/rtse/packet-rtse-exp.h"
int dissect_rtse_RTORQapdu(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_);
int dissect_rtse_RTOACapdu(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_);
int dissect_rtse_RTORJapdu(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_);
int dissect_rtse_RTABapdu(gboolean implicit_tag _U_, tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_);

/*--- End of included file: packet-rtse-exp.h ---*/
#line 16 "./asn1/rtse/packet-rtse-template.h"

void register_rtse_oid_dissector_handle(const char *oid, dissector_handle_t dissector, int proto _U_, const char *name, gboolean uses_ros);

#endif  /* PACKET_RTSE_H */
