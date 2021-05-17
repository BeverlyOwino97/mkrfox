## SigFox technology for water resource monitoring
- The Arduino MKRFox 1200 is a learning and development board which contains the ATMEL SAMD21 micro controller, designed to integrate the core's low power-consumption and high performance with the Arduino's ease-of-use. 
- The MKRFOX1200 brings the Arduino Zero functionalities in the smaller form factor established by the Arduino MKR1000 and adding the SigFox connectivity to the Arduino platform.
- It can be programmed using Arduino Software (IDE) common to all Arduino boards and running both online and offline (you need to download and install it). 
- For more information on how to get started with the Arduino Software visit the Getting Started Page: https://support.sigfox.com/docs/callbacks-documentation

## Setup process
- Connect the Hardware
- Once the MKRFox is removed from the black foam, you can connect it with a USB cable to your PC/laptop. Once done, the green LED “ON” will be powered on. 

## Arduino IDE Setup:
After having MKRFox successfully connected to your machine, start the Arduino IDE previously downloaded and installed. You can alternatively use Arduino Web Editor online.
Next, go to Tools > Board > Boards Manager… and type in “Arduino SAMD”. Install the one provided by Arduino. This is needed to be able to choose MKRFox from the Arduino boards listed within the board manager. 
After you have installed **Arduino SAMD Boards**, go back to tab Tools > Board > Boards Manager… and choose “Arduino MKRFox1200”. 

## Retrieve ID and PAC numbers for Sigfox Backend
There is an example for the MKRFox 1200 device which allows you to setup the SigFox's backend for your board. 
After the MKRFox is selected and your machine has recognised it, go to your IDE. 
Select File > Examples > Arduino SigFox for MKRFox1200 > FirstConfiguration and run that code.
In setup() the Serial is initialized. This will allow you to insert your first SigFox message and to get the information you need to configure the SigFox's backend. Since the MKRFox1200 doesn't have an autoreset function associated to the Serial monitor opening, a Serial while is present. We also check that the SigFox module is present and can be used. 
In loop() we have no instructions since we don't need to do something more.
After this, we can read our ID and PAC that you have to use to register your board on the SigFox backend.

## Register your MKRFox 
- To register the board, you have to navigate to the Sigfox backend. This is a one time registration process, needed once for every MKRFox 1200 you own.
- Open the link https://buy.sigfox.com/activate and select the country where the user is residing or using it right now.
- After that, enter your ID and PAC number which was shown on the serial monitor after uploading the FirstConfiguration sketch. Next, input your credentials to get to the Sigfox portal home page and register your board.
