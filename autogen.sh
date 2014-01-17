#!/bin/sh
autopoint --force
AUTOPOINT='intltoolize --automake --copy' autoreconf --force --install --verbose
