/*
	Jeu d'essai
*/

SET NOCOUNT ON;

------------------------------------------------------------------------------------
-- Nettoie la base
------------------------------------------------------------------------------------

delete from Commande;
delete from Equipement;
delete from Serveur;
go

-- Reinitialise les sequences d'indentités à 1 (Ids)
DBCC CHECKIDENT('Commande', RESEED, 1) WITH NO_INFOMSGS;
DBCC CHECKIDENT('Equipement', RESEED, 1) WITH NO_INFOMSGS;
DBCC CHECKIDENT('Serveur', RESEED, 1) WITH NO_INFOMSGS;
go

/*
	-----------------------------------------------------------------------------------
	Equipements
	-----------------------------------------------------------------------------------
*/
insert into Serveur (AdressePhysique, Jeton)
	values('7A-C4-0E-1D-F9-F6','hklhjkl');
declare @Serveur_Id int = convert(int,@@IDENTITY);

insert into Equipement (Serveur_Id,Nom,Description,RxPinNum,TxPinNum,Px,Py,Pz)
	values(@Serveur_Id,'ArduinoMega','Arduino basique',NULL,NULL,0,0,0);
declare @Equipement_Id int = convert(int,@@IDENTITY);

insert into Commande (Equipement_Id,Description,CodeCmd,CmdParams)
	values(@Equipement_Id,'Active la led interne','DOUT','PinNum=13;Value=1;');
	
insert into Commande (Equipement_Id,Description,CodeCmd,CmdParams)
	values(@Equipement_Id,'Desactive la led interne','DOUT','PinNum=13;Value=0;');

/*
insert into Commande(Nom)
	values('Eteindre Led1');
declare @Commande_Id int = convert(int,@@IDENTITY);
insert into Commande_Argument (Nom,Description,TypeValeur)
	values(@Commande_Id, 'Eteindre Led1', 'DOUT', 'bit');
insert into Commande_Argument (Nom,Description,TypeValeur)
	values(@Commande_Id, 'Allumer Led1', 'DOUT', '1');
go

insert into Commande(Nom)
	values('Allumer Led1');
declare @Commande_Id int = convert(int,@@IDENTITY);
insert into Commande_Argument (Nom,Description,TypeValeur)
	values(@Commande_Id, 'Eteindre Led1', 'DOUT', '0');
insert into Commande_Argument (Nom,Description,TypeValeur)
	values(@Commande_Id, 'Allumer Led1', 'DOUT', '1');
go*/