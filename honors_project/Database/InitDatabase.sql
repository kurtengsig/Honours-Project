BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS Users (
	username text PRIMARY KEY NOT NULL,
	password text NOT NULL,
	userID Integer NOT NULL,
	ipaddress text,
	port text,
	lastCheckIn text,
	status text NOT NULL);
insert into Users VALUES('Susan', '1508B697895ABF03D55C3841F59236AB92C9BA6BA89795C8337FCF392FDEE8B4', 1000, '0', '0','0', 'Offline');
insert into Users VALUES('Scott', 'E731911F912EC4CD2C9DF9700E078E9796B3547F53119FFE74324C3635A42DD8', 1001, '0', '0', '0', 'Offline');
insert into Users VALUES('James', 'DD68980994539901879A9DA77DFD992C099B708B05F44D6F33994EAB05B4D590', 1002, '0', '0', '0', 'Offline');
insert into Users VALUES('Kurt', '5E884898DA28047151D0E56F8DC6292773603D0D6AABBDD62A11EF721D1542D8', 1003, '0', '0', '0', 'Offline');

CREATE TABLE IF NOT EXISTS Friends (
	friendNumber Integer PRIMARY KEY NOT NULL,
	userID text NOT NULL,
	friendID text NOT NULL);
insert into Friends VALUES(1, '1000', '1003');
insert into Friends VALUES(2, '1003', '1000');
insert into Friends VALUES(3, '1003', '1001');
insert into Friends VALUES(4, '1003', '1002');
COMMIT;
