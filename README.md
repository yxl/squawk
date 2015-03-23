Squawk js
===================

[Squawk](https://java.net/projects/squawk/pages/SquawkDevelopment) is a Java micro edition virtual machine for embedded system and small devices. I ported to JavaScript using [emscripten](http://emscripten.org).

Build under Ubuntu
-----

Download and unzip portable emscripten SDK to a directory, say `EMSDK_PORTABLE`:
<http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html>

Install and activate the emscripten SDK under `EMSDK_PORTABLE`:

```
./emsdk update
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
sudo apt-get install nodejs-legacy
```

Run `jsbld.sh` under `root` directory of the project source code tree.
A demo file named `index.html` will be launched after building is done.

Demo
-----

The demo file is `index.html`, which is generated after building and could also be accessed online from <http://yxl.github.io/squawk/>.

License
-----

Released under the same lincense of GPL 2.0 as the original project.
