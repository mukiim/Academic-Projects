/* Procedure for a finding a train name */
SET SERVEROUTPUT ON;

create or replace PROCEDURE tmp IS
	trainno train.train_no%type;
	lname train.name%type;
BEGIN
	trainno := 12581;
	SELECT name into lname
	FROM train where train_no=trainno;
	DBMS_OUTPUT.PUT_LINE('Name of Train: ' || lname);
END;
/
show errors;

BEGIN
	tmp;
END;
/

/* Function for maximum arrival time */
create or replace FUNCTION maxx_time return INTERVAL DAY TO SECOND IS
	timee Stoppage.arrival_time%type;
BEGIN
	SELECT max(arrival_time) into timee
	FROM Stoppage;
	return timee;
END;
/
show errors;
SET SERVEROUTPUT ON;
BEGIN
	DBMS_OUTPUT.PUT_LINE('Maximum Arrival Time ' || maxx_time);
END;
/


/* Trigger when canceling a ticktet */

create or REPLACE trigger cancellation 
 before delete on ticket
 for each row  
 DECLARE
 pragma autonomous_transaction;
  trainno CONSTANT NUMBER(6) := :old.train_no; 
  ticketno CONSTANT NUMBER(10) := :old.ticket_no;  
  Clas VARCHAR(20);
BEGIN
	SELECT p.Class into Clas FROM PASSENGER p WHERE p.ticket_no = ticketno;
	if clas='first class ac' then    
		UPDATE Train set Seat_First_Class_AC = Seat_First_Class_AC+1 WHERE Train_No = trainno ;   
    elsif clas='sleeper' then        
		UPDATE Train set Seat_Sleeper = Seat_Sleeper+1 WHERE Train_No = trainno ;   
    elsif clas='second class ac' then       
		UPDATE Train set Seat_Second_Class_AC = Seat_Second_Class_AC+1 WHERE Train_No = trainno ;    
    elsif clas='third class ac' then        
		UPDATE Train set Seat_Third_Class_AC = Seat_Third_Class_AC+1 WHERE Train_No = trainno ;      
  end if; 
END;
/

show errors

INSERT INTO Passenger values ('1','admin','kos','F','233',1,20,'first Class ac');
INSERT INTO Passenger values ('2','admin','kos','F','233',2,20,'first Class ac');

SELECT * from ticket;
SELECT * from PASSENGER;

delete from ticket where ticket_no=1;

SELECT * from ticket;
SELECT * from PASSENGER;