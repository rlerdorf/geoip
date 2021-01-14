/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: dd9427439072e37f6d6b243bf18311885642a8b8 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_geoip_database_info, 0, 0, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, database, IS_LONG, 0, "GEOIP_COUNTRY_EDITION")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_geoip_country_code_by_name, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, hostname, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_geoip_country_code_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_code_by_addr arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_code_by_addr_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_domain_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_domain_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_code3_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_code3_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_name_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_country_name_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_continent_code_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_continent_code_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_org_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_org_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_record_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_record_by_name_v6 arginfo_geoip_country_code_by_name

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_geoip_id_by_name, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, hostname, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_geoip_id_by_name_v6 arginfo_geoip_id_by_name

#define arginfo_geoip_region_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_region_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_isp_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_isp_by_name_v6 arginfo_geoip_country_code_by_name

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_geoip_db_avail, 0, 1, _IS_BOOL, 1)
	ZEND_ARG_TYPE_INFO(0, database, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_geoip_db_get_all_info, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_geoip_db_filename, 0, 1, IS_STRING, 1)
	ZEND_ARG_TYPE_INFO(0, database, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_geoip_region_name_by_code, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, country_code, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, region_code, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_geoip_time_zone_by_country_and_region, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, country_code, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, region_code, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_geoip_asnum_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_asnum_by_name_v6 arginfo_geoip_country_code_by_name

#define arginfo_geoip_netspeedcell_by_name arginfo_geoip_country_code_by_name

#define arginfo_geoip_netspeedcell_by_name_v6 arginfo_geoip_country_code_by_name

ZEND_BEGIN_ARG_INFO_EX(arginfo_geoip_setup_custom_directory, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(geoip_database_info);
ZEND_FUNCTION(geoip_country_code_by_name);
ZEND_FUNCTION(geoip_country_code_by_name_v6);
ZEND_FUNCTION(geoip_country_code_by_addr);
ZEND_FUNCTION(geoip_country_code_by_addr_v6);
ZEND_FUNCTION(geoip_domain_by_name);
ZEND_FUNCTION(geoip_domain_by_name_v6);
ZEND_FUNCTION(geoip_country_code3_by_name);
ZEND_FUNCTION(geoip_country_code3_by_name_v6);
ZEND_FUNCTION(geoip_country_name_by_name);
ZEND_FUNCTION(geoip_country_name_by_name_v6);
ZEND_FUNCTION(geoip_continent_code_by_name);
ZEND_FUNCTION(geoip_continent_code_by_name_v6);
ZEND_FUNCTION(geoip_org_by_name);
ZEND_FUNCTION(geoip_org_by_name_v6);
ZEND_FUNCTION(geoip_record_by_name);
ZEND_FUNCTION(geoip_record_by_name_v6);
ZEND_FUNCTION(geoip_id_by_name);
ZEND_FUNCTION(geoip_id_by_name_v6);
ZEND_FUNCTION(geoip_region_by_name);
ZEND_FUNCTION(geoip_region_by_name_v6);
ZEND_FUNCTION(geoip_isp_by_name);
ZEND_FUNCTION(geoip_isp_by_name_v6);
ZEND_FUNCTION(geoip_db_avail);
ZEND_FUNCTION(geoip_db_get_all_info);
ZEND_FUNCTION(geoip_db_filename);
ZEND_FUNCTION(geoip_region_name_by_code);
ZEND_FUNCTION(geoip_time_zone_by_country_and_region);
ZEND_FUNCTION(geoip_asnum_by_name);
ZEND_FUNCTION(geoip_asnum_by_name_v6);
ZEND_FUNCTION(geoip_netspeedcell_by_name);
ZEND_FUNCTION(geoip_netspeedcell_by_name_v6);
ZEND_FUNCTION(geoip_setup_custom_directory);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(geoip_database_info, arginfo_geoip_database_info)
	ZEND_FE(geoip_country_code_by_name, arginfo_geoip_country_code_by_name)
	ZEND_FE(geoip_country_code_by_name_v6, arginfo_geoip_country_code_by_name_v6)
	ZEND_FE(geoip_country_code_by_addr, arginfo_geoip_country_code_by_addr)
	ZEND_FE(geoip_country_code_by_addr_v6, arginfo_geoip_country_code_by_addr_v6)
	ZEND_FE(geoip_domain_by_name, arginfo_geoip_domain_by_name)
	ZEND_FE(geoip_domain_by_name_v6, arginfo_geoip_domain_by_name_v6)
	ZEND_FE(geoip_country_code3_by_name, arginfo_geoip_country_code3_by_name)
	ZEND_FE(geoip_country_code3_by_name_v6, arginfo_geoip_country_code3_by_name_v6)
	ZEND_FE(geoip_country_name_by_name, arginfo_geoip_country_name_by_name)
	ZEND_FE(geoip_country_name_by_name_v6, arginfo_geoip_country_name_by_name_v6)
	ZEND_FE(geoip_continent_code_by_name, arginfo_geoip_continent_code_by_name)
	ZEND_FE(geoip_continent_code_by_name_v6, arginfo_geoip_continent_code_by_name_v6)
	ZEND_FE(geoip_org_by_name, arginfo_geoip_org_by_name)
	ZEND_FE(geoip_org_by_name_v6, arginfo_geoip_org_by_name_v6)
	ZEND_FE(geoip_record_by_name, arginfo_geoip_record_by_name)
	ZEND_FE(geoip_record_by_name_v6, arginfo_geoip_record_by_name_v6)
	ZEND_FE(geoip_id_by_name, arginfo_geoip_id_by_name)
	ZEND_FE(geoip_id_by_name_v6, arginfo_geoip_id_by_name_v6)
	ZEND_FE(geoip_region_by_name, arginfo_geoip_region_by_name)
	ZEND_FE(geoip_region_by_name_v6, arginfo_geoip_region_by_name_v6)
	ZEND_FE(geoip_isp_by_name, arginfo_geoip_isp_by_name)
	ZEND_FE(geoip_isp_by_name_v6, arginfo_geoip_isp_by_name_v6)
	ZEND_FE(geoip_db_avail, arginfo_geoip_db_avail)
	ZEND_FE(geoip_db_get_all_info, arginfo_geoip_db_get_all_info)
	ZEND_FE(geoip_db_filename, arginfo_geoip_db_filename)
	ZEND_FE(geoip_region_name_by_code, arginfo_geoip_region_name_by_code)
	ZEND_FE(geoip_time_zone_by_country_and_region, arginfo_geoip_time_zone_by_country_and_region)
	ZEND_FE(geoip_asnum_by_name, arginfo_geoip_asnum_by_name)
	ZEND_FE(geoip_asnum_by_name_v6, arginfo_geoip_asnum_by_name_v6)
	ZEND_FE(geoip_netspeedcell_by_name, arginfo_geoip_netspeedcell_by_name)
	ZEND_FE(geoip_netspeedcell_by_name_v6, arginfo_geoip_netspeedcell_by_name_v6)
	ZEND_FE(geoip_setup_custom_directory, arginfo_geoip_setup_custom_directory)
	ZEND_FE_END
};
