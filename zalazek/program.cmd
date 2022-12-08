#define NIGHTY 90
#define FOURTYFIVE 45


 

Begin_Parallel_Actions
Rotate Podstawa 5 Z NIGHTY  
End_Parallel_Actions

Begin_Parallel_Actions 
Rotate Podstawa.Ramie1.Ramie2 1 Y FOURTYFIVE
Rotate Podstawa.Ramie1 1 Y FOURTYFIVE
End_Parallel_Actions

Begin_Parallel_Actions 
Rotate Podstawa 4 Z 180  
End_Parallel_Actions

Begin_Parallel_Actions 
Rotate Podstawa.Ramie1.Ramie2 1 Y FOURTYFIVE
Rotate Podstawa.Ramie1 1 Y FOURTYFIVE
End_Parallel_Actions






Begin_Parallel_Actions
Move Car 0.2  25
Rotate Car.PP 5 Y 700 
Rotate Car.LP 5 Y 700 
Rotate Car.PT 5 Y 700
Rotate Car.LT 5 Y 700 
End_Parallel_Actions  