--TEST--
Checking geoip_record_by_name_v6
--SKIPIF--
<?php if (!extension_loaded("geoip") || !geoip_db_avail(GEOIP_CITY_EDITION_REV0_V6)) print "skip"; ?>
--FILE--
<?php

var_dump(geoip_record_by_name_v6('2001:4860:4860::8888'));

?>
--EXPECT--
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
  string(0) ""
  ["city"]=>
  string(0) ""
  ["postal_code"]=>
  string(0) ""
  ["latitude"]=>
  float(38)
  ["longitude"]=>
  float(-97)
  ["dma_code"]=>
  int(0)
  ["area_code"]=>
  int(0)
}
