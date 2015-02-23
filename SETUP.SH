#!/bin/bash
aclocal
intltoolize
autoreconf --install
automake --add-missing
echo 'Now you can run ./configure or ./configure --prefix=/usr and make'
