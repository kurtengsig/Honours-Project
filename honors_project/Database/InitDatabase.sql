BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS Users (username text PRIMARY KEY, password text, userID Integer, ipaddress text, port text, lastCheckIn text, status text);
insert into Users VALUES('Susan', 'lee', 1000, '0', '0','0', 'Offline');
insert into Users VALUES('Scott', 'grobowski', 1001, '0', '0', '0', 'Offline');
insert into Users VALUES('James', 'pippy', 1002, '0', '0', '0', 'Offline');
insert into Users VALUES('Kurt', 'password', 1003, '0', '0', '0', 'Offline');

CREATE TABLE IF NOT EXISTS Friends (friendNumber Integer PRIMARY KEY, userID text, friendID text);
insert into Friends VALUES(1, '1000', '1003');
insert into Friends VALUES(2, '1003', '1000');
insert into Friends VALUES(3, '1003', '1001');
insert into Friends VALUES(4, '1003', '1002');
COMMIT;
