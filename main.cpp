#include <iostream>
#include <cstdarg>
#include "cql.h"
#include <memory>
#include <iomanip>
#include <ctime>
using namespace std;

CREATE TABLE Boolean SCHEMA ( value CHAR (6) );

INSERT INTO Boolean ATTRIBUTES (value) VALUES ( "true" );
INSERT INTO Boolean ATTRIBUTES (value) VALUES ( "false" );

CREATE TABLE States SCHEMA (sid INTEGER, name CHAR (20));
INSERT INTO States ATTRIBUTES (sid, name) VALUES ( 1, "Michigan" );
INSERT INTO States ATTRIBUTES (sid, name) VALUES ( 2, "Texas" );
INSERT INTO States ATTRIBUTES (sid, name) VALUES ( 3, "California" );
INSERT INTO States ATTRIBUTES (sid, name) VALUES ( 4, "Florida" );

CREATE TABLE Teams SCHEMA ( tid INTEGER, name CHAR (50), sid INTEGER );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 33, "The Killer Bees",	1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 67, "The HOT Team",	1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 27, "RUSH",			1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 85, "B.O.B",			1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 148, "Robowranglers",	2 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 216, "RoboDawgs",		1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 217, "ThunderChickens",1 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 233, "The Pink Team",	4 );
INSERT INTO Teams ATTRIBUTES ( tid, name, sid ) VALUES ( 254, "Cheesy Poofs",	3 );


CREATE TABLE Abbrev SCHEMA ( code CHAR (10), value CHAR (70), nothing INTEGER );
INSERT INTO Abbrev ATTRIBUTES ( code, value ) VALUES ( "EECS", "Electical Engineering / Computer Science" );
INSERT INTO Abbrev ATTRIBUTES ( code, value ) VALUES ( "LING", "Linguistics" );
INSERT INTO Abbrev ATTRIBUTES ( code, value ) VALUES ( "MATH", "Mathematics" );
INSERT INTO Abbrev ATTRIBUTES ( code, value ) VALUES ( "AERO", "Aerospace Engineering" );

CREATE TABLE Profs SCHEMA ( pid INTEGER, name CHAR(50), department CHAR(20) );	

INSERT INTO Profs ATTRIBUTES ( pid, name, department ) VALUES ( 1, "Drew DeOrio", "EECS" );
INSERT INTO Profs ATTRIBUTES ( pid, name, department ) VALUES ( 4, "Satinder Baveja", "EECS" );
INSERT INTO Profs ATTRIBUTES ( pid, name, department ) VALUES ( 18, "Michael Lempert", "LING" );
INSERT INTO Profs ATTRIBUTES ( pid, name, department) VALUES  ( 14, "Valeria Bertacco", "EECS" );
INSERT INTO Profs ATTRIBUTES ( pid, name, department ) VALUES ( 21, "David Speyer", "MATH" );
INSERT INTO Profs ATTRIBUTES ( pid, name, department ) VALUES ( 24, "Ella Atkins", "AERO" );

   
CREATE TABLE Students SCHEMA ( sid INTEGER, name CHAR(45), gpa DOUBLE );

INSERT INTO Students ATTRIBUTES ( sid, gpa, name ) VALUES ( 1, 3.85, "Charlie" );
INSERT INTO Students ATTRIBUTES ( sid, gpa, name ) VALUES ( 3, 3.59, "NAND Dalal");
INSERT INTO Students ATTRIBUTES ( sid, gpa, name ) VALUES ( 8, 3.76, "Rohit Ramprasad" );
//INSERT INTO Students VALUES ( 9, "David Quesada" );
	


CREATE TABLE Classes SCHEMA ( cid INTEGER, code CHAR(10), number INTEGER, title CHAR(100));
INSERT INTO Classes ATTRIBUTES ( cid,code, number ) VALUES ( 1, "EECS", 281 );
INSERT INTO Classes ATTRIBUTES ( cid,code, number ) VALUES ( 2, "MATH", 417 );
INSERT INTO Classes ATTRIBUTES ( cid,code, number ) VALUES ( 3, "ECON", 101 );
INSERT INTO Classes ATTRIBUTES ( cid,code, number ) VALUES ( 4, "EECS", 370 );

CREATE TABLE Takes SCHEMA ( sid INTEGER, cid INTEGER );

void test1();

int main()
{

	cout << SELECT * FROM Students << endl;
	return 0;

}






