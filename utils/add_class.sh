#!/usr/bin/env bash

class_name=$1

class_header_path="include/minecpp/$(echo $class_name | sed 's/::/\//g').h"
class_include_path="minecpp/$(echo $class_name | sed 's/::/\//g').h"
class_source_path="lib/$(echo $class_name | sed 's/::/\//g').cpp"

echo $class_header_path
echo $class_source_path

echo "
#include <$class_include_path>

namespace

"
