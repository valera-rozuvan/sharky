#!/bin/bash
set -ev

make test
./build/tests

exit 0
