# VigasocoSDL-AI

Headless version of https://github.com/luzbel/VigasocoSDL optimised to be used with https://github.com/LaAbadIAdelCrimen/abadia-gym

## How to compile and run on macOS

### 1. Install dependencies

You will need to install SDL and Boost. The easiest way to do this is using [Homebrew](https://brew.sh/).

```bash
brew install sdl boost
```

### 2. Compile the project

Once the dependencies are installed, you can compile the project by running the following command in the root directory:

```bash
make -f Makefile.MACOS
```

This will compile the main game server executable `abadIA` and place it in the `VigasocoSDL` directory.

### 3. Run the game server

To run the game server, navigate to the `VigasocoSDL` directory and run the `abadIA` executable:

```bash
cd VigasocoSDL
./abadIA
```

The server will start and listen for connections on port 4477.

### 4. Test the server

You can test if the server is running by sending it a request with `curl`:

```bash
curl -H "accept: application/json" http://localhost:4477/abadIA/game/current
```

This should return a JSON object with the current game state.