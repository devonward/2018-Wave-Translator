# 2018-Wave-Translator

Wave Translator (working title)

2018-06-29

created during the Digital Naturalism Conference in Koh Lon, Thailand

by Devon Ward

https://devon-ward.com

This is a prototype for a wearable garment the translates wave movements into a 
dislocated, felt experience. This is a system that wirelessly sends acceleration 
data from a weather buoy to a wearable array of 6 vibrotactile motors. This setup 
uses two Arduinos, connected to Xbees for wireless data transfer. 
                
The first Arduino is connected to a 3-axis accelerometer (LIS331), an Xbee and powered 
by solar (a Medium 2W 6V solar panel connected to a DC solar lithium charger, and 
a 3.7v 2500mAh Li-Po Battery). These items were housed inside a weather box
that served as a makeshift buoy, which was anchored roughly 15 metres offshore.
                
The second Arduino was connected to an Xbee, an array of transistors and 6 vibrating
mini motor discs that were glued to stretchable nylon straps that could be placed on
different parts of the body. 
               
/ notes /  

This project was created over the course of a week as part of the 2018 Digital 
Naturalism Conference. It is a functional prototype.

/ information for setup / 

Accelerometer hookup guide: 
https://learn.sparkfun.com/tutorials/h3lis331dl-accelerometer-breakout-hookup-guide/all

Xbee setup (videos):
Xbee Basics - Lessons 1-5 by 'tunnelsup': 
https://www.youtube.com/watch?v=odekkumB3WQ

/ libraries required / 

Library for Accelerometer: https://github.com/sparkfun/SparkFun_LIS331_Arduino_Library
                
/ usage /   

Use how you like.
                

                
                
