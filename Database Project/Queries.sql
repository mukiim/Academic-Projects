/* Queries From Here */

/* Find The Trains that have stoppage both at Dinajpur and Chittagong */
select a.Train_No from Stoppage a join Stoppage b on a.Train_No = b.Train_No 
where (a.Station_Code = 'Dinajpur' and b.Station_Code = 'Chittagong');

/* Find The Trains that have stoppage both at Dinajpur and Chittagong sorting in DESC*/
select a.Train_No from Stoppage a join Stoppage b on a.Train_No = b.Train_No 
where (a.Station_Code = 'Dinajpur' and b.Station_Code = 'Chittagong') ORDER by a.Train_No desc;

/* Find The Trains that have stoppage both at Dhaka and Khulna */
select a.Train_No from Stoppage a join Stoppage b on a.Train_No = b.Train_No 
where (a.Station_Code = 'Dhaka' and b.Station_Code = 'Khulna');


/* Find The maximum Arrival TIME of the Trains that have stoppage both at Dinajpur and Chittagong */
select max((EXTRACT(HOUR FROM a.Arrival_Time))) from Stoppage a join Stoppage b on a.Train_No = b.Train_No 
where (a.Station_Code = 'Dinajpur' and b.Station_Code = 'Chittagong');


/* Find The minimum Arrival TIME of the Trains that have stoppage both at Dhaka and Khulna */
select min((EXTRACT(HOUR FROM a.Arrival_Time))) from Stoppage a join Stoppage b on a.Train_No = b.Train_No 
where (a.Station_Code = 'Dhaka' and b.Station_Code = 'Khulna');



/* Find The Trains that have stoppage AFTER 10:00 and before 20:00 */
SELECT DISTINCT  Train_No from Stoppage where (EXTRACT(HOUR FROM Arrival_Time))<20 and (EXTRACT(HOUR FROM Arrival_Time))>10;

/* Find The COUNT of Trains that have stoppage AFTER 7:00 and before 20:00 */
SELECT COUNT(DISTINCT Train_No) from Stoppage where (EXTRACT(HOUR FROM Arrival_Time))<20 and (EXTRACT(HOUR FROM Arrival_Time))>7;

/* GROUPING by Train_No */
SELECT train_no from Stoppage GROUP by train_no;

/* Find total number of first class seats available on any train that reaches Dinajpur Station before 7pm on Monday .*/

drop view a;

create view a(Station_code,Train_no,Arrival_Time)as
SELECT Stoppage.Station_code,Train_no,Arrival_Time
from Station inner join Stoppage on station.Station_code=Stoppage.Station_code where station.Station_name='Dinajpur Station';

SELECT * FROM a;

drop view b;

create view b(Station_code,Train_no,Arrival_Time)as
SELECT Station_code,Train_no,Arrival_Time
from a where (EXTRACT(HOUR FROM Arrival_Time))<19;

SELECT * FROM b;

drop view c;

create view c(Station_code,Train_no,Arrival_Time,First_Class_seats,Run_on_monday)as
SELECT Station_code,train.Train_no,Arrival_Time,Seat_First_Class_AC,Run_on_monday
from train inner join b on train.Train_No=b.Train_No where train.Run_On_Monday='Y' AND train.Seat_First_Class_AC >0;

SELECT * FROM c;

SELECT SUM(First_class_seats)
FROM c;


/* Find the time at which last train  leaves Chittagong Station  */
drop view f;

create view f(Departure_time)as
 SELECT Departure_time 
   FROM Stoppage 
   WHERE Station_Code IN (SELECT Station_code 
         FROM station 
         WHERE Station_Name='Chittagong Station') ;
SELECT * FROM f;
select MAX(Departure_time) from f;

/* Find the phone number of the user whose email id is mukim14200@gmail.com */
Select Phone_no from Contact where username IN (Select Username from account where Email_id='mukim14200@gmail.com');

