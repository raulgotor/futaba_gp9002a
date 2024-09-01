Futaba GP9002A
######

Overview
********

For the time being this repository is a driver approach to a VFD Futaba GP9002A

Requirements
************

The code is tailored to run in a STM32 Nucleo F401:

#. Connect MOSI, CLK, CS and C/D to ``PA7``, ``PA5``, ``PB6`` and ``PA9`` respectively
#. Power the VFD board with the 5V and GND of the nucleo board


Building and Running
********************

Build and flash Blinky as follows, changing ``reel_board`` for your board:

.. code-block:: DTS

    west build -b nucleo_f401re -p; west flash