/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Olivier Hill <ohill@php.net>                                 |
  |         Matthew Fonda                                                |
  |         Adam Saponara <as@php.net>                                   |
  +----------------------------------------------------------------------+
  Please contact support@maxmind.com with any comments
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <GeoIP.h>
#include <GeoIPCity.h>
#ifdef PHP_WIN32
#include <GeoIP_internal.h>
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_geoip.h"

ZEND_DECLARE_MODULE_GLOBALS(geoip)

static int le_geoip;

/* {{{ */
zend_function_entry geoip_functions[] = {
	PHP_FE(geoip_country_code_by_name, NULL)
	PHP_FE(geoip_country_code3_by_name, NULL)
	PHP_FE(geoip_country_name_by_name, NULL)
	PHP_FE(geoip_asnum_by_name, NULL)
	PHP_FE(geoip_domain_by_name, NULL)
	PHP_FE(geoip_isp_by_name, NULL)
	PHP_FE(geoip_org_by_name, NULL)
	PHP_FE(geoip_region_by_name, NULL)
	PHP_FE(geoip_record_by_name, NULL)
	PHP_FE(geoip_id_by_name, NULL)
	PHP_FE(geoip_continent_code_by_name, NULL)
#if LIBGEOIP_VERSION >= 1004005
	PHP_FE(geoip_country_code_by_name_v6, NULL)
	PHP_FE(geoip_country_code3_by_name_v6, NULL)
	PHP_FE(geoip_country_name_by_name_v6, NULL)
	PHP_FE(geoip_asnum_by_name_v6, NULL)
	PHP_FE(geoip_domain_by_name_v6, NULL)
	PHP_FE(geoip_isp_by_name_v6, NULL)
	PHP_FE(geoip_org_by_name_v6, NULL)
	PHP_FE(geoip_region_by_name_v6, NULL)
	PHP_FE(geoip_record_by_name_v6, NULL)
	PHP_FE(geoip_id_by_name_v6, NULL)
	PHP_FE(geoip_continent_code_by_name_v6, NULL)
#endif
	PHP_FE(geoip_db_avail, NULL)
	PHP_FE(geoip_db_filename, NULL)
	PHP_FE(geoip_db_get_all_info, NULL)
	PHP_FE(geoip_database_info, NULL)
#if LIBGEOIP_VERSION >= 1004001
	PHP_FE(geoip_region_name_by_code, NULL)
	PHP_FE(geoip_time_zone_by_country_and_region, NULL)
#endif
#ifdef HAVE_CUSTOM_DIRECTORY
	PHP_FE(geoip_setup_custom_directory, NULL)
#endif
#if LIBGEOIP_VERSION >= 1004008
	PHP_FE(geoip_netspeedcell_by_name, NULL)
	PHP_FE(geoip_netspeedcell_by_name_v6, NULL)
#endif
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ geoip_module_entry
 */
zend_module_entry geoip_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"geoip",
	geoip_functions,
	PHP_MINIT(geoip),
	NULL,
	NULL,
	PHP_RSHUTDOWN(geoip),
	PHP_MINFO(geoip),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GEOIP_VERSION, /* version number of the extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEOIP
ZEND_GET_MODULE(geoip)
#endif

#ifdef HAVE_CUSTOM_DIRECTORY
/* {{{ geoip_change_custom_directory() helper function */
static void geoip_change_custom_directory(char *value) {
#if LIBGEOIP_VERSION >= 1004007
	GeoIP_cleanup();
#else
	int i;
	if (GeoIPDBFileName != NULL) {
		for (i = 0; i < NUM_DB_TYPES; i++) {
			if (GeoIPDBFileName[i]) {
				free(GeoIPDBFileName[i]);
			}
		}
		free(GeoIPDBFileName);
		GeoIPDBFileName = NULL;
	}
#endif
	GeoIP_setup_custom_directory(value);
	_GeoIP_setup_dbfilename();
}
/* }}} */
#endif

#ifdef HAVE_CUSTOM_DIRECTORY
/* {{{ PHP_INI_MH */
static PHP_INI_MH(OnUpdateDirectory) {
	if (stage == PHP_INI_STAGE_RUNTIME || stage == PHP_INI_STAGE_HTACCESS) {
		GEOIP_G(set_runtime_custom_directory) = 1;
		geoip_change_custom_directory(new_value);
		return SUCCESS;
	}
	return OnUpdateString(entry, new_value, new_value_length, mh_arg1, mh_arg2, mh_arg3, stage TSRMLS_CC);
}
/* }}} */
#endif

/* {{{ PHP_INI */
PHP_INI_BEGIN()
#ifdef HAVE_CUSTOM_DIRECTORY
	STD_PHP_INI_ENTRY("geoip.custom_directory", NULL, PHP_INI_ALL, OnUpdateDirectory, custom_directory, zend_geoip_globals, geoip_globals)
#endif
PHP_INI_END()
/* }}} */

/* {{{ php_geoip_init_globals */
static void php_geoip_init_globals(zend_geoip_globals *geoip_globals) {
	geoip_globals->custom_directory = NULL;
	geoip_globals->set_runtime_custom_directory = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(geoip) {
	ZEND_INIT_MODULE_GLOBALS(geoip, php_geoip_init_globals, NULL);

	REGISTER_INI_ENTRIES();
	/* @TODO: Do something for custom_directory before initialization here */

#ifdef HAVE_CUSTOM_DIRECTORY
	GeoIP_setup_custom_directory(GEOIP_G(custom_directory));
#endif

	_GeoIP_setup_dbfilename();
	/* For database type constants */
	REGISTER_LONG_CONSTANT("GEOIP_COUNTRY_EDITION",        GEOIP_COUNTRY_EDITION,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_REGION_EDITION_REV0",    GEOIP_REGION_EDITION_REV0,    CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CITY_EDITION_REV0",      GEOIP_CITY_EDITION_REV0,      CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ORG_EDITION",            GEOIP_ORG_EDITION,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ISP_EDITION",            GEOIP_ISP_EDITION,            CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CITY_EDITION_REV1",      GEOIP_CITY_EDITION_REV1,      CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_REGION_EDITION_REV1",    GEOIP_REGION_EDITION_REV1,    CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_PROXY_EDITION",          GEOIP_PROXY_EDITION,          CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ASNUM_EDITION",          GEOIP_ASNUM_EDITION,          CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_NETSPEED_EDITION",       GEOIP_NETSPEED_EDITION,       CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_DOMAIN_EDITION",         GEOIP_DOMAIN_EDITION,         CONST_CS | CONST_PERSISTENT);

#if LIBGEOIP_VERSION >= 1004005
	REGISTER_LONG_CONSTANT("GEOIP_COUNTRY_EDITION_V6",     GEOIP_COUNTRY_EDITION_V6,     CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CITY_EDITION_REV0_V6",   GEOIP_CITY_EDITION_REV0_V6,   CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ORG_EDITION_V6",         GEOIP_ORG_EDITION_V6,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ISP_EDITION_V6",         GEOIP_ISP_EDITION_V6,         CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CITY_EDITION_REV1_V6",   GEOIP_CITY_EDITION_REV1_V6,   CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_ASNUM_EDITION_V6",       GEOIP_ASNUM_EDITION_V6,       CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_DOMAIN_EDITION_V6",      GEOIP_DOMAIN_EDITION_V6,      CONST_CS | CONST_PERSISTENT);
#endif

#if LIBGEOIP_VERSION >= 1004008
	REGISTER_LONG_CONSTANT("GEOIP_NETSPEED_EDITION_REV1",    GEOIP_NETSPEED_EDITION_REV1,    CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_NETSPEED_EDITION_REV1_V6", GEOIP_NETSPEED_EDITION_REV1_V6, CONST_CS | CONST_PERSISTENT);
#endif

	/* For netspeed constants */
	REGISTER_LONG_CONSTANT("GEOIP_UNKNOWN_SPEED",       GEOIP_UNKNOWN_SPEED,       CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_DIALUP_SPEED",        GEOIP_DIALUP_SPEED,        CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CABLEDSL_SPEED",      GEOIP_CABLEDSL_SPEED,      CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("GEOIP_CORPORATE_SPEED",     GEOIP_CORPORATE_SPEED,     CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(geoip) {
#ifdef HAVE_CUSTOM_DIRECTORY
	/* If we have a custom directory (and have support from   */
	/* libgeoip, we reset the extension to default directory) */
	if (GEOIP_G(set_runtime_custom_directory)) {
		geoip_change_custom_directory(GEOIP_G(custom_directory));
		GEOIP_G(set_runtime_custom_directory) = 0;
	}
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(geoip) {
	char buf[32];
	php_info_print_table_start();
	php_info_print_table_header(2, "geoip support", "enabled");
	php_info_print_table_row(2, "geoip extension version", PHP_GEOIP_VERSION);
	snprintf(buf, sizeof(buf), "%d", LIBGEOIP_VERSION);
	php_info_print_table_row(2, "geoip library version", buf);
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ geoip_open_db helper */
GeoIP* geoip_open_db(int db_type, int db_type_fallback, int use_fallback) {
	GeoIP* gi;
	gi = NULL;
	if (db_type < 0 || db_type >= NUM_DB_TYPES
		|| (use_fallback && (db_type_fallback < 0 || db_type_fallback >= NUM_DB_TYPES))
	) {
	    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Database type given is out of bound.");
	} else if (GeoIP_db_avail(db_type)) {
	    gi = GeoIP_open_type(db_type, GEOIP_STANDARD);
	} else if (use_fallback && GeoIP_db_avail(db_type_fallback)) {
		gi = GeoIP_open_type(db_type_fallback, GEOIP_STANDARD);
	} else {
	    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Required database not available at %s.", GeoIPDBFileName[db_type]);
	}
	return gi;
}
/* }}} */

/* {{{ geoip_generic_string helper */
void geoip_generic_string(
	INTERNAL_FUNCTION_PARAMETERS,
	char* (*geoip_func)(GeoIP* gi, const char* host),
	int db_type,
    int do_free
) {
	GeoIP* gi;
	char* hostname;
	char* retval;
	int arglen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &hostname, &arglen) == FAILURE) {
		return;
	}

	if (!(gi = geoip_open_db(db_type, 0, 0))) {
		return;
	}

	retval = (char*)geoip_func(gi, hostname);
	GeoIP_delete(gi);
	if (!retval) {
		RETURN_FALSE;
	}
	RETVAL_STRING(retval, 1);
	if (do_free) free(retval);
}
/* }}} */

/* {{{ geoip_generic_string helper */
void geoip_generic_region(
	INTERNAL_FUNCTION_PARAMETERS,
	GeoIPRegion* (*geoip_func)(GeoIP* gi, const char* host),
	int db_type_1,
	int db_type_2
) {
	GeoIP* gi;
	char* hostname;
	int arglen;
	GeoIPRegion* region;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &hostname, &arglen) == FAILURE) {
		return;
	}

	if (!(gi = geoip_open_db(db_type_1, db_type_2, 1))) {
	    return;
	}

	region = geoip_func(gi, hostname);
	GeoIP_delete(gi);
	if (!region) {
		RETURN_FALSE;
	}
	array_init(return_value);
	add_assoc_string(return_value, "country_code", region->country_code, 1);
	add_assoc_string(return_value, "region", region->region, 1);
	GeoIPRegion_delete(region);
}
/* }}} */

/* {{{ geoip_generic_record helper */
void geoip_generic_record(
	INTERNAL_FUNCTION_PARAMETERS,
	GeoIPRecord* (*geoip_func)(GeoIP* gi, const char* host),
    int db_type1,
    int db_type2
) {
	GeoIP* gi;
	char* hostname;
	int arglen;
	GeoIPRecord* gir;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &hostname, &arglen) == FAILURE) {
		return;
	}

	if (!(gi = geoip_open_db(db_type1, db_type2, 1))) {
		return;
	}

	gir = GeoIP_record_by_name(gi, hostname);
	GeoIP_delete(gi);
	if (!gir) {
		RETURN_FALSE;
	}

	array_init(return_value);
#if LIBGEOIP_VERSION >= 1004003
	add_assoc_string(return_value, "continent_code", (gir->continent_code == NULL) ? "" : gir->continent_code, 1);
#endif
	add_assoc_string(return_value, "country_code", (gir->country_code == NULL) ? "" : gir->country_code, 1);
	add_assoc_string(return_value, "country_code3", (gir->country_code3 == NULL) ? "" : gir->country_code3, 1);
	add_assoc_string(return_value, "country_name", (gir->country_name == NULL) ? "" : gir->country_name, 1);
	add_assoc_string(return_value, "region", (gir->region == NULL) ? "" : gir->region, 1);
	add_assoc_string(return_value, "city", (gir->city == NULL) ? "" : gir->city, 1);
	add_assoc_string(return_value, "postal_code", (gir->postal_code == NULL) ? "" : gir->postal_code, 1);
	add_assoc_double(return_value, "latitude", gir->latitude);
	add_assoc_double(return_value, "longitude", gir->longitude);
#if LIBGEOIP_VERSION >= 1004005
	add_assoc_long(return_value, "dma_code", gir->metro_code);
#else
	add_assoc_long(return_value, "dma_code", gir->dma_code);
#endif
	add_assoc_long(return_value, "area_code", gir->area_code);

	GeoIPRecord_delete(gir);
}
/* }}} */

/* {{{ geoip_generic_id helper */
int geoip_generic_id(
	INTERNAL_FUNCTION_PARAMETERS,
	int (*geoip_func)(GeoIP* gi, const char* host),
	int db_type,
	int* ret_id
) {
	GeoIP* gi;
	char* hostname;
	int arglen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &hostname, &arglen) == FAILURE) {
		return 0;
	}

	if (!(gi = geoip_open_db(db_type, 0, 0))) {
		return 0;
	}

	*ret_id = geoip_func(gi, hostname);
	GeoIP_delete(gi);
	return 1;
}
/* }}} */

/* {{{ proto string geoip_db_avail( [ int database ] ) */
PHP_FUNCTION(geoip_country_code_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_code_by_name, GEOIP_COUNTRY_EDITION, 0);
}

PHP_FUNCTION(geoip_country_code3_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_code3_by_name, GEOIP_COUNTRY_EDITION, 0);
}

PHP_FUNCTION(geoip_country_name_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_name_by_name, GEOIP_COUNTRY_EDITION, 0);
}

PHP_FUNCTION(geoip_asnum_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name, GEOIP_ASNUM_EDITION, 1);
}

PHP_FUNCTION(geoip_domain_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name, GEOIP_DOMAIN_EDITION, 1);
}

#if LIBGEOIP_VERSION >= 1004008
PHP_FUNCTION(geoip_netspeedcell_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name, GEOIP_NETSPEED_EDITION_REV1, 1);
}
#endif

PHP_FUNCTION(geoip_isp_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name, GEOIP_ISP_EDITION, 1);
}

PHP_FUNCTION(geoip_org_by_name) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_org_by_name, GEOIP_ORG_EDITION, 1);
}

PHP_FUNCTION(geoip_region_by_name) {
	geoip_generic_region(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_region_by_name, GEOIP_CITY_EDITION_REV1, GEOIP_CITY_EDITION_REV0);
}

PHP_FUNCTION(geoip_record_by_name) {
	geoip_generic_record(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_record_by_name, GEOIP_CITY_EDITION_REV1, GEOIP_CITY_EDITION_REV0);
}

PHP_FUNCTION(geoip_id_by_name) {
	int netspeed;
	if (geoip_generic_id(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_id_by_name, GEOIP_NETSPEED_EDITION_REV1, &netspeed)) {
		RETURN_LONG(netspeed);
	}
}

PHP_FUNCTION(geoip_continent_code_by_name) {
	int id;
	if (geoip_generic_id(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_id_by_name, GEOIP_COUNTRY_EDITION, &id)) {
		if (id == 0) {
			RETURN_FALSE;
		} else {
			RETURN_STRING((char*)GeoIP_country_continent[id], 1);
		}
	}
}

#if LIBGEOIP_VERSION >= 1004005
/* {{{ IPV6 functions */
PHP_FUNCTION(geoip_country_code_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_code_by_name_v6, GEOIP_COUNTRY_EDITION_V6, 0);
}

PHP_FUNCTION(geoip_country_code3_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_code3_by_name_v6, GEOIP_COUNTRY_EDITION_V6, 0);
}

PHP_FUNCTION(geoip_country_name_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, (char* (*)(GeoIP*, const char*))GeoIP_country_name_by_name_v6, GEOIP_COUNTRY_EDITION_V6, 0);
}

PHP_FUNCTION(geoip_asnum_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name_v6, GEOIP_ASNUM_EDITION_V6, 1);
}

PHP_FUNCTION(geoip_domain_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name_v6, GEOIP_DOMAIN_EDITION_V6, 1);
}

#if LIBGEOIP_VERSION >= 1004008
PHP_FUNCTION(geoip_netspeedcell_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name_v6, GEOIP_NETSPEED_EDITION_REV1_V6, 1);
}
#endif

PHP_FUNCTION(geoip_isp_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_name_by_name_v6, GEOIP_ISP_EDITION_V6, 1);
}

PHP_FUNCTION(geoip_org_by_name_v6) {
	geoip_generic_string(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_org_by_name_v6, GEOIP_ORG_EDITION_V6, 1);
}

PHP_FUNCTION(geoip_region_by_name_v6) {
	geoip_generic_region(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_region_by_name_v6, GEOIP_CITY_EDITION_REV1_V6, GEOIP_CITY_EDITION_REV0_V6);
}

PHP_FUNCTION(geoip_record_by_name_v6) {
	geoip_generic_record(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_record_by_name_v6, GEOIP_CITY_EDITION_REV1_V6, GEOIP_CITY_EDITION_REV0_V6);
}

PHP_FUNCTION(geoip_id_by_name_v6) {
	int netspeed;
	if (geoip_generic_id(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_id_by_name_v6, GEOIP_NETSPEED_EDITION_REV1_V6, &netspeed)) {
		RETURN_LONG(netspeed);
	}
}

PHP_FUNCTION(geoip_continent_code_by_name_v6) {
	int id;
	if (geoip_generic_id(INTERNAL_FUNCTION_PARAM_PASSTHRU, GeoIP_id_by_name_v6, GEOIP_COUNTRY_EDITION_V6, &id)) {
		if (id == 0) {
			RETURN_FALSE;
		} else {
			RETURN_STRING((char*)GeoIP_country_continent[id], 1);
		}
	}
}
/* }}} */
#endif

/* {{{ proto boolean geoip_db_avail( [ int database ] ) */
PHP_FUNCTION(geoip_db_avail) {
	long edition;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &edition) == FAILURE) {
		return;
	}

	if (edition < 0 || edition >= NUM_DB_TYPES)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Database type given is out of bound.");
		return;
	}

	RETURN_BOOL(GeoIP_db_avail(edition));
}
/* }}} */

/* {{{ proto string geoip_db_filename( [ int database ] ) */
PHP_FUNCTION(geoip_db_filename) {
	long edition;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &edition) == FAILURE) {
		return;
	}

	if (edition < 0 || edition >= NUM_DB_TYPES)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Database type given is out of bound.");
		return;
	}

	if (NULL != GeoIPDBFileName[edition])
		RETURN_STRING(GeoIPDBFileName[edition], 1);	
}
/* }}} */

/* {{{ proto array geoip_db_get_all_info( ) */
PHP_FUNCTION(geoip_db_get_all_info) {
	int i;

	array_init(return_value);

	for (i=0; i < NUM_DB_TYPES; i++)
	{
		if (NULL != GeoIPDBDescription[i])
		{
			zval *row;
			ALLOC_INIT_ZVAL(row);
			array_init(row);

			add_assoc_bool(row, "available", GeoIP_db_avail(i));
			if (GeoIPDBDescription[i]) {
				add_assoc_string(row, "description", (char *)GeoIPDBDescription[i], 1);
			}
			if (GeoIPDBFileName[i]) {
				add_assoc_string(row, "filename", GeoIPDBFileName[i], 1);
			}

			add_index_zval(return_value, i, row);
		}
	}
}
/* }}} */

/* {{{ proto string geoip_database_info( [ int database ] )
   Returns GeoIP Database information */
PHP_FUNCTION(geoip_database_info)
{
	GeoIP * gi;
	char * db_info;
	long edition = GEOIP_COUNTRY_EDITION;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|l", &edition) == FAILURE) {
		return;
	}

	if (edition < 0 || edition >= NUM_DB_TYPES)
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Database type given is out of bound.");
		return;
	}

	if (GeoIP_db_avail(edition)) {
		gi = GeoIP_open_type(edition, GEOIP_STANDARD);
	} else {
		if (NULL != GeoIPDBFileName[edition])
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Required database not available at %s.", GeoIPDBFileName[GEOIP_COUNTRY_EDITION]);
		else
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Required database not available.");
		return;
	}

	db_info = GeoIP_database_info(gi);
	GeoIP_delete(gi);

	RETVAL_STRING(db_info, 1);
	free(db_info);
}
/* }}} */

#if LIBGEOIP_VERSION >= 1004001
/* {{{ proto string geoip_region_name_by_code( string country_code, string region_code )
   Returns the region name for some country code and region code combo */
PHP_FUNCTION(geoip_region_name_by_code) {
	char * country_code = NULL;
	char * region_code = NULL;
	const char * region_name;
	int countrylen, regionlen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &country_code, &countrylen, &region_code, &regionlen) == FAILURE) {
		return;
	}

	if (!countrylen || !regionlen) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "You need to specify the country and region codes.");
		RETURN_FALSE;
	}

	region_name = GeoIP_region_name_by_code(country_code, region_code);
	if (region_name == NULL) {
		RETURN_FALSE;
	}
	RETURN_STRING((char*)region_name, 1);
}
/* }}} */
#endif

#if LIBGEOIP_VERSION >= 1004001
/* {{{ proto string geoip_time_zone_by_country_and_region( string country, string region )
   Returns the time zone for some country code and region code combo */
PHP_FUNCTION(geoip_time_zone_by_country_and_region) {
	char * country = NULL;
	char * region = NULL;
	const char * timezone;
	int countrylen, arg2len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &country, &countrylen, &region, &arg2len) == FAILURE) {
		return;
	}

	if (!countrylen) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "You need to specify at least the country code.");
		RETURN_FALSE;
	}

	timezone = GeoIP_time_zone_by_country_and_region(country, region);
	if (timezone == NULL) {
		RETURN_FALSE;
	}
	RETURN_STRING((char*)timezone, 1);
}
/* }}} */
#endif

#ifdef HAVE_CUSTOM_DIRECTORY
/* {{{ proto void geoip_setup_custom_directory( string directory )
   Sets the custom directory for GeoIP databases */
PHP_FUNCTION(geoip_setup_custom_directory) {
	char * dir = NULL;
	int dirlen;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &dir, &dirlen) == FAILURE) {
		return;
	}

	GEOIP_G(set_runtime_custom_directory) = 1;
	geoip_change_custom_directory(dir);
}
/* }}} */
#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
