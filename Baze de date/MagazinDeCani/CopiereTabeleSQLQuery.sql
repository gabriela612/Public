
CREATE TABLE CMateriale (
	id_material INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) UNIQUE NOT NULL,
	rezistent_la_soc_puternic BIT NOT NULL DEFAULT 0,
	-- id_material, nume, rezistenta_la_soc_puternic
);

CREATE TABLE CFurnizori (
	id_furnizor INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) UNIQUE NOT NULL,
	nr_telefon VARCHAR(255) UNIQUE NOT NULL,
	email VARCHAR(255) UNIQUE NOT NULL,

	-- id_furnizor, nume, email, nr_telefon
);

CREATE TABLE CCani (
	-- id_cana, capactate(litri), model, [in_stoc], id_furnizor,
	-- greutate(grame), pret, [cantitate], 
	id_cana INT PRIMARY KEY IDENTITY (1,1),
	model VARCHAR(255),
	capacitate INT CHECK(capacitate >= 0),
	pret INT CHECK(pret >= 0) NOT NULL,
	id_furnizor INT FOREIGN KEY REFERENCES CFurnizori(id_furnizor) ON UPDATE CASCADE,
);

CREATE TABLE CMateriale_folosite (
	-- id_material_folosit, id_cana, id_material
	id_cana INT FOREIGN KEY REFERENCES CCani(id_cana) ON UPDATE CASCADE ON DELETE CASCADE,
	id_material INT FOREIGN KEY REFERENCES CMateriale(id_material) ON UPDATE CASCADE
		ON DELETE CASCADE,
	CONSTRAINT id_cmateriale_folosite PRIMARY KEY (id_cana, id_material)
);

INSERT INTO CFurnizori(nume, nr_telefon, email)
VALUES('CupaMug', '0711111111', 'contact@cupamug.com');

/*
INSERT INTO CMateriale(nume, rezistent_la_soc_puternic)
VALUES('plastic', 0);

INSERT INTO CCani(model, capacitate, pret, id_furnizor)
VALUES('Cana neagra simpla', 250, 20, 1);

INSERT INTO CMateriale_folosite(id_cana, id_material)
VALUES(1, 1);
*/


CREATE OR ALTER VIEW vCMateriale
AS
SELECT C.id_material, C.nume, C.rezistent_la_soc_puternic
FROM CMateriale AS C
GO

SELECT * FROM vCMateriale

CREATE OR ALTER VIEW vCMaterialeCCani
AS
SELECT c.id_cana, c.model, c.capacitate,
c.pret, c.id_furnizor, m.id_material, m.nume, m.rezistent_la_soc_puternic
FROM CMateriale AS m
INNER JOIN CMateriale_folosite AS mf
ON m.id_material = mf.id_material
INNER JOIN CCani AS c
ON mf.id_cana = c.id_cana
GO

SELECT * FROM vCMaterialeCCani

CREATE OR ALTER VIEW vCMaterialeCCaniGroup
AS
SELECT c.id_cana, c.model, COUNT(*) as [Nr materiale]
FROM CMateriale AS m
INNER JOIN CMateriale_folosite AS mf
ON m.id_material = mf.id_material
INNER JOIN CCani AS c
ON mf.id_cana = c.id_cana
GROUP BY c.id_cana, c.model
GO

SELECT * FROM vCMaterialeCCaniGroup

CREATE OR ALTER  PROCEDURE InsCMateriale @N INT
AS
BEGIN
	 IF @N < 0
	 BEGIN
		 RAISERROR('N trebuie sa fie mai mare decat 0', 16, 1);
		RETURN;
	 END

	 DECLARE @i AS INT
	 SET @i = 0


	WHILE @N > @i
	BEGIN

		SET @i = @i + 1;

		INSERT INTO CMateriale(nume, rezistent_la_soc_puternic)
		VALUES('plastic' + CAST(@i AS VARCHAR), 0);

	END

END
GO

EXEC dbo.InsCMateriale 10;

delete from CMateriale


CREATE OR ALTER  PROCEDURE InsCMaterialeRez @N INT
AS
BEGIN
	 IF @N < 0
	 BEGIN
		 RAISERROR('N trebuie sa fie mai mare decat 0', 16, 1);
		RETURN;
	 END

	 DECLARE @i AS INT
	 SET @i = 0


	WHILE @N > @i
	BEGIN

		SET @i = @i + 1;

		INSERT INTO CMateriale(nume, rezistent_la_soc_puternic)
		VALUES('metal' + CAST(@i AS VARCHAR), 1);

	END

END
GO

CREATE OR ALTER  PROCEDURE InsCCani @N INT
AS
BEGIN
	 IF @N < 0
	 BEGIN
		 RAISERROR('N trebuie sa fie mai mare decat 0', 16, 1);
		RETURN;
	 END

	 DECLARE @i AS INT
	 SET @i = 0


	WHILE @N > @i
	BEGIN

		SET @i = @i + 1;

		INSERT INTO CCani(model, capacitate, pret, id_furnizor)
		VALUES('Cana simpla' + CAST(@i as VARCHAR), 250, @i, 1);

	END

END
GO

EXEC dbo.InsCCani 10;

delete from CCani

CREATE OR ALTER  PROCEDURE InsCMateriale_folosite @N INT
AS
BEGIN
	 IF @N < 0
	 BEGIN
		 RAISERROR('N trebuie sa fie mai mare decat 0', 16, 1);
		RETURN;
	 END

	DECLARE @id_material INT, @id_cana INT;
	SELECT TOP 1 @id_cana = C.id_cana from CCani AS C;

	DECLARE cursor_materiale CURSOR FAST_FORWARD FOR
	SELECT C.id_material FROM CMateriale C;
	OPEN cursor_materiale;
	FETCH NEXT FROM cursor_materiale INTO @id_material;
	WHILE @@FETCH_STATUS=0 
	BEGIN
		INSERT INTO CMateriale_folosite(id_cana, id_material)
		VALUES(@id_cana, @id_material);
		FETCH NEXT FROM cursor_materiale INTO @id_material;
	END
	CLOSE cursor_materiale;
	DEALLOCATE cursor_materiale;

END
GO

CREATE OR ALTER  PROCEDURE InsCMateriale_folosite_rand
AS
BEGIN

	DECLARE @id_material INT, @id_cana INT;
	SELECT TOP 1 @id_cana = C.id_cana from CCani AS C ORDER BY NEWID();

	DECLARE cursor_materiale CURSOR FAST_FORWARD FOR
	SELECT C.id_material FROM CMateriale C;
	OPEN cursor_materiale;
	FETCH NEXT FROM cursor_materiale INTO @id_material;
	WHILE @@FETCH_STATUS=0 
	BEGIN
		INSERT INTO CMateriale_folosite(id_cana, id_material)
		VALUES(@id_cana, @id_material);
		FETCH NEXT FROM cursor_materiale INTO @id_material;
		SELECT TOP 1 @id_cana = C.id_cana from CCani AS C ORDER BY NEWID();
	END
	CLOSE cursor_materiale;
	DEALLOCATE cursor_materiale;

END
GO


EXEC InsCMateriale_folosite 10

delete from CMateriale_folosite

CREATE OR ALTER  PROCEDURE DelCMateriale_folosite
AS
BEGIN

	delete from CMateriale_folosite

END
GO

EXEC DelCMateriale_folosite

CREATE OR ALTER  PROCEDURE DelCMateriale
AS
BEGIN

	delete from CMateriale

END
GO

EXEC DelCMateriale

CREATE OR ALTER  PROCEDURE DelCCani
AS
BEGIN

	delete from CCani

END
GO

EXEC DelCCani


INSERT INTO Tables(Name) VALUES ('CMateriale'), ('CCani'), ('CMateriale_folosite');
INSERT INTO Tests(Name) VALUES ('InserareAll'), ('StergereAll');
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
(1, 1, 10000, 1),
(1, 2, 10000, 2),
(1, 3, 10000, 3),

(2, 1, 10000, 1),
(2, 2, 10000, 2),
(2, 3, 10000, 3);

INSERT INTO Tests(Name) VALUES ('TestAll'); -- id = 4
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
(4, 1, 10000, 1),
(4, 2, 10000, 2),
(4, 3, 10000, 3);


INSERT INTO Views (Name) VALUES
('vCMateriale'), ('vCMaterialeCCani'), ('vCMaterialeCCaniGroup');
 
INSERT INTO Tests(Name) VALUES ('SelectAll'); -- id = 5
INSERT INTO TestViews(TestID, ViewID) VALUES
(5, 1),
(5, 2),
(5, 3);


CREATE OR ALTER PROCEDURE InserareAll
AS
BEGIN

	DECLARE @Table VARCHAR(255), @NrRows INT
	DECLARE @i AS VARCHAR(255)
	DECLARE @t1 DATETIME, @t2 DATETIME
	DECLARE @tt1 DATETIME, @tt2 DATETIME
	DECLARE @id_test INT, @id_tabel INT

	DECLARE cursor_tabele CURSOR FAST_FORWARD FOR
	
	SELECT ta.Name, NoOfRows, ta.TableID
	FROM dbo.TestTables AS tt
	INNER JOIN dbo.Tables AS ta
	ON ta.TableID = tt.TableID
	WHERE TestID = 1
	ORDER BY Position

	SET @t1 = GETDATE()
	INSERT INTO TestRuns(StartAt) VALUES(@t1);
	SELECT @id_test = MAX(T.TestRunID) FROM TestRuns AS T

	OPEN cursor_tabele;
	FETCH NEXT FROM cursor_tabele INTO @Table, @NrRows, @id_tabel;
	WHILE @@FETCH_STATUS=0 
	BEGIN
		SET @i = CAST(@NrRows AS VARCHAR)

		SET @tt1 = GETDATE()

		EXEC('Ins' + @Table + ' ' + @i);

		SET @tt2 = GETDATE()

		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES
		(@id_test, @id_tabel, @tt1, @tt2);

		FETCH NEXT FROM cursor_tabele INTO @Table, @NrRows, @id_tabel;
	END
	CLOSE cursor_tabele;
	DEALLOCATE cursor_tabele;

	SET @t2 = GETDATE()

	UPDATE TestRuns
	SET Description = 'The tests: InserareAll', EndAt = @t2
	WHERE TestRunID = @id_test;

END
GO

EXEC InserareAll

CREATE OR ALTER PROCEDURE StergereAll
AS
BEGIN
	
	DECLARE @Table VARCHAR(255)
	DECLARE @t1 DATETIME, @t2 DATETIME
	DECLARE @tt1 DATETIME, @tt2 DATETIME
	DECLARE @id_test INT, @id_tabel INT

	DECLARE cursor_tabele CURSOR FAST_FORWARD FOR
	
	SELECT ta.Name, ta.TableID
	FROM dbo.TestTables AS tt
	INNER JOIN dbo.Tables AS ta
	ON ta.TableID = tt.TableID
	WHERE TestID = 2
	ORDER BY Position DESC

	SET @t1 = GETDATE()
	INSERT INTO TestRuns(StartAt) VALUES(@t1);
	SELECT @id_test = MAX(T.TestRunID) FROM TestRuns AS T

	OPEN cursor_tabele;
	FETCH NEXT FROM cursor_tabele INTO @Table, @id_tabel;
	WHILE @@FETCH_STATUS=0 
	BEGIN

		SET @tt1 = GETDATE()
		EXEC('Del' + @Table);
		SET @tt2 = GETDATE()

		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES
		(@id_test, @id_tabel, @tt1, @tt2);

		FETCH NEXT FROM cursor_tabele INTO @Table, @id_tabel;
	END
	CLOSE cursor_tabele;
	DEALLOCATE cursor_tabele;

	SET @t2 = GETDATE()

	UPDATE TestRuns
	SET Description = 'The tests: StergereAll', EndAt = @t2
	WHERE TestRunID = @id_test;


END
GO

EXEC StergereAll


CREATE OR ALTER PROCEDURE SelectAll
AS
BEGIN
	
	DECLARE @View VARCHAR(255)
	DECLARE @t1 DATETIME, @t2 DATETIME
	DECLARE @tt1 DATETIME, @tt2 DATETIME
	DECLARE @id_test INT, @id_view INT

	DECLARE cursor_viewuri CURSOR FAST_FORWARD FOR
	
	SELECT v.Name, v.ViewID
	FROM dbo.TestViews AS tv
	INNER JOIN dbo.Views AS v
	ON tv.ViewID = v.ViewID
	WHERE TestID = 5

	SET @t1 = GETDATE()
	INSERT INTO TestRuns(StartAt) VALUES(@t1);
	SELECT @id_test = MAX(T.TestRunID) FROM TestRuns AS T

	OPEN cursor_viewuri;
	FETCH NEXT FROM cursor_viewuri INTO @View, @id_view;
	WHILE @@FETCH_STATUS=0 
	BEGIN

		SET @tt1 = GETDATE()
		EXEC('SELECT * FROM ' + @View)
		SET @tt2 = GETDATE()

		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES
		(@id_test, @id_view, @tt1, @tt2);

		FETCH NEXT FROM cursor_viewuri INTO @View, @id_view;
	END
	CLOSE cursor_viewuri;
	DEALLOCATE cursor_viewuri;

	SET @t2 = GETDATE()

	UPDATE TestRuns
	SET Description = 'The tests: SelectAll', EndAt = @t2
	WHERE TestRunID = @id_test;


END
GO

EXEC SelectAll


CREATE OR ALTER PROCEDURE Main
AS
BEGIN
	DECLARE @t1 datetime, @t2 datetime
	DECLARE @desc NVARCHAR(2000)

	DECLARE @testInsert VARCHAR(255)
	DECLARE @testSelect VARCHAR(255)
	DECLARE @testDelete VARCHAR(255)

	SET @testInsert = 'InserareAll'
	SET @testSelect = 'SelectAll'
	SET @testDelete = 'StergereAll'

	SET @t1 = GETDATE()
	EXEC (@testInsert)
	EXEC (@testSelect)
	EXEC (@testDelete)
	SET @t2 = GETDATE()

	SET @desc=N'All tests: '+@testInsert+', '+@testSelect+', '+@testDelete
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (@desc,@t1,@t2)

END
GO

EXEC Main


SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
SELECT * FROM TestTables
SELECT * FROM TestViews
SELECT * FROM Tests
SELECT * FROM Tables
SELECT * FROM Views

