# Rush Hour

Par Guillaume Ortega et Edouard Menayde.

## Performance analysis and memory usage

Using `perf` we can analyse the performance of our program for a given situation to solve.

Using `mprof` (provided by package [http://jmdana.github.io/memprof/](http://jmdana.github.io/memprof/)) we can 
measure memory usage overtime.

### v1

![](doc/perf01.png)

We can see `History:exists` is the function were our program spends most of the time.

![](doc/mprof01.png)
