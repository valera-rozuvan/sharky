# Roadmap

LILO list for things to do on the project. Put new items at the top. Items towards the end of the list get more attention. Please mark items as done when appropriate.

## 2024 list

- complete enough of functionality to take part in [TCEC](https://tcec-chess.com/) (Top Chess Engine Championship)

## Things to do

- Windows build of the engine. Setup Visual Studio project. Add support for Windows native threads. Pthread library should only be used on `Linux`/`MacOS`/`*nix` systems.

- Setup simple infrastructure to test new code from Pull Requests against latest `master` version of the engine. Need to compare actual game play results. Unit tests and code coverage can continue to run on Travis CI.

- Use [emscripten-core/emscripten](https://github.com/emscripten-core/emscripten) to generate JavaScript build of the engine. Provide web demo for the engine using [ornicar/chessground](https://github.com/ornicar/chessground).

- Initial skeleton for depth-based monte carlo tree search. Provided a depth, the function must perform a monte carlo search along all available moves, up to a set depth. The function must be smart enough to know when no more improvement for a certain move is possible, and not look at it again. The function should return the move with the highest probability of success when time runs out, or there is no more sense in searching the available moves.

- Add time control parsing for UCI. The engine should be aware of how much time is has per move/per game.

- **[done]** Improve perft program. Enable passing as CLI options the following: depth, FEN string. Update Travis CI checks with perft depth 5 tests for various positions.

- **[done]** Remove `human` mode. What's human mode? Initial idea was to allow the user use the engine via CLI (text input) in a manual mode - like it's 1980s ;) Human mode was supposed to provide nice move output (PGN style), allow the user to quickly make moves without the wordy UCI syntax, etc. However, I have decided that the engine will support only UCI mode going forward. Several reasons for this. For one, the more code/features you have, the more bugs in code exist. For two, I don't foresee any usage of this feature - because these days it's so easy to connect an engine to a GUI, and play with it. For three, I want to simplify and minimize the code base.

- **[done]** Fix code related to thread killing. Actually wait for the thread to die, before exiting the program. Make sure that a new thread is not started until the old one is killed.
