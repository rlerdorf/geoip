### This is the **_legacy (v1) GeoIP PHP extension_** for PHP 7.x and **_PHP 8.x._**
Unless you have old code that needs this, you might be better off using [GeoIP2](https://github.com/maxmind/GeoIP2-php).

#### Installing:
_Example for Debian (`apt`) and **PHP 8.2**_

```bash
apt install php8.2-dev geoip-bin geoip-database libgeoip-dev
git clone https://github.com/rlerdorf/geoip.git geoip && cd geoip
phpize8.2
./configure 
make
make test
make install
```

#### To use it:
1. Add line `extension=geoip.so` to your (PHP 8.2) `php.ini`
2. Restart your webserver e.g. `service apache2 restart`
3. If using FPM: `service php8.2-fpm restart`

