--TEST--
Checking timezone info with (some) empty fields
--SKIPIF--
<?php if (!extension_loaded("geoip")) print "skip"; ?>
--POST--
--GET--
--FILE--
<?php

var_dump(geoip_time_zone_by_country_and_region('US','MA'));
var_dump(geoip_time_zone_by_country_and_region('DE'));
var_dump(geoip_time_zone_by_country_and_region('',''));
var_dump(geoip_time_zone_by_country_and_region('','MA'));

?>
--EXPECTF--
string(16) "America/New_York"
string(13) "Europe/Berlin"

Warning: geoip_time_zone_by_country_and_region(): You need to specify at least the country code. in %s on line %d
bool(false)

Warning: geoip_time_zone_by_country_and_region(): You need to specify at least the country code. in %s on line %d
bool(false)
