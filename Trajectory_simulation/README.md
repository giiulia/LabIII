# Trajectory simulations 

The path taken by muons that interacted with S1 toward S2 depends on the inclination of the trajectory of each of them.
To obtain the average path between S1 and S2, we developed a simulation in C++ that is based on mathematical calculations whereby a straight line:
- with a slope defined by two angles
- fixed in space by a gaicent point on S1
can inetersect a rectangle 80x30 cm <sup>2</sup> (S2) distant L from S1.

When coincidence is possible, the [main.cpp](/Trajectory_simulation/main.cpp) program, supported by the [checks.h](//Trajectory_simulation/checks.h) library, reports in a histogram the path taken by the particle using the [TH1F](https://root.cern.ch/doc/master/classTH1F.html) class of ROOT CERN. Histograms are shown in [Simulated_paths](/Trajectory_simulation/Graphs/Simulated_paths) and the 2D histogram 

