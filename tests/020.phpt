--TEST--
Checking geoip_record_by_name_v6
--SKIPIF--
<?php if (!extension_loaded("geoip") || !geoip_db_avail(GEOIP_CITY_EDITION_REV0_V6)) print "skip"; ?>
--FILE--
<?php

var_dump(geoip_record_by_name_v6('2001:4860:4860::8888'));

?>
--EXPECTF--
array(11) {
  ["continent_code"]=>
  string(2) "NA"
  ["country_code"]=>
  string(2) "US"
  ["country_code3"]=>
  string(3) "USA"
  ["country_name"]=>
  string(13) "United States"
  ["region"]=>
  string(0) "%S"
  ["city"]=>
  string(0) "%S"
  ["postal_code"]=>
  string(0) "%S"
  ["latitude"]=>
  float(%f)
  ["longitude"]=>
  float(%f)
  ["dma_code"]=>
  int(%i)
  ["area_code"]=>
  int(%i)
}
