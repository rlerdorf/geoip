# Changelog

## 1.4.0 - 2026-04-06

- Add PIE (PHP Installer for Extensions) support
- Add NULL check on GeoIP_open_type() return to prevent segfault on corrupt/unreadable DB files
- Remove pre-PHP 7.2 compatibility shims (minimum PHP version is now 7.2)
- Remove unused le_geoip variable
- Replace compat macros with native PHP 7+ API calls
- Initialize uninitialized variable in geoip_time_zone_by_country_and_region()
- Add tests for geoip_country_code_by_name(), geoip_country_code3_by_name(), geoip_country_name_by_name(), geoip_continent_code_by_name()
- Verified clean build and tests on PHP 8.4 and 8.5
- Verified zero memory leaks under Valgrind

## 1.3.0 - 2021-01-13

- Add PHP 8 support
- Drop PHP 5 support
- Add geoip_country_code_by_addr() and geoip_country_code_by_addr_v6()

## 1.1.1

- Add IPv6 support (geoip_country_code_by_*_v6)
- PHP 7 support (thanks to Adam and Dan Ackroyd)

## 1.1.0-dev - 2012-xx-xx

- Add geoip_setup_custom_directory() to setup custom directories per request
- Remove E_NOTICES for IPs not found in database
- Fix a segfault with geoip_db_get_all_info() on newer libs (bug #64692)
- Add support for geoip_netspeedcell_by_name(), geoip_asnum_by_name() and geoip_domain_by_name() (bug #67121)
- Fix memory leak with custom directories (bug #67138)
- Support changing custom directory via ini_set() (bug #61607)

## 1.0.8 - 2011-10-23

- Windows support
- Fix segfault with newer geoip libraries and geoip_db_get_all_info() (bug #60066)
- Use X-Macros for repeated code
- Updated tests

## 1.0.7 - 2009-03-11

- Do not issue a NOTICE when values don't exist for timezone and region name (as added in 1.0.4)
- Fix a compile issue on FreeBSD
- Try to be bulletproof on library features detection

## 1.0.6 - 2009-01-20

- Fix compile bug when multiple GeoIP libs are installed (bug #15372)

## 1.0.5 - 2008-12-19

- Small bug in phpinfo() when printing version number could crash PHP

## 1.0.4 - 2008-12-19

- Fix memleaks (bug #14851)
- Small patch for MacPorts by jhohle
- Add geoip_time_zone_by_country_and_region() and geoip_region_name_by_code() (thanks to Sid Dunayer)
- Add continent_code field for City Database, only if using GeoIP lib 1.4.3 or newer

## 1.0.3 - 2008-06-12

- Change license from PHP 3.0 to PHP 3.01
- Add geoip_continent_code_by_name() to get continent instead of country
- Fix a small casting issue (compiler warning)
- Fix missing entries in geoip_record_by_name (bug #14131)

## 1.0.2 - 2007-11-20

- Add geoip_isp_by_name (patch by Yannick Gard)

## 1.0.1 - 2007-08-22

- Add geoip_db_avail() to check for DB availability (file found)
- Add geoip_db_filename() to get the internal file name of the library
- Add geoip_db_get_all_info() to fetch all info about all database types
- Add some tests so that make test can crunch something
- Add database file path and name in warning when DB is not found
- Add geoip.custom_directory php.ini option to change default path for DBs

## 1.0.0 - 2007-08-14

- Marked as stable
- Fix wrong version number inside extension

## 0.2.0 - 2006-08-22

- Initial PECL Release
- Fix various memory leaks
- Register the C API constants in PHP

## 0.1.3 - 2006-07-10

- Missing PHP function prototypes (Olivier Hill)
- Fix code foldings in Emacs
- Output E_NOTICES instead of E_WARNING for non-fatal errors
- Return type of longitude/latitude should be DOUBLE not LONG

## 0.1.2 - 2006-05-19

- Moved argument parsing before GeoIP creation (Guenter Knauf)
- Moved GeoIP_delete() calls to prevent leaks on error paths
- Fixed segfault when RETURN_STRING() was called with NULL on lookup failure
- Added php.ini entry parsing for geoip.database_standard
- Added config.m4 (Jonathan Whiteman)

## 0.1.1 - 2005-09-21

- Initial release (Matthew Fonda)
