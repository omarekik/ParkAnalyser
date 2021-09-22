# ParkAnalyser
This module analyses car logs of park data. 

We follow the movement of several remote-controlled cars on the plane (X, Y). Using C ++ and the attached text file  
(in ParkAnalyzer/testes/config/) presenting the information in the following format:  
IDa | X1 * Y1 * T1 / X2 * Y2 * T2 / X3 * Y3 * T3; IDb | X1 * Y1 * T1 / X2 * Y2 * T2 (for example: Ida = 111, X1 = 2.5; Y1 = 3.5; T1 = 25)
* Return the ID of the car (s) which has an average speed of more than 5 m / s
* Taking into account errors (data and / or loops or functions that can cause errors)
* Reprocess the data to avoid taking into account points with aberrant speeds (e.g.> 10m / s). Return the ID of the car (s) which has an average "retired" speed of more than 5 m / s
