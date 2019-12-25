# -Calculate-pi-using-Threads
An interesting way of calculating 𝜋 (pi) is to use a technique known as Monte Carlo, which involves randomization. This technique works as follows: Suppose you have a circle inscribed within a square, as shown in Figure 1 (Assume that the radius of this circle is 1). First, generate a series of random points as simple (x, y) coordinates. These points must fall within the Cartesian coordinates that bound the square. Of the total number of random points that are generated, some will occur within the circle. Next, estimate pi by performing the following calculation: π= 4× (number of points in circle) / (total number of points)  Write a multithreaded version of this algorithm, where you create several threads (at least two excluding the main thread), each of which generates random points (for an example 100 points) and determines if the points fall within the circle. Each thread will have to update two global variables, the number of points in the circle and the total number of points. While child threads are generating random points and updating the global variables, the main thread continuously calculates the value of pi and display it on the console. Main thread finishes the calculation when all child threads exited. Experiment with the number of points generated by a thread and the number of threads. As a general rule, the greater the number of points, the closer the approximation to pi. Make sure you protect against race conditions on updates to the shared global variables by using mutex locks.
