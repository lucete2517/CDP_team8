CREATE TABLE PERSON (
        Pid     CHAR(4) NOT NULL, 
        Pname   CHAR(16), 
        Btype   CHAR(2), 
        Rrn     CHAR(14), 
        Email   CHAR(32), 
        Phone   CHAR(13), 
        PRIMARY KEY(Pid)
);

CREATE TABLE EQUIP (
        Eid     CHAR(4) NOT NULL,
        Ename   CHAR(16), 
        PRIMARY KEY(Eid)
);

CREATE TABLE MODULE (
        Mid             CHAR(4) NOT NULL, 
        Personid        CHAR(4), 
        Equipid         CHAR(4), 
        Time            TIME, 
        Date            DATE, 
        Power           BOOL, 
        PRIMARY KEY(Mid), 
        FOREIGN KEY(Personid) REFERENCES PERSON(Pid), 
        FOREIGN KEY(Equipid) REFERENCES EQUIP(Eid)
);

CREATE TABLE SENSOR (
        Moduleid        CHAR(4), 
        Range_          INT, 
        Sound           INT, 
        FOREIGN KEY(Moduleid) REFERENCES MODULE(Mid)
);

CREATE VIEW STATE AS 
        SELECT Personid, Equipid, Time, Date 
        FROM MODULE 
        WHERE Power = TRUE;