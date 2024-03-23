
CREATE OR ALTER  PROCEDURE CreateTable
AS
BEGIN
	CREATE TABLE Telefon_furnizori(
	id_numar INT PRIMARY KEY IDENTITY (1,1),
	id_furnizor INT NOT NULL,
	numar_de_telefon VARCHAR(31) NOT NULL,
	numar_alternativa INT NOT NULL,
	);
END
GO

EXECUTE CreateTable;
GO


CREATE OR ALTER PROCEDURE DeleteTable
AS
BEGIN
DROP TABLE dbo.Telefon_furnizori;
END
GO

DeleteTable;
GO


CREATE OR ALTER  PROCEDURE AdaugaCheieStraina
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    ADD CONSTRAINT cheie_straina
    FOREIGN KEY (id_furnizor) REFERENCES Furnizori(id_furnizor);
END
GO

AdaugaCheieStraina;
GO

CREATE OR ALTER  PROCEDURE StergeCheieStraina
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    DROP CONSTRAINT cheie_straina;
END
GO

StergeCheieStraina;
GO


CREATE OR ALTER  PROCEDURE AdaugaColoana
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    ADD data_introducere DATETIME;
END
GO

AdaugaColoana;
GO

CREATE OR ALTER  PROCEDURE StergeColoana
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    DROP COLUMN data_introducere;
END
GO

StergeColoana;
GO


CREATE OR ALTER PROCEDURE AdaugaConstrangereDefault
AS
BEGIN
	ALTER TABLE dbo.Telefon_furnizori
    ADD CONSTRAINT alternativa DEFAULT 1 FOR numar_alternativa;
END
GO

AdaugaConstrangereDefault;
GO


CREATE OR ALTER  PROCEDURE StergeConstrangereDefault
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    DROP CONSTRAINT alternativa;
END
GO

StergeConstrangereDefault;
GO

INSERT INTO dbo.Telefon_furnizori(id_furnizor, numar_de_telefon)
VALUES(1, '000');
GO


CREATE OR ALTER PROCEDURE ModificareColoana
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    ALTER COLUMN numar_de_telefon NVARCHAR(31);

END
GO

ModificareColoana;
GO


CREATE OR ALTER  PROCEDURE UndoModificareColoana
AS
BEGIN
    ALTER TABLE dbo.Telefon_furnizori
    ALTER COLUMN numar_de_telefon VARCHAR(31);
END
GO

UndoModificareColoana;
GO


Create Table Lista_Proceduri(
	nr_versiune INT PRIMARY KEY,
	nume_procedura varchar(100),
	nume_procedura_inversa varchar(100)
);

INSERT INTO Lista_Proceduri(nr_versiune, nume_procedura, nume_procedura_inversa)
VALUES
(0, '', ''),
(1, 'CreateTable', 'DeleteTable'),
(2, 'AdaugaCheieStraina', 'StergeCheieStraina'),
(3, 'AdaugaColoana', 'StergeColoana'),
(4, 'AdaugaConstrangereDefault', 'StergeConstrangereDefault'),
(5, 'ModificareColoana', 'UndoModificareColoana');
GO


CREATE TABLE VersiuneDB(
	nr_versiune INT,
);

INSERT INTO VersiuneDB(nr_versiune)
VALUES (0);
GO



CREATE OR ALTER  PROCEDURE SchimbaVersiunea @Versiune_noua INT
AS
BEGIN
	 IF @Versiune_noua > 5 OR @Versiune_noua < 0
	 BEGIN
		 RAISERROR('Nu exista decat 6 veriuni ale DB-ul (de la 0 la 5 inclusiv)', 16, 1);
		RETURN;
	 END

	 DECLARE @Versiune_actuala AS INT
	 SELECT @Versiune_actuala = nr_versiune
	 FROM VersiuneDB;

	 IF @Versiune_noua = @Versiune_actuala
	 BEGIN
		PRINT 'Suntem deja in versiunea data!';
		RETURN;
	 END

	 PRINT 'Versiunea actuala este : '; 
	 PRINT @Versiune_actuala;
	 PRINT 'Schimbam la versiunea : '; 
	 PRINT @Versiune_noua;

	 DECLARE @Procedura AS varchar(100);


	 IF @Versiune_noua > @Versiune_actuala
	 BEGIN
		WHILE @Versiune_noua != @Versiune_actuala
		BEGIN

			SET @Versiune_actuala = @Versiune_actuala + 1;

			SELECT @Procedura = nume_procedura
			FROM Lista_Proceduri
			WHERE @Versiune_actuala = nr_versiune;

			EXECUTE @Procedura;

		END

		UPDATE VersiuneDB
		SET nr_versiune = @Versiune_noua;

		RETURN;
	 END
	 
	 -- altfel daca  @Versiune < @Versiune_actuala

	 WHILE @Versiune_noua != @Versiune_actuala
		BEGIN

			SELECT @Procedura = nume_procedura_inversa
			FROM Lista_Proceduri
			WHERE @Versiune_actuala = nr_versiune;

			EXECUTE @Procedura;

			SET @Versiune_actuala = @Versiune_actuala - 1;

		END
	 
	 UPDATE VersiuneDB
	 SET nr_versiune = @Versiune_noua;
	 RETURN;
END
GO


EXEC SchimbaVersiunea -1;


SELECT nr_versiune FROM VersiuneDB;
