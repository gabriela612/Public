
-- Cate comenzi a preluat fiecare angajat in luna curenta
SELECT nume AS [Nume Angajat], COUNT(*) AS [Numar de preluari]
FROM Angajati AS a
INNER JOIN Prelucrari_comenzi AS p
ON a.id_angajat = p.id_angajat
WHERE MONTH(p.data_preluarii_comenzii) = MONTH(CURRENT_TIMESTAMP) AND
YEAR(p.data_preluarii_comenzii) = YEAR(CURRENT_TIMESTAMP)
GROUP BY nume

-- Cate cani a prelucrat fiecare angajat in luna curenta
SELECT nume AS [Nume Angajat], SUM(cantitate) AS [Nr. de cani prelucrate]
FROM Angajati AS a
INNER JOIN Prelucrari_comenzi AS p
ON a.id_angajat = p.id_angajat
INNER JOIN Comenzi AS c
ON p.id_comanda = c.id_comanda
INNER JOIN Cani_comandate AS cc
ON c.id_comanda = cc.id_comanda
WHERE MONTH(p.data_preluarii_comenzii) = MONTH(CURRENT_TIMESTAMP) AND
YEAR(p.data_preluarii_comenzii) = YEAR(CURRENT_TIMESTAMP)
GROUP BY nume

-- Care sunt canile care s-au comandat cel putin odata anul acesta?
SELECT DISTINCT c.id_cana, model, capacitate, c.pret
FROM Cani_comandate as cc
INNER JOIN Cani as c
ON cc.id_cana = c.id_cana
INNER JOIN Comenzi as co
ON co.id_comanda = cc.id_comanda
WHERE YEAR(co.data_efectuarii_comenzii) = YEAR(CURRENT_TIMESTAMP)

-- Ce clienti au cumparat cel putin 2 cani anul acesta?
SELECT nume AS [Nume Client], SUM(cantitate) AS [Nr. de cani comandate]
FROM Clienti AS cl
INNER JOIN Comenzi AS co
ON cl.id_client = co.id_client
INNER JOIN Cani_comandate AS cc
ON co.id_comanda = cc.id_comanda
WHERE YEAR(co.data_efectuarii_comenzii) = YEAR(CURRENT_TIMESTAMP)
GROUP BY nume
HAVING SUM(cantitate) >= 2

-- De cate ori s-a comandat fiecare cana in acest an?
SELECT ca.id_cana, model, capacitate, ca.pret, SUM(cantitate) AS [Nr. de comenzi]
FROM Cani as ca
LEFT OUTER JOIN Cani_comandate as cc
ON cc.id_cana = ca.id_cana
LEFT OUTER JOIN Comenzi as co
ON co.id_comanda = cc.id_comanda
WHERE YEAR(co.data_efectuarii_comenzii) = YEAR(CURRENT_TIMESTAMP) OR
co.data_efectuarii_comenzii IS NULL
GROUP BY ca.id_cana, model, capacitate, ca.pret

-- Care sunt genurile clientilor?
SELECT DISTINCT gen
FROM Clienti

-- Care sunt canile facute din mai multe materiale?
SELECT ca.id_cana, model, capacitate, ca.pret, COUNT(id_material) AS [Nr. materiale felosite]
FROM Cani as ca
INNER JOIN Materiale_folosite AS mf
ON ca.id_cana = mf.id_cana
GROUP BY ca.id_cana, model, capacitate, pret
HAVING COUNT(id_material) > 1

-- Cate cani s-au vandut de la fiecare furnizor in anul acesta?
SELECT nume, SUM(cantitate) AS [Nr. de cani]
FROM Furnizori AS f
LEFT JOIN Cani AS ca
ON ca.id_furnizor = f.id_furnizor
LEFT JOIN Cani_comandate AS cc
ON ca.id_cana = cc.id_cana
LEFT JOIN Comenzi AS co
ON cc.id_comanda = co.id_comanda
WHERE YEAR(co.data_efectuarii_comenzii) = YEAR(CURRENT_TIMESTAMP) OR
co.data_efectuarii_comenzii IS NULL
GROUP BY nume

-- Ce cani rezistente la soc avem?
SELECT ca.model--, COUNT(*) AS [Rezistent]
FROM Cani AS ca
INNER JOIN Materiale_folosite AS mf
ON ca.id_cana = mf.id_cana
INNER JOIN Materiale AS ma
ON mf.id_material = ma.id_material
GROUP BY ca.model
HAVING SUM(CAST(ma.rezistent_la_soc_puternic AS INT)) = COUNT(*)

-- Care este data in care s-a comandat ultima data o cana de la fiecare furnizor?
SELECT f.nume, MAX(co.data_efectuarii_comenzii) AS [Data ultimei comenzi]
FROM Furnizori AS f
LEFT OUTER JOIN Cani AS ca
ON f.id_furnizor = ca.id_furnizor
LEFT OUTER JOIN Cani_comandate AS cc
ON ca.id_cana = cc.id_cana
LEFT OUTER JOIN Comenzi AS co
ON cc.id_comanda = co.id_comanda
GROUP BY f.nume









/*
-- Cate materiale foloseste un furnizor
SELECT f.nume, COUNT(DISTINCT ma.nume) AS [Nr. de materiale]
FROM Furnizori AS f
LEFT JOIN Cani AS ca
ON ca.id_furnizor = f.id_furnizor
LEFT JOIN Materiale_folosite AS mf
ON ca.id_cana = mf.id_cana
LEFT JOIN Materiale AS ma
ON mf.id_material = ma.id_material
GROUP BY f.nume
*/

-- Cate cani avem din plastic?

-- Care sunt angajatii care au mai mult de 2 contracte?
