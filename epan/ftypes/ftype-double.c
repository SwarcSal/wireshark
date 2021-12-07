/*
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 2001 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <stdio.h>
#include <ftypes-int.h>
#include <math.h>
#include <errno.h>
#include <float.h>

#include "strutil.h"

static void
double_fvalue_new(fvalue_t *fv)
{
	fv->value.floating = 0.0;
}

static void
double_fvalue_set_floating(fvalue_t *fv, gdouble value)
{
	fv->value.floating = value;
}

static double
value_get_floating(fvalue_t *fv)
{
	return fv->value.floating;
}

static gboolean
val_from_literal(fvalue_t *fv, const char *s, gboolean allow_partial_value _U_, gchar **err_msg)
{
	char    *endptr = NULL;

	fv->value.floating = g_ascii_strtod(s, &endptr);

	if (endptr == s || *endptr != '\0') {
		/* This isn't a valid number. */
		if (err_msg != NULL)
			*err_msg = ws_strdup_printf("\"%s\" is not a valid number.", s);
		return FALSE;
	}
	if (errno == ERANGE) {
		if (fv->value.floating == 0) {
			if (err_msg != NULL)
				*err_msg = ws_strdup_printf("\"%s\" causes floating-point underflow.", s);
		}
		else if (fv->value.floating == HUGE_VAL) {
			if (err_msg != NULL)
				*err_msg = ws_strdup_printf("\"%s\" causes floating-point overflow.", s);
		}
		else {
			if (err_msg != NULL)
				*err_msg = ws_strdup_printf("\"%s\" is not a valid floating-point number.",
				    s);
		}
		return FALSE;
	}

	return TRUE;
}

static char *
float_val_to_repr(wmem_allocator_t *scope, const fvalue_t *fv, ftrepr_t rtype _U_, int field_display _U_)
{
	size_t size = G_ASCII_DTOSTR_BUF_SIZE;
	char *buf = wmem_alloc(scope, size);
	g_ascii_formatd(buf, (gint)size, "%." G_STRINGIFY(FLT_DIG) "g", fv->value.floating);
	return buf;
}

static char *
double_val_to_repr(wmem_allocator_t *scope, const fvalue_t *fv, ftrepr_t rtype _U_, int field_display _U_)
{
	size_t size = G_ASCII_DTOSTR_BUF_SIZE;
	char *buf = wmem_alloc(scope, size);
	g_ascii_formatd(buf, (gint)size, "%." G_STRINGIFY(DBL_DIG) "g", fv->value.floating);
	return buf;
}

enum ft_result
val_unary_minus(fvalue_t * dst, const fvalue_t *src, char **err_ptr _U_)
{
	dst->value.floating = -src->value.floating;
	return FT_OK;
}

static int
cmp_order(const fvalue_t *a, const fvalue_t *b)
{
	if (a->value.floating < b->value.floating)
		return -1;
	if (a->value.floating > b->value.floating)
		return 1;
	return 0;
}

void
ftype_register_double(void)
{

	static ftype_t float_type = {
		FT_FLOAT,			/* ftype */
		"FT_FLOAT",			/* name */
		"Floating point (single-precision)", /* pretty_name */
		0,				/* wire_size */
		double_fvalue_new,		/* new_value */
		NULL,				/* free_value */
		val_from_literal,		/* val_from_literal */
		NULL,				/* val_from_string */
		NULL,				/* val_from_charconst */
		float_val_to_repr,		/* val_to_string_repr */

		{ .set_value_floating = double_fvalue_set_floating },		/* union set_value */
		{ .get_value_floating = value_get_floating },	/* union get_value */

		cmp_order,
		NULL,				/* cmp_contains */
		NULL,				/* cmp_matches */

		NULL,				/* is_zero */
		NULL,
		NULL,
		NULL,				/* bitwise_and */
		val_unary_minus,		/* unary_minus */
	};

	static ftype_t double_type = {
		FT_DOUBLE,			/* ftype */
		"FT_DOUBLE",			/* name */
		"Floating point (double-precision)", /* pretty_name */
		0,				/* wire_size */
		double_fvalue_new,		/* new_value */
		NULL,				/* free_value */
		val_from_literal,		/* val_from_literal */
		NULL,				/* val_from_string */
		NULL,				/* val_from_charconst */
		double_val_to_repr,		/* val_to_string_repr */

		{ .set_value_floating = double_fvalue_set_floating },		/* union set_value */
		{ .get_value_floating = value_get_floating },	/* union get_value */

		cmp_order,
		NULL,				/* cmp_contains */
		NULL,				/* cmp_matches */

		NULL,				/* is_zero */
		NULL,
		NULL,
		NULL,				/* bitwise_and */
		val_unary_minus,		/* unary_minus */
	};

	ftype_register(FT_FLOAT, &float_type);
	ftype_register(FT_DOUBLE, &double_type);
}

void
ftype_register_pseudofields_double(int proto)
{
	static int hf_ft_float;
	static int hf_ft_double;

	static hf_register_info hf_ftypes[] = {
		{ &hf_ft_float,
		    { "FT_FLOAT", "_ws.ftypes.float",
			FT_FLOAT, BASE_NONE, NULL, 0x00,
			NULL, HFILL }
		},
		{ &hf_ft_double,
		    { "FT_DOUBLE", "_ws.ftypes.double",
			FT_DOUBLE, BASE_NONE, NULL, 0x00,
			NULL, HFILL }
		},
	};

	proto_register_field_array(proto, hf_ftypes, array_length(hf_ftypes));
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */
