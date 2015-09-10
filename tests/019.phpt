--TEST--
Checking setting manually ini for custom_directory
--SKIPIF--
<?php if (!extension_loaded("geoip")) print "skip"; ?>
--INI--
geoip.custom_directory="/test/"
--FILE--
<?php

var_dump( geoip_db_filename(GEOIP_COUNTRY_EDITION) );
var_dump( ini_get('geoip.custom_directory') );

ini_set('geoip.custom_directory','/some/other/place');
var_dump( geoip_db_filename(GEOIP_COUNTRY_EDITION) );
var_dump( ini_get('geoip.custom_directory') );

?>
--EXPECT--
string(15) "/test/GeoIP.dat"
string(6) "/test/"
string(27) "/some/other/place/GeoIP.dat"
string(17) "/some/other/place"
