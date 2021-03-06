# Base Cinder App

This is a wrapper around Cinder's API to quickly get objects drawn on the screen.

The largest convienince Base Cinder App brings are the `SimulationObject` and `mSimulationObjectsMap` struct and map, which dynamically keep track of objects. SimulationObject struct handles drawing them and provides access to transform each object using its Key name.

## Getting started

Run `install.sh`, which will clone submodules and build them. It will also build the examples in the examples directory. Or.. [Cinder](https://github.com/cinder/Cinder.git) is a submodule of this repository. The submodule is located at ./externals/Cinder and is used by CMake to build the Base Cinder App. Please run `git submodule update --init --recursive` after cloning this repo or clone with the `--recursive` option to automatically fetch Cinder. You will need to build Cinder afterwards to generate the .lib files.

For a quick start, clone the [Simple app](./examples/Simple), which has a usable CMakeLists.txt file, and creates the necessary method overrides and Macros calls to create a Cinder app instance, as well as draw two cubes.

See the [Examples directory](./examples) for other examples.

### SimulationObject

`SimulationObject` is a struct. It stores a geom::Source, generates the gl::BatchRef and handles the transformations and drawing of a geom::Source.

- Below is an example creating a Cube, initializing SimulationObject with the cube, and then adding the cube to `mSimulationObjectsMap` with the name "cube". Cube will be automatically drawn in the next frame.
    ```
    geom::SourceMods slice = geom::Cube();
    SimulationObject cube(slice >> geom::Translate(ci::vec3(0, 2, 0)), shader);
    mSimulationObjectsMap["cube"] = cube;
    ```
- Below is accessing the cube we created above and adding transformations. Notice that transformations are absolute from the initial location.
    ```
    SimulationObject* cube = &mSimulationObjectsMap["cube"];
    cube->translation = ci::vec3(2 + cube->translation.x, 0, 0);
    cube->rotation = angleAxis(.5f + cube->rotation.w, vec3( cube->rotation.x, cube->rotation.y, cube->rotation.z)
    cube->scale = ci::vec3(1 + cube->scale.x, 0, 0);
    ```
- Example change color:
    ```
    Color redColor = Color( CM_RGB, 1, 0, 0 ); // or ColorA
    cube2->color = redColor;
    ```

## References

- [Cinder Documentation](https://libcinder.org/docs/reference/index.html)
- [Neuropod insect simulation](https://github.com/neuroprod/InsectRobotSimulation) - This is a fantastic robotics project that's built in Cinder.
- [Cinder GUI example](https://github.com/cinder/Cinder/blob/master/samples/ParamsBasic/src/ParamsBasicApp.cpp)