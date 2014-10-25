--------------------------------------------------------
--
-- Création des bases de données
-- Notes:
--		* Le codage des caractères est insensible à la casse (CI)
--------------------------------------------------------

USE Master;
GO

-- Instance de test
if db_id('arduino') is not null
begin
	-- deconnecte les utilisateurs
	ALTER DATABASE [arduino] SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
	drop database arduino;
end
create database arduino COLLATE SQL_Latin1_General_CP1_CI_AS;
