
@echo off


echo Mise a jour de la base de donnees..
echo Creation
sqlcmd -E -S "THOMAS-PC\SQLSERVEREXPRESS" -d master -i 0.Create.sql
echo Tables
sqlcmd -E -S "THOMAS-PC\SQLSERVEREXPRESS" -d arduino -i 1.Tables.sql
echo Jeu d'essai
sqlcmd -E -S "THOMAS-PC\SQLSERVEREXPRESS" -d arduino -i 4.JeuEssai.sql

pause