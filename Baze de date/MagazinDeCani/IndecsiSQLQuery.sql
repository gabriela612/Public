
-- filtrare dupa pret
CREATE OR ALTER VIEW View_CCana_Pret
AS
 SELECT C.model, C.pret, C.capacitate
 FROM CCani as C
 WHERE pret > 55;
GO

SELECT * FROM View_CCana_Pret
DELETE FROM CCani

EXEC dbo.InsCCani 100 -- pret = 1-100
EXEC dbo.InsCCani 10
EXEC dbo.InsCCani 100
EXEC dbo.InsCCani 100
EXEC dbo.InsCCani 100
EXEC dbo.InsCCani 100

CREATE NONCLUSTERED INDEX N_Idx_Pret ON CCani (pret) INCLUDE(model, capacitate, id_cana, id_furnizor);

DROP INDEX N_idx_Pret ON CCani;

EXEC sys.sp_helpindex @objname = 'CCani';

--SELECT TOP 50 * FROM sys.dm_db_index_usage_stats;


-- canile nerezistente la soc puternic / fragile
CREATE OR ALTER VIEW View_CCani_Nerezistente
AS
 SELECT DISTINCT C.model
 FROM CMateriale AS M
 INNER JOIN CMateriale_folosite AS MF
 ON M.id_material = MF.id_material
 INNER JOIN CCani AS C
 ON C.id_cana = MF.id_cana
 WHERE M.rezistent_la_soc_puternic = 0;
GO

SELECT * FROM dbo.View_CCani_Nerezistente

DELETE FROM CMateriale_folosite
DELETE FROM CCani
DELETE FROM CMateriale

EXEC dbo.InsCCani 100
EXEC dbo.InsCMateriale 25
EXEC dbo.InsCMaterialeRez 75
EXEC dbo.InsCMateriale_folosite_rand


CREATE NONCLUSTERED INDEX N_Idx_Rez ON CMateriale (rezistent_la_soc_puternic) INCLUDE(nume);

DROP INDEX N_idx_Rez ON CMateriale;

EXEC sys.sp_helpindex @objname = 'CMateriale';


CREATE NONCLUSTERED INDEX N_Idx_IDM ON CMateriale_folosite (id_material) INCLUDE(id_cana);

DROP INDEX N_Idx_IDM ON CMateriale_folosite;

EXEC sys.sp_helpindex @objname = 'CMateriale_folosite';


CREATE NONCLUSTERED INDEX N_Idx_Model ON CCani (model) INCLUDE(pret, capacitate, id_cana, id_furnizor);

DROP INDEX N_idx_Model ON CCani;

EXEC sys.sp_helpindex @objname = 'CCani';