DROP TABLE Stoppage;
DROP TABLE Passenger;
DROP TABLE Ticket;
DROP TABLE Train;
DROP TABLE Station;
DROP TABLE Contact;
DROP TABLE ACCOUNT;
 
CREATE TABLE Account (
  Username varchar(15) NOT NULL,
  Password varchar(20) NOT NULL,
  Email_Id varchar(35) NOT NULL,
  Address varchar(50) DEFAULT NULL,
  PRIMARY KEY (Username)
);

INSERT intO Account VALUES ('mukim','eba094d4d15bc478cdc9','mukim14200@gmail.com','Chittagong');
INSERT intO Account VALUES ('karim','proxyman','karim@stud.kuet.ac.bd','Dhaka');
INSERT intO Account VALUES ('sadi','qwerty','sadi.jain.cse14@gmail.com','Madaripur');
INSERT intO Account VALUES ('joshim','goyal1002','joshim.goyal@gmail.com','Khulna');
INSERT intO Account VALUES ('salman','dejavu','salman@gmail.com','Rajshahi');
INSERT intO Account VALUES ('roni','ronaldoisgreat','roni@gmail.com','Dinajpur');
INSERT intO Account VALUES ('sabbir','eba094d4d15bc478cdc9','sabbir.jain.cse14@gmail.com','Rangpur');

CREATE TABLE Contact (
  Username varchar(15) NOT NULL  ,
  Phone_No varchar(11) NOT NULL  ,
  PRIMARY KEY (Username,Phone_No),
  CONSTRAINT Contact_ibfk_1 FOREIGN KEY (Username) REFERENCES Account (Username) ON DELETE CASCADE
);

INSERT intO Contact VALUES ('karim','01899887766');
INSERT intO Contact VALUES ('karim','01876543210');
INSERT intO Contact VALUES ('sadi','01771475390');
INSERT intO Contact VALUES ('sadi','01809224040');
INSERT intO Contact VALUES ('mukim','01411452250');
INSERT intO Contact VALUES ('mukim','01650367698');
INSERT intO Contact VALUES ('mukim','01968254144');
INSERT intO Contact VALUES ('joshim','01989786765');
INSERT intO Contact VALUES ('salman','01532453425');
INSERT intO Contact VALUES ('salman','01989786756');
INSERT intO Contact VALUES ('roni','01988342565');
INSERT intO Contact VALUES ('sabbir','01771475390');

SELECT * FROM Contact;


CREATE TABLE Station (
  Station_Code varchar(15) NOT NULL,
  Station_Name varchar(25) NOT NULL,
  PRIMARY KEY (Station_Code)
);

INSERT intO Station VALUES ('Dhaka','Kamalapur Station');
INSERT intO Station VALUES ('Rajshahi','Rajshahi Station');
INSERT intO Station VALUES ('Khulna','Khulna Station');
INSERT intO Station VALUES ('Sylhet','Sylhet Station');
INSERT intO Station VALUES ('Dinajpur','Dinajpur Station');
INSERT intO Station VALUES ('Chittagong','Chittagong Station');

CREATE TABLE Train (
  Train_No number(6) NOT NULL ,
  Name varchar(25) NOT NULL,
  Seat_Sleeper number(4) NOT NULL,
  Seat_First_Class_AC number(4) NOT NULL,
  Seat_Second_Class_AC number(4) NOT NULL,
  Seat_Third_Class_AC number(4) NOT NULL,
  Wifi varchar(1) NOT NULL,
  Food varchar(1) NOT NULL,
  Run_On_Sunday varchar(1) NOT NULL,
  Run_On_Monday varchar(1) NOT NULL,
  Run_On_Tuesday varchar(1) NOT NULL,
  Run_On_Wednesday varchar(1) NOT NULL,
  Run_On_Thursday varchar(1) NOT NULL,
  Run_On_Friday varchar(1) NOT NULL,
  Run_On_Saturday varchar(1) NOT NULL,
  PRIMARY KEY (Train_No)
);

INSERT intO Train VALUES (12559,'Subarna Exp ',479,47,96,192,'N','Y','Y','Y','Y','Y','Y','Y','Y');
INSERT intO Train VALUES (12560,'Subarna Exp ',480,43,96,192,'N','Y','Y','Y','Y','Y','Y','Y','Y');
INSERT intO Train VALUES (12581,'Sundarban Exp',432,48,80,144,'N','N','Y','Y','Y','Y','Y','Y','Y');
INSERT intO Train VALUES (12582,'Sundarban Exp',432,48,80,144,'N','N','Y','Y','Y','Y','Y','Y','Y');

CREATE TABLE Ticket (
  Ticket_No number(10) NOT NULL ,
  Train_No number(6) NOT NULL,
  Date_of_Journey date NOT NULL,
  Username varchar(15) NOT NULL,
  PRIMARY KEY (Ticket_No),
  CONSTRAINT Ticket_ibfk_1 FOREIGN KEY (Username) REFERENCES Account (Username) ON DELETE CASCADE,
  CONSTRAINT Ticket_ibfk_2 FOREIGN KEY (Train_No) REFERENCES Train (Train_No) ON DELETE CASCADE
);

INSERT INTO ticket VALUES (1,12559, to_date('1990-12-12', 'yyyy-mm-dd'),'mukim');
INSERT INTO ticket VALUES (2,12560, to_date('1991-12-12', 'yyyy-mm-dd'),'karim');
INSERT INTO ticket VALUES (3,12560, to_date('1992-12-12', 'yyyy-mm-dd'),'sadi');
INSERT INTO ticket VALUES (4,12581, to_date('1993-12-12', 'yyyy-mm-dd'),'joshim');
INSERT INTO ticket VALUES (5,12581, to_date('1994-12-12', 'yyyy-mm-dd'),'roni');
INSERT INTO ticket VALUES (6,12582, to_date('1995-12-12', 'yyyy-mm-dd'),'sabbir');

SELECT * FROM ticket;

CREATE TABLE Passenger (
  Passenger_Id number(11) NOT NULL ,
  First_Name varchar(20) NOT NULL,
  Last_Name varchar(20) NOT NULL,
  Gender varchar(1) NOT NULL,
  Phone_No varchar(10) DEFAULT NULL,
  Ticket_No number(6) NOT NULL,
  Age number(11) NOT NULL,
  Class varchar(20) NOT NULL,
  PRIMARY KEY (Passenger_Id),
  CONSTRAINT Passenger_ibfk_1 FOREIGN KEY (Ticket_No) REFERENCES Ticket (Ticket_No) ON DELETE CASCADE
);

CREATE TABLE Stoppage (
  Train_No number(6) NOT NULL,
  Station_Code varchar(15) NOT NULL,
  Arrival_Time INTERVAL DAY TO SECOND NULL,
  Departure_Time INTERVAL DAY TO SECOND NULL,
  PRIMARY KEY (Train_No,Station_Code),
  CONSTRAINT Stoppage_ibfk_1 FOREIGN KEY (Train_No) REFERENCES Train (Train_No) ON DELETE CASCADE ,
  CONSTRAINT Stoppage_ibfk_2 FOREIGN KEY (Station_Code) REFERENCES Station (Station_Code) ON DELETE CASCADE 
);


INSERT intO Stoppage VALUES (12559,'Dhaka','0 22:05:00','0 22:30:00');
INSERT intO Stoppage VALUES (12559,'Rajshahi','0 01:30:00','0 01:38:00');
INSERT intO Stoppage VALUES (12559,'Dinajpur','0 19:20:00','0 19:30:00');
INSERT intO Stoppage VALUES (12559,'Chittagong','0 08:10:00',NULL);
INSERT intO Stoppage VALUES (12560,'Dhaka','0 03:45:00','0 04:10:00');
INSERT intO Stoppage VALUES (12560,'Rajshahi','0 01:00:00','0 01:05:00');
INSERT intO Stoppage VALUES (12560,'Dinajpur','0 07:00:00',NULL);
INSERT intO Stoppage VALUES (12560,'Chittagong','0 18:35:00','0 18:55:00');
INSERT intO Stoppage VALUES (12581,'Dhaka','0 01:20:00','0 01:45:00');
INSERT intO Stoppage VALUES (12581,'Rajshahi','0 04:15:00','0 04:20:00');
INSERT intO Stoppage VALUES (12581,'Khulna','0 23:31:00','0 23:33:00');
INSERT intO Stoppage VALUES (12581,'Sylhet','0 11:30:00','0 11:32:00');
INSERT intO Stoppage VALUES (12581,'Dinajpur','0 22:20:00','0 22:30:00');
INSERT intO Stoppage VALUES (12581,'Chittagong','0 12:20:00',NULL);
INSERT intO Stoppage VALUES (12582,'Dhaka','0 07:45:00','0 08:15:00');
INSERT intO Stoppage VALUES (12582,'Rajshahi','0 04:55:00','0 05:00:00');
INSERT intO Stoppage VALUES (12582,'Khulna','0 09:21:00','0 09:23:00');
INSERT intO Stoppage VALUES (12582,'Sylhet','0 23:03:00','0 23:05:00');
INSERT intO Stoppage VALUES (12582,'Dinajpur','0 11:20:00',NULL);
INSERT intO Stoppage VALUES (12582,'Chittagong','0 22:15:00','0 22:25:00');

SELECT * FROM Stoppage;

INSERT intO Account VALUES ('admin','admin@1234','mukim14200@gmail.com','Old airport road,Dinajpur Station');


