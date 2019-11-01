#!/bin/bash
set -ev

make test
./build/tests > /dev/null

exit 0
