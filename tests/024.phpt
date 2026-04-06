--TEST--
Checking geoip_country_name_by_name
--SKIPIF--
<?php if (!extension_loaded("geoip") || !geoip_db_avail(GEOIP_COUNTRY_EDITION)) print "skip"; ?>
--FILE--
<?php

var_dump(geoip_country_name_by_name("128.100.100.128"));

?>
--EXPECT--
string(6) "Canada"
