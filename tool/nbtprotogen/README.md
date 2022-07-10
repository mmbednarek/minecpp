# NBT Protocol Language

NBT Protocol Language is used to describe NBT structures.
Its syntax resembles the protocol buffer language with minor differences
to support more NBT features.
This tool is used to compile the `.nbt.proto` file into cpp source code.

- The syntax name is "nbt". (`syntax = "nbt";`)
- NBT tag label can be specified with `int32 name = 1 [label = "Label"]`.
- Repeated can be used multiple times `repeated repeated int32 name = 1;`.
- Import is not supported. (May be in the future)
- `int8` and `int16` are available. (`uint`'s are not)
- `ints` and `longs` are supported.
- `compound` is used for dynamic NBT structures.
- `map` is only supported with `string` as a key.

## Usage

```bash
nbtc scheme.nbt.proto -s [OUTPUT SOURCE DIRECTORY] -h [OUTPUT HEADER DIRECTORY] -I [INCLUDE HEADER DIRECTORY]
```

## Example nbt proto file

```protobuf
syntax = "nbt";
package minecpp.message.nbt;

message Player {
  string name = 1 [label = "Name"];
  int32 entity_id = 2 [label = "EntityId"];
  bytes uuid = 3 [label = "UUID"];
  map<string, string> metadata = 4 [label = "Metadata"];
}
```