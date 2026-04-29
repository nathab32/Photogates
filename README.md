# Photogates

## Description

Photogates allow precise, automatic timing of objects moving between two points. The photogates trigger automatically when a laser beam is interrupted, providing much faster response times than a human ever could with a stopwatch.

Commonly available solutions online cost at least $50, with high resolution ones costing hundreds of dollars. This design seeks lower the barrier to precise timing by using commonly available parts and 3D printed materials for a cost-effective design.

## Features

## Basic Usage

1. Position the two lasers perpendicular to the direction of travel at your specified distance.

2. Position the two phototransistors directly across from the two lasers. Each laser should hit straight onto a phototransistor.

3. Plug the lasers into the right side of the main module, and the phototransistors into the left side. Both the lasers and phototransistors have polarities, and will not function if plugged in wrong.

4. Before powering up the module, cover both lasers so that calibration can occur. Alternatively, plug the module in first, cover the lasers, and then press `R` to calibrate.

5. After calibration, make sure that the phototransistors are functioning by each beam independently. One of the interruptions should start the timing, indicated by `Timing...` on the LCD. The other interruption should stop the timing.
   - This is a good time to check the order of the phototransistors. If the order is incorrect, then simply plug the phototransistor in the top slot into the bottom slot and vice versa.

6. If everything has been executed correctly, then your photogate should be ready for timing! If you need to recalibrate at any point, simply interrput both beams and press `R` again.

## Assembly

### Lasers

### Phototransistors

### Shield

### Final Assembly

## BOM

<!-- |Item|Part Number|Description|Quantity|Reference Designator|
|----|-----------|-----------|--------|--------------------|
|1|dfa|adfads|adsfa|adsfa| -->

## Todo

- distance input for avg speed
- switch phototransistor 0 and 1 (automatically?)
