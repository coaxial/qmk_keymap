#! /usr/bin/env bash

echo "v$1 ($2)"

cat << EOF >> version.h
#define CXL_VERSION "$1"
#define CXL_BUILD_DATE "$2"
EOF