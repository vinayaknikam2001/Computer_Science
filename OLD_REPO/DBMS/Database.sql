/* PWD=fast*/
/* Creating and deleting a database*/
create database test;
drop database test;


/*Connecting to a database*/
postgres=# \c test


/*Listing all databases*/
postgres=# \l

List of databases
   Name    |  Owner   | Encoding | Locale Provider |      Collate       |       Ctype        | ICU Locale | ICU Rules |   Access privileges
-----------+----------+----------+-----------------+--------------------+--------------------+------------+-----------+-----------------------
 postgres  | postgres | UTF8     | libc            | English_India.1252 | English_India.1252 |            |           |
 template0 | postgres | UTF8     | libc            | English_India.1252 | English_India.1252 |            |           | =c/postgres          +
           |          |          |                 |
          |                    |            |           | postgres=CTc/postgres
 template1 | postgres | UTF8     | libc            | English_India.1252 | English_India.1252 |            |           | =c/postgres          +
           |          |          |                 |
          |                    |            |           | postgres=CTc/postgres
 test      | postgres | UTF8     | libc            | English_India.1252 | English_India.1252 |            |           |
(4 rows)


/*Creating a new db table*/
You are now connected to database "test" as user "postgres".
test=# CREATE TABLE person (
test(# id int,
test(# first_name varchar(50),
test(# last_name varchar(50),
test(# gender varchar(7),
test(# date_of_birth date);
CREATE TABLE

/*To check list of tables \d stands for describe. */
test=# \d
         List of relations
 Schema |  Name  | Type  |  Owner
--------+--------+-------+----------
 public | person | table | postgres
(1 row)

/*Displays description of all tables in current database. */
\dt


/*To describe a table. */
test=# \d person
                         Table "public.person"
    Column     |         Type          | Collation | Nullable | Default
---------------+-----------------------+-----------+----------+---------
 id            | integer               |           |
|
 first_name    | character varying(50) |           |
|
 last_name     | character varying(50) |           |
|
 gender        | character varying(7)  |           |
|
 date_of_birth | date                  |           |
|



