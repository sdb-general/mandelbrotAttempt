# mandelbrotAttempt

Here is a short test project to generate a plot of the Mandelbrot set, just to familiarise myself with SDL.

This branch is a little messy, but will utilise all the available threads.

The included Makefile should put together the executable. Just type ```make```.

This branch can accept some command-line arguments, such as below:

```./game.exe --centrex -0.68 --centrey -0.2995 --zoom 0.001```

There is lots to do, still, namely:
  Tidy up and refactor everything \\
  Add a lot of comments \\
  Move the threadpool to a separate file \\
  Optimise calculation of Mandelbrot numbers \\
