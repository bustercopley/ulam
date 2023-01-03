# Hacking

Here is some wisdom to help you build and run this project.

## Developer mode

Build system targets that are only useful for developers of this project are
hidden if the `ulam_DEVELOPER_MODE` option is disabled. Enabling this
option makes tests and other developer targets and options available. Not
enabling this option means that you are a consumer of this project and thus you
have no need for these targets and options.

### Presets

This project makes use of [presets][1] to simplify the process of configuring
the project. As a developer, you are recommended to always have the [latest
CMake version][2] installed to make use of the latest Quality-of-Life
additions.

You have a few options to pass `ulam_DEVELOPER_MODE` to the configure
command, but this project prefers to use presets.

As a developer, you should create a `CMakeUserPresets.json` file at the root of
the project. See the included `CMakeUserPresets.sample.json` for an example.

`CMakeUserPresets.json` is also the perfect place in which you can put all
sorts of things that you would otherwise want to pass to the configure command
in the terminal.

### Configure, build and run

If you followed the above instructions, then you can configure, build and test
the project respectively with the following commands from the project root on
any operating system with any build system:

```sh
cmake --preset=dev
cmake --build --preset=dev
cmake --build --preset=dev --target=run-exe
```

Please note that the build command accepts a `-j` flag to specify the number
of jobs to use, which should ideally be specified to the number of threads your
CPU has. You may also want to add that to your preset using the `jobs` property,
see the [presets documentation][1] for more details.

### Developer mode targets

These are targets you may invoke using the build command from above, with an
additional `-t <target>` flag:

#### `format-check` and `format-fix`

These targets run the clang-format tool on the codebase to check errors and to
fix them respectively. Customization available using the `FORMAT_PATTERNS` and
`FORMAT_COMMAND` cache variables.

#### `run-exe`

Runs the executable target `ulam_exe`.

[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://cmake.org/download/
