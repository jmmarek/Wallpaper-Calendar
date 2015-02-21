#!/bin/bash
aclocal
intltoolize
autoreconf --install
automake --add-missing
echo 'Now you can run ./configure and make'
