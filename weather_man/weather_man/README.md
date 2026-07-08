## Install the official Arduino CLI binary

> ```
> curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
> ```

This downloads the binary into your current directory.

Move it into your PATH:

> ```
> sudo mv bin/arduino-cli /usr/local/bin/
> ```

Verify:

> ```
> which arduino-cli
> ```

It should now print:

> ```
> /usr/local/bin/arduino-cli
> ```

Check that board detection works

> ```
> arduino-cli board list
> ```

## Install the ESP32 core

