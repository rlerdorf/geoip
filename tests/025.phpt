--TEST--
Checking geoip_continent_code_by_name
--SKIPIF--
<?php if (!extension_loaded("geoip") || !geoip_db_avail(GEOIP_COUNTRY_EDITION)) print "skip"; ?>
--FILE--
<?php

var_dump(geoip_continent_code_by_name("128.100.100.128"));
var_dump(geoip_continent_code_by_name("0.0.0.0"));

?>
--EXPECT--
string(2) "NA"
bool(false)
