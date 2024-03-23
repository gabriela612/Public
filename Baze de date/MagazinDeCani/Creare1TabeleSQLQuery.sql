
USE MagazinDeCani;

CREATE TABLE Furnizori (
	id_furnizor INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) UNIQUE NOT NULL,
	nr_telefon VARCHAR(255) UNIQUE NOT NULL,
	email VARCHAR(255) UNIQUE NOT NULL,

	-- id_furnizor, nume, email, nr_telefon
);

CREATE TABLE Clienti (
	id_client INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) NOT NULL,
	nr_telefon VARCHAR(255) UNIQUE NOT NULL,
	email VARCHAR(255) UNIQUE NOT NULL,
	parola VARCHAR(255) NOT NULL CHECK(LEN(parola) > 8), -- sa aiba mai mult de 8 char
	gen VARCHAR(255),
	adresa VARCHAR(255),
	-- id_client, email, nume, parola, data_nasterii, gen, telefon, adresa
);

CREATE TABLE Materiale (
	id_material INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) UNIQUE NOT NULL,
	rezistent_la_soc_puternic BIT NOT NULL DEFAULT 0,
	-- id_material, nume, rezistenta_la_soc_puternic
);

CREATE TABLE Categorii_de_angajati (
	id_categorie INT PRIMARY KEY IDENTITY (1,1),
	nume VARCHAR(255) UNIQUE,
	cerintele_postului VARCHAR(255) UNIQUE NOT NULL,
	salariu_de_pornire INT NOT NULL DEFAULT 0 CHECK(salariu_de_pornire >= 0), -- mai mare decat 0 sau minimul pe economie
	-- id_categorie, cerintele_postului, nume
);

INSERT INTO Furnizori(nume, nr_telefon, email)
VALUES('Maricica SRL', '0712312345', 'contact@maricicasrl.com');

INSERT INTO Clienti(nume, nr_telefon, email, parola, gen, adresa)
VALUES('Ionescu Ion', '0712345678', 'ion.ionescu@gmail.com', 'parola_mea_ion_ionescu', 'masculin', 'Strada Ghinionului, nr. 13');

INSERT INTO Materiale(nume)
VALUES('plastic');

INSERT INTO Categorii_de_angajati(nume, cerintele_postului, salariu_de_pornire)
VALUES('Livrator', 'Livrarea comenzilor.', 2500);




INSERT INTO Furnizori(nume, nr_telefon, email)
VALUES('CupaMug', '0711111111', 'contact@cupamug.com'),
('CaniRadu Ceramics', '0711111112', 'caniraduceramics.contact@outlook.com'),
('Andreea Creations', '0711111113', 'contact@andreeacreations.com'),
('CupCrafters', '0711111114', 'contact@cupcrafters.com');

INSERT INTO Clienti(nume, nr_telefon, email, parola, gen, adresa)
VALUES('Alexandru Gheorghiu', '0711111115', 'alexandru.heorghiu@gmail.com',
'parola_mea_alexandru_gheorghiu', 'masculin', 'Strada Ghinionului, nr. 14'),
('Camelia Barbu', '0711111116', 'camelia.barbu@yahoo.com',
'parola_mea_camelia_barbu', 'feminin', 'Strada Ghinionului, nr. 15'),
('Ana Dumitru', '0711111117', 'ana.dumitru@mail.com',
'parola_mea_ana_dumitru', 'prefer sa nu raspund', 'Strada Ghinionului, nr. 16'),
('Ioan Petrescu', '0711111118', 'ioan.petrescu@yahoo.com',
'parola_mea_ioan_petrescu', 'masculin', 'Strada Ghinionului, nr. 17');

INSERT INTO Materiale(nume, rezistent_la_soc_puternic)
VALUES('lemn', 1),
('carton', 0),
('sticla', 0),
('portelan', 0),
('metal', 1);

INSERT INTO Categorii_de_angajati(nume, cerintele_postului, salariu_de_pornire)
VALUES('Impachetare cani', 'Impacheteaza canile.', 2400),
('Secretar', 'Are atributiile unui secretar.', 2800),
('Manager', 'Are atributiile unui manager.', 3000),
('Inginer Software', 'Intretine si dezvolta site-ul si baza de date.', 3500);

