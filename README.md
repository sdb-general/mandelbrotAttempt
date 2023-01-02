# mandelbrotAttempt

Here is a short test project to generate a plot of the Mandelbrot set, just to familiarise myself with SDL.

This branch is a little messy, but will utilise all the available threads.

The included Makefile should put together the executable. Just type ```make```.

This branch can accept some command-line arguments, such as below:

```./game.exe --centrex -0.68 --centrey -0.2995 --zoom 0.001```

The most recent change enables the use of the ```--scale``` argument - values greater than 1 will reduce the quality (and evaluation time)
It's pretty rudimentary, but removes the need to calculate one set of iterations per pixel.

We can also set the max number of iterations using ```--iters```. default value is 500.

There is lots to do, still, namely:

  Tidy up and refactor everything 

  Add a lot of comments 

  Move the threadpool to a separate file 

  add in SIMD  calculations to speed up evaluation

  the real thing adds a colour proportional to the number of iters required - this requires a little refactoring and a map from int -> rgb

  Refactor to use an SDL surface instead of passing the renderer around as this is a real bottleneck