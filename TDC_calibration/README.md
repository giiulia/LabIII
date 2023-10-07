# TDC calibration

Running the program [TDC.c](/CAMAC_modules/TDC.c) on the PC interfaced with the CRATE CONTROLLER we got the channels proportional to each coincidence detected. The
values were saved and confronted with known time intervals (for example using delays due to specific cables). Through a **linear interpolation** of the [plot](/TDC_calibration/Graphs/fit_calibrazione_TDC1.pdf) 
we got the parameters needed to convert **channels into nanoseconds**.
