<?php
/** @generate-function-entries */
/**
 * @param int $database
 * @return string|null
 */
function geoip_database_info(int $database = GEOIP_COUNTRY_EDITION): ?string {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code_by_addr(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code_by_addr_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_domain_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_domain_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code3_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_code3_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_name_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_country_name_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_continent_code_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_continent_code_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_org_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_org_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return array|false
 */
function geoip_record_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return array|false
 */
function geoip_record_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return int
 */
function geoip_id_by_name(string $hostname): int {}

/**
 * @param string $hostname
 * @return int
 */
function geoip_id_by_name_v6(string $hostname): int {}

/**
 * @param string $hostname
 * @return array|false
 */
function geoip_region_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return array|false
 */
function geoip_region_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_isp_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_isp_by_name_v6(string $hostname) {}

/**
 * @param int $database
 * @return bool|null
 */
function geoip_db_avail(int $database): ?bool {}

/**
 * @return array
 */
function geoip_db_get_all_info(): array {}

/**
 * @param int $database
 * @return string|null
 */
function geoip_db_filename (int $database): ?string {}

/**
 * @param string $country_code
 * @param string $region_code
 * @return string|false
 */
function geoip_region_name_by_code(string $country_code, string $region_code) {}

/**
 * @param string $country_code
 * @param string|null $region_code
 * @return string|false
 */
function geoip_time_zone_by_country_and_region(string $country_code, ?string $region_code) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_asnum_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_asnum_by_name_v6(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_netspeedcell_by_name(string $hostname) {}

/**
 * @param string $hostname
 * @return string|false
 */
function geoip_netspeedcell_by_name_v6(string $hostname) {}

/**
 * @param string $path
 * @return void
 */
function geoip_setup_custom_directory(string $path) {}
