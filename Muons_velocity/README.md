# Derivation of the muon velocity

The **main program** here to look at is [muon_velocity.cpp](/Muons_velocity/muon_velocity.cpp),it [plots](/Muons_velocity/velocity_graph.pdf) foue points of times VS distance covered in average by muons
and with a linear fit it derives angular coefficient and intercept. From the former we were able to get the velocity of muons passing the detetctors.

The time measurements had to undergo preliminary correction because of amplitude errors that occur when the energy deposited by different particles is not the same. 
Correction calculations were done through:
- [t_profile.cpp](/Muons_velocity/t_profile.cpp)
- [calc_mean_parameters](/Muons_velocity/calc_mean_parameters.cpp)
