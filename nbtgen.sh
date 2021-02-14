#!/bin/bash

for scheme in resource/message/nbt/*.nbt.proto; do
  echo "generating $scheme"
  nbtc "$scheme" -s lib/message/nbt -h include/minecpp/message/nbt -I minecpp/message/nbt
done