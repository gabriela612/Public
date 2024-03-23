
ALTER TABLE CCani
ADD CONSTRAINT CK_pret CHECK (
   pret > 0
   )

ALTER TABLE CCani
ADD CONSTRAINT CK_capacitate CHECK (
   capacitate > 0 AND capacitate <= 1500
   )

delete from CCani
insert into Ccani(model, capacitate, pret, id_furnizor) values ('m', 0, 1, 5);
insert into Ccani(model, capacitate, pret, id_furnizor) values ('m', 10, -1, 5);
insert into Ccani(model, capacitate, pret, id_furnizor) values ('m', 10, 1, 5);

select * from CCani

CREATE OR ALTER Function Is_Valid_IdFurnizor(@id_f INT)
   RETURNS BIT
AS
BEGIN
	IF @id_f IS NULL
	BEGIN
		RETURN 0
	END

	IF EXISTS (SELECT * FROM CFurnizori WHERE id_furnizor = @id_f)
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


CREATE OR ALTER Function Is_Valid_IdCana(@id_c INT)
   RETURNS BIT
AS
BEGIN
	IF @id_c IS NULL
	BEGIN
		RETURN 0
	END

	IF EXISTS (SELECT * FROM CCani WHERE id_cana = @id_c)
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


CREATE OR ALTER Function Is_Valid_IdMaterial(@id_m INT)
   RETURNS BIT
AS
BEGIN
	IF @id_m IS NULL
	BEGIN
		RETURN 0
	END

	IF EXISTS (SELECT * FROM CMateriale WHERE id_material = @id_m)
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO

CREATE OR ALTER Function Is_Valid_IdMaterialFolosit(@id_c INT, @id_m INT)
   RETURNS BIT
AS
BEGIN
	IF @id_c IS NULL OR @id_m IS NULL
	BEGIN
		RETURN 0
	END

	IF EXISTS (SELECT * FROM CMateriale_folosite WHERE id_material = @id_m AND id_cana = @id_c)
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO

CREATE OR ALTER Function STRING_NOT_NULL(@string nvarchar(100))
   RETURNS BIT
AS
BEGIN
	IF @string IS NOT NULL
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


CREATE OR ALTER Function INT_NOT_NULL(@int INT)
   RETURNS BIT
AS
BEGIN
	IF @int IS NOT NULL
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


CREATE OR ALTER Function BIT_NOT_NULL(@bit BIT)
   RETURNS BIT
AS
BEGIN
	IF @bit IS NOT NULL
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


CREATE OR ALTER FUNCTION Validate_String(@nume VARCHAR(250))
RETURNS BIT
AS
    BEGIN
        if @nume is null
            return 0
        if LTRIM(@nume) = ''
            return 0
        if LEN(@nume) < 3
            return 0

        DECLARE @len INT
        SET @len = LEN(@nume)

        DECLARE @index INT
        SET @index = 1

        WHILE @index <= @len
        BEGIN
            IF NOT SUBSTRING(@nume, @index, 1) LIKE '%[!%--//!+!|0-9a-zA-z  ]'
                return 0
            SET @index = @index + 1
        END
        return 1
    END
GO

IF dbo.Validate_String('aa aa') = 1
BEGIN
	PRINT 'aaaa'
END


CREATE OR ALTER FUNCTION Validate_Unsigned_Int
(
    @number INT
)
RETURNS BIT
AS
    BEGIN
        if @number is null
            return 0
		IF @number <= 0
		BEGIN
			RETURN 0
		END
        return 1
    END
GO

IF dbo.Validate_Unsigned_Int(-1) = 1
BEGIN
	PRINT '555'
END


CREATE OR ALTER PROCEDURE CreateCCani
    @model NVARCHAR(250),
	@capacitate INT,
	@pret INT,
	@id_furnizor INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Validate_String(@model) = 1 AND
		dbo.Validate_Unsigned_Int(@capacitate) = 1 AND
		dbo.Validate_Unsigned_Int(@pret) = 1 AND
		dbo.Is_Valid_IdFurnizor(@id_furnizor) = 1 AND
		NOT EXISTS (SELECT * FROM CCani WHERE model = @model AND
			capacitate = @capacitate AND pret = @pret AND id_furnizor = @id_furnizor))
    BEGIN
        INSERT INTO CCani(model, capacitate, pret, id_furnizor)
			VALUES (@model, @capacitate, @pret, @id_furnizor)
		PRINT 'Inserarea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC CreateCCani 'neagra', 10, 1, 1
SELECT * FROM CCani

CREATE OR ALTER PROCEDURE CreateCMaterialeFolosite
	@id_cana INT,
	@id_material INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdMaterial(@id_material) = 1 AND
		dbo.Is_Valid_IdCana(@id_cana) = 1 AND
		NOT EXISTS (SELECT * FROM CMateriale_folosite 
			WHERE id_cana = @id_cana AND id_material = id_material))
    BEGIN
        INSERT INTO CMateriale_folosite(id_cana, id_material)
			VALUES (@id_cana, @id_material)
		PRINT 'Inserarea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC CreateCMaterialeFolosite 748087, 350813
SELECT * FROM CMateriale_folosite

CREATE OR ALTER PROCEDURE CreateCMateriale
    @nume NVARCHAR(250),
	@rez BIT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Validate_String(@nume) = 1 AND
		dbo.BIT_NOT_NULL(@rez) = 1 AND
		NOT EXISTS (SELECT * FROM CMateriale WHERE nume = @nume
			AND rezistent_la_soc_puternic = @rez))
    BEGIN
        INSERT INTO CMateriale(nume, rezistent_la_soc_puternic)
			VALUES (@nume, @rez)
		PRINT 'Inserarea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC dbo.CreateCMateriale material1, 1
SELECT * FROM CMateriale


CREATE OR ALTER PROCEDURE ReadOneCCani
	@id_cana INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdCana(@id_cana) = 1)
    BEGIN
        SELECT * FROM CCani WHERE id_cana = @id_cana
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC ReadOneCCani 748087


CREATE OR ALTER PROCEDURE ReadOneCMaterialeFolosite
	@id_c INT, @id_m INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdMaterialFolosit(@id_c, @id_m) = 1)
    BEGIN
        SELECT * FROM CMateriale_folosite WHERE id_cana = @id_c AND id_material = @id_m
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC ReadOneCMaterialeFolosite 748087, 350813


CREATE OR ALTER PROCEDURE ReadOneCMateriale
	@id_m INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdMaterial(@id_m) = 1)
    BEGIN
        SELECT * FROM CMateriale WHERE id_material = @id_m
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC ReadOneCMateriale 350813


CREATE OR ALTER PROCEDURE ReadAllCCani
AS
BEGIN
    SELECT * FROM CCani
END
GO

EXEC ReadAllCCani


CREATE OR ALTER PROCEDURE ReadAllCMaterialeFolosite
AS
BEGIN
    SELECT * FROM CMateriale_folosite
END
GO

EXEC ReadAllCMaterialeFolosite


CREATE OR ALTER PROCEDURE ReadAllCMateriale
AS
BEGIN
    SELECT * FROM CMateriale
END
GO

EXEC ReadAllCMateriale


CREATE OR ALTER PROCEDURE UpdateCCani
    @model NVARCHAR(250),
	@capacitate INT,
	@pret INT,
	@id_furnizor INT,
	@id_cana INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Validate_String(@model) = 1 AND
		dbo.Validate_Unsigned_Int(@capacitate) = 1 AND
		dbo.Validate_Unsigned_Int(@pret) = 1 AND
		dbo.Is_Valid_IdFurnizor(@id_furnizor) = 1 AND
		dbo.Is_Valid_IdCana(@id_cana) = 1)
    BEGIN
		UPDATE CCani
			SET model = @model, capacitate = @capacitate, pret = @pret, id_furnizor = @id_furnizor
			WHERE id_cana = @id_cana;
		PRINT 'Actualizarea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC dbo.UpdateCCani 'rosie', 1, 1, 1, 748087
select * from CCani


CREATE OR ALTER PROCEDURE UpdateCMateriale
    @nume NVARCHAR(250),
	@rez BIT,
	@id_material INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Validate_String(@nume) = 1 AND
		dbo.BIT_NOT_NULL(@rez) = 1 AND
		dbo.Is_Valid_IdMaterial(@id_material) = 1)
    BEGIN
		UPDATE CMateriale
			SET nume = @nume, rezistent_la_soc_puternic = @rez
			WHERE id_material = @id_material
		PRINT 'Actualizarea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

select * from CMateriale
EXEC UpdateCMateriale 'sticla', 1, 350813



CREATE OR ALTER PROCEDURE DeleteCCani
	@id_cana INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdCana(@id_cana) = 1)
    BEGIN
        DELETE FROM CCani WHERE id_cana = @id_cana
		PRINT 'Stergerea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC DeleteCCani 748087
select * from CCani


CREATE OR ALTER PROCEDURE DeleteCMaterialeFolosite
	@id_c INT, @id_m INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdMaterialFolosit(@id_c, @id_m) = 1)
    BEGIN
        DELETE FROM CMateriale_folosite WHERE id_cana = @id_c AND id_material = @id_m
		PRINT 'Stergerea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC DeleteCMaterialeFolosite 748087, 350813
select * from CMateriale_folosite


CREATE OR ALTER PROCEDURE DeleteCMateriale
	@id_m INT
AS
BEGIN
    SET NOCOUNT ON;
    IF (dbo.Is_Valid_IdMaterial(@id_m) = 1)
    BEGIN
        DELETE FROM CMateriale WHERE id_material = @id_m
		PRINT 'Stergerea a avut loc cu succes'
	END
	ELSE
	BEGIN
		RAISERROR('Datele de intrare nu sunt valide.', 16, 1);
	END
END
GO

EXEC DeleteCMateriale 350813
select * from CMateriale


