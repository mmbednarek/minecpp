# Schema Compiler

The schema compiler is a source-to-source compiler. It compiles `.schema` files you can find under `api/` directory.
The idea is to have schemas for common NBT or Network structured records, which
will greatly improve serialization of those structures.

## Schema format

Schema files should begin with package statement for example.
This is an effort to limit the symbol conflicts in different schema files.

```
package testing.example
```

You don't need to import anything, you can use any symbol included in the project.
After specifying the package you can define record you want to be generated.
You start with the `record` keyword, following with the record name.
Then you can list the properties within the brackets.
A property definition starts with the property name followed by the type
seperated with a colon. For example:

```
record Test {
    foo: int32
    bar: float64
}
```

The base types are:
- `int8`
- `int16`
- `int32`
- `int64`
- `uint8`
- `uint16`
- `uint32`
- `uint64`
- `float32`
- `float64`
- `string`
- `map[key, value]`
- `list[type]`
- `optional[type]`
- `variant[...]`

In order to refer to records in other files you don't need to import anything. 
You just need to specify the part of the package that differs from the current one.
For example if you're in a package `testing.example` and you want to refer to a record `Foo`
in package `testing.bar` you only need to specify the `bar` part because `testing` is common.
This results in `bar.Foo` symbol.

## CLI Interface

For compilation, you need to specify the source directory and not the individual source files (flag `-i`). 
It's also necessary to provide the destination headers `-h` and source directories `-s`.
Finally, you can specify the include prefix of the generated files in the project `-I`.
For example:
```
schema_compiler -i ./api/minecpp/nbt -s library/api/minecpp/nbt/src -h library/api/minecpp/nbt/include/minecpp/nbt -I minecpp/nbt
```
