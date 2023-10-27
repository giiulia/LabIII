# Derivation of the muon velocity

The goal is to extrapolate the muon velocity from the [plot](/Muons_velocity/velocity_graph.pdf) of four points of times Vs average distances traveled by muons. Through a linear fit, we derived the angular coefficient m and the intercept q; from the former we could calculate the velocity of muons passing in front of the detectors: v [m/s] = 1/m * 10<sup>9</sup>.

The graphs that display the [energy distribution](/Muons_velocity/Graphs/Energy_distributions) for detector 1 and 2 (outputs of ADC1 and ADC2) show that the most frequent energies are collected in a range between 120 ch - 380ch for ADC1 and 60ch - 240ch for ADC2. We consider **energy intervals** like these the **most populated by cosmic muons** since those particles will have similar energies; therefore only counts that occour in these intervals were considered as useful data.\
The time measurements had to undergo a subsequent **preliminary correction because of amplitude errors** that occur when energy deposited by the same particle in different detectors is not the same.

Calculations for time correction were done through:
- [t_profile.cpp](/Muons_velocity/t_profile.cpp), this program creates a particular yet useful graph with [TGraphErrors](https://root.cern.ch/doc/master/classTGraphErrors.html) of times Vs energies in a way that events with similar energy are meadiated into being represented as only one point in the graph; in this way the fluctuations are smaller and the apparent dependence of the time interval from ADC1 or ADC2 is more easily quantified with **numerical parameters** tau and Vs (wich we presume different for scintillators 1 and 2).
- [calc_mean_parameters.cpp](/Muons_velocity/calc_mean_parameters.cpp), having four distances we were able to **meadiate** between them in order  have only one estimate for parameter.
- [correct_times.cpp](/Muons_velocity/correct_times.cpp), new data files were created using the **average corrective parameters** and considering only events in the **energy range of choice**. This time intervals are now correct and we can onserve the constant trend by the graphs in the directory [TimesVSEnergies_corrected](/Muons_velocity/Graphs/TimesVSEnergies_corrected).

The times are corrected, how about the distances? We know that the mean distance traveled by muons is not the one corresponding to the vertical trajectory but it can be estrapolated by the **average path** of the histogram generated with previous [simulations](/Trajectory_simulation).

Those exposed are the data used to plot times Vs distances, note that in this [graph](/Muons_velocity/velocity_graph.pdf) **systematic errors** due to the subjective choice made in determining the ADC channels to be considered were also considered. To estimate the error due to this choice, we made several choices of energy interval and evaluated the difference that subsequently occurred in determining the mean time interval of this interval.
