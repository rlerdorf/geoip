--TEST--
Checking geoip_country_code_by_addr and geoip_country_code_by_addr_v6
--SKIPIF--
<?php if (!extension_loaded("geoip") || !geoip_db_avail(GEOIP_COUNTRY_EDITION_V6)) print "skip"; ?>
--FILE--
<?php

var_dump(geoip_country_code_by_addr("128.100.100.128"));
var_dump(geoip_country_code_by_addr_v6("2620:101:f000:0:250:56ff:fe80:168e"));

?>
--EXPECTF--
string(2) "CA"
string(2) "CA"
