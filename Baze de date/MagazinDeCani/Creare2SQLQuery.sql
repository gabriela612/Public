
USE MagazinDeCani;

CREATE TABLE Cani (
	-- id_cana, capactate(litri), model, [in_stoc], id_furnizor,
	-- greutate(grame), pret, [cantitate], 
	id_cana INT PRIMARY KEY IDENTITY (1,1),
	model VARCHAR(255),
	capacitate INT CHECK(capacitate >= 0),
	pret INT CHECK(pret >= 0) NOT NULL,
	id_furnizor INT FOREIGN KEY REFERENCES Furnizori(id_furnizor) ON UPDATE CASCADE,
);

CREATE TABLE Comenzi (
	-- id_comanda, id_client, pret, adresa_de_livrare, achitata_online
	id_comanda INT PRIMARY KEY IDENTITY (1,1),
	pret INT CHECK(pret >= 0) NOT NULL,
	adresa_de_livrare VARCHAR(255) NOT NULL,
	achitata_online BIT NOT NULL,
	data_efectuarii_comenzii DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	id_client INT FOREIGN KEY REFERENCES Clienti(id_client) ON UPDATE CASCADE,
)

CREATE TABLE Cani_comandate (
	-- id_cana_comandata, id_cana, id_comanda, cantitate
	cantitate INT CHECK(cantitate >= 0) NOT NULL,
	id_cana INT FOREIGN KEY REFERENCES Cani(id_cana) ON UPDATE CASCADE,
	id_comanda INT FOREIGN KEY REFERENCES Comenzi(id_comanda) ON UPDATE CASCADE,
	CONSTRAINT id_cani_comandate PRIMARY KEY (id_cana, id_comanda)
);

CREATE TABLE Materiale_folosite (
	-- id_material_folosit, id_cana, id_material
	id_cana INT FOREIGN KEY REFERENCES Cani(id_cana) ON UPDATE CASCADE,
	id_material INT FOREIGN KEY REFERENCES Materiale(id_material) ON UPDATE CASCADE,
	CONSTRAINT id_materiale_folosite PRIMARY KEY (id_cana, id_material)
);

CREATE TABLE Angajati (
	-- id_angajat, salariu, data_angajarii, nume, id_categorie
	id_angajat INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) NOT NULL,
	salariu INT NOT NULL DEFAULT 0 CHECK(salariu >= 0),
	--data_angajarii DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	--id_categorie INT FOREIGN KEY REFERENCES Categorii_de_angajati(id_categorie) ON UPDATE CASCADE,
);

CREATE TABLE Prelucrari_comenzi (
	-- id_prelucrarea_comanda, data, id_angajat, id_comanda
	data_preluarii_comenzii DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	id_angajat INT FOREIGN KEY REFERENCES Angajati(id_angajat) ON UPDATE CASCADE,
	id_comanda INT FOREIGN KEY REFERENCES Comenzi(id_comanda) ON UPDATE CASCADE,
	CONSTRAINT id_prelucrari_comenzi PRIMARY KEY (id_angajat, id_comanda)
);

CREATE TABLE Contracte_de_angajare (
	id_contract_de_angajare INT PRIMARY KEY IDENTITY (1,1),
	data_semnarii DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
	in_vigoare BIT NOT NULL DEFAULT 1,
	id_categorie INT FOREIGN KEY REFERENCES Categorii_de_angajati(id_categorie) ON UPDATE CASCADE,
	id_angajat INT FOREIGN KEY REFERENCES Angajati(id_angajat) ON UPDATE CASCADE,
);

INSERT INTO Cani(model, capacitate, pret, id_furnizor)
VALUES('Cana alba simpla', 250, 20, 1);

INSERT INTO Comenzi(pret, adresa_de_livrare, achitata_online, id_client)
VALUES(50, 'Strada Ghinionului, nr. 13', 0, 1);

INSERT INTO Cani_comandate(cantitate, id_cana, id_comanda)
VALUES(2, 1, 1);

INSERT INTO Materiale_folosite(id_cana, id_material)
VALUES(1, 1);

INSERT INTO Angajati(nume, salariu)
VALUES('Maria Popescu', 2600);

INSERT INTO Prelucrari_comenzi(id_angajat, id_comanda)
VALUES(1, 1);

INSERT INTO Contracte_de_angajare(id_categorie, id_angajat)
VALUES(1, 1);






INSERT INTO Cani(model, capacitate, pret, id_furnizor)
VALUES('Cana neagra simpla', 250, 20, 1),
('Cana Barbie', 150, 30, 3),
('Cana albastra simpla', 250, 20, 1),
('Cana rezistenta metal', 200, 30, 5);

INSERT INTO Cani(model, capacitate, pret, id_furnizor)
VALUES('Cana Superman', 150, 30, 3);

INSERT INTO Cani(model, capacitate, pret, id_furnizor)
VALUES('Cana metal si plastic', 150, 30, 5);

INSERT INTO Comenzi(pret, adresa_de_livrare, achitata_online, id_client)
VALUES(45, 'Strada Ghinionului, nr. 16', 1, 4),
(55, 'Strada Ghinionului, nr. 16', 0, 4),
(55, 'Strada Ghinionului, nr. 14', 1, 2),
(65, 'Strada Ghinionului, nr. 17', 1, 5);

INSERT INTO Cani_comandate(cantitate, id_cana, id_comanda)
VALUES(2, 2, 2),
(1, 3, 3),
(2, 1, 4),
(1, 4, 5),
(1, 5, 5);

INSERT INTO Materiale_folosite(id_cana, id_material)
VALUES(2, 1),
(3, 4),
(3, 5),
(4, 1),
(5, 6);

INSERT INTO Materiale_folosite(id_cana, id_material)
VALUES(7, 1),
(7, 6);

INSERT INTO Angajati(nume, salariu)
VALUES('Grigorean Muntean', 3600),
('Aurelian Cozma', 3200),
('Niculina Marin', 2600),
('Ionel Moldovan', 2650);

INSERT INTO Prelucrari_comenzi(id_angajat, id_comanda)
VALUES(4, 2),
(5, 5),
(1, 2),
(1, 5),
(4, 3);

INSERT INTO Contracte_de_angajare(id_categorie, id_angajat)
VALUES(2, 4),
(2, 5),
(4, 3),
(5, 2);

