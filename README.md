# Smart-Irrigation-Sysytem

**Methodology**		

The planned system includes an Arduino NANO that is the management unit of the whole 
system, a temperature sensing element connected with an Arduino module that senses 
temperature of surroundings, a Rain sensing module for perceiving rain and managing 
irrigation with pumps accordingly. We tend to set a threshold price for moisture and humidity 
sensing elements thus once either of the two parameters crosses threshold motor driver 
modules activate the motor.
Deploying various sensors for ceaselessly observant these factors and fulfilling the wants can 
improve the strategy. The sensors will monitor soil wet levels, humidity, rain, Soil 
temperature ceaselessly. Usually this can be the foremost very important profit that the 
strategy of automation can give among the sphere of every agriculture..
We use an Arduino Nano board to send the control signals and to connect to our Blynk App. 
On the App, four things are displayed:

• Motor status 
• Moisture level 
• Atmospheric temperature and moisture
• Rain detector

The circuit keeps checking the moisture content of the soil by means of a moisture sensor, 
and updates the “Moisture level” on the app. The user can then check the current moisture 
level from a remote location and control the water supply. For this, the user only has to toggle 
the “Motor status” from ‘ON-OFF’ or ‘OFF-ON’; and the “water pump” will be ‘turned ON’ 
or ‘turned OFF’ accordingly. Thus the ‘soil-moisture’ gets monitored and the ‘water supply’ 
can be controlled just by the toggling the “Motor status”. So the user doesn’t have to worry 
about his crops or plants getting damaged due to ‘water-logging’ or ‘drought’.
This system can also be useful for people having small gardens, while it may not be possible 
for a person to be continuously present at his/her garden but one can use this project to keep a 
track of ‘soil-moisture’ and ensure proper water supply even from a distance.


**Functional Requirements**

The planned IoT irrigation system has the subsequent practical necessities of the hardware: 
• The detectors ought to gather sensor knowledge and pass it to the Arduino nano.
• The actuators ought to receive inputs from the Arduino Nano and translate those 
inputs into physical actions. as an example, activate the irrigation system. 
The planned golem application (BLYNK) ought to have the subsequent practical 
necessities : 
• User Authentication- The user ought to be ready to login into the golem application so 
as to access the various functionalities that square measure obtainable. 
• The user ought to be ready to read the standing of the farm 
• The user ought to be ready to flip the irrigation system on and off remotely.
