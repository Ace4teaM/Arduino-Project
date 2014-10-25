/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     25/10/2014 18:00:01                          */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Commande') and o.name = 'FK_COMMANDE_R2_EQUIPEMENT')
alter table Commande
   drop constraint FK_COMMANDE_R2_EQUIPEMENT
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Equipement') and o.name = 'FK_EQUIPEMENT_R4_SERVEUR')
alter table Equipement
   drop constraint FK_EQUIPEMENT_R4_SERVEUR
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('Etat') and o.name = 'FK_ETAT_R1_EQUIPEMENT')
alter table Etat
   drop constraint FK_ETAT_R1_EQUIPEMENT
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Commande')
            and   name  = 'R2_FK'
            and   indid > 0
            and   indid < 255)
   drop index Commande.R2_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Commande')
            and   type = 'U')
   drop table Commande
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Equipement')
            and   name  = 'R4_FK'
            and   indid > 0
            and   indid < 255)
   drop index Equipement.R4_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Equipement')
            and   type = 'U')
   drop table Equipement
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('Etat')
            and   name  = 'R1_FK'
            and   indid > 0
            and   indid < 255)
   drop index Etat.R1_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Etat')
            and   type = 'U')
   drop table Etat
go

if exists (select 1
            from  sysobjects
           where  id = object_id('Serveur')
            and   type = 'U')
   drop table Serveur
go

/*==============================================================*/
/* Table: Commande                                              */
/*==============================================================*/
create table Commande (
   Commande_Id          int                  identity,
   Equipement_Id        int                  null,
   Description          varchar(256)         not null,
   CodeCmd              char(4)              not null,
   CmdParams            varchar(1024)        null,
   constraint PK_COMMANDE primary key nonclustered (Commande_Id)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Commande')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Commande_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Commande_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant de la commande',
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Commande_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Commande')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Equipement_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Equipement_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant de l''équipement',
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Equipement_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Commande')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Description')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Description'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Description',
   'user', @CurrentUser, 'table', 'Commande', 'column', 'Description'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Commande')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'CodeCmd')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Commande', 'column', 'CodeCmd'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Code commande',
   'user', @CurrentUser, 'table', 'Commande', 'column', 'CodeCmd'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Commande')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'CmdParams')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Commande', 'column', 'CmdParams'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Paramètres de la commande',
   'user', @CurrentUser, 'table', 'Commande', 'column', 'CmdParams'
go

/*==============================================================*/
/* Index: R2_FK                                                 */
/*==============================================================*/
create index R2_FK on Commande (
Equipement_Id ASC
)
go

/*==============================================================*/
/* Table: Equipement                                            */
/*==============================================================*/
create table Equipement (
   Equipement_Id        int                  identity,
   Serveur_Id           int                  null,
   Nom                  varchar(64)          not null,
   Description          varchar(256)         null,
   RxPinNum             int                  null,
   TxPinNum             int                  null,
   Px                   int                  null,
   Py                   int                  null,
   Pz                   int                  null,
   constraint PK_EQUIPEMENT primary key nonclustered (Equipement_Id)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Equipement_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Equipement_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant de l''équipement',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Equipement_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Serveur_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Serveur_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant du serveur',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Serveur_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Nom')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Nom'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Nom',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Nom'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Description')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Description'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Description',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Description'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'RxPinNum')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'RxPinNum'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Numéro PIN (RX)',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'RxPinNum'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'TxPinNum')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'TxPinNum'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Numéro PIN (TX)',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'TxPinNum'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Px')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Px'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Position X',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Px'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Py')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Py'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Position Y',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Py'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Equipement')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Pz')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Pz'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Position Z',
   'user', @CurrentUser, 'table', 'Equipement', 'column', 'Pz'
go

/*==============================================================*/
/* Index: R4_FK                                                 */
/*==============================================================*/
create index R4_FK on Equipement (
Serveur_Id ASC
)
go

/*==============================================================*/
/* Table: Etat                                                  */
/*==============================================================*/
create table Etat (
   Etat_Id              int                  identity,
   Equipement_Id        int                  null,
   Nom                  varchar(64)          not null,
   Valeur               varchar(64)          null,
   constraint PK_ETAT primary key nonclustered (Etat_Id)
)
go

if exists (select 1 from  sys.extended_properties
           where major_id = object_id('Etat') and minor_id = 0)
begin 
   declare @CurrentUser sysname 
select @CurrentUser = user_name() 
execute sp_dropextendedproperty 'MS_Description',  
   'user', @CurrentUser, 'table', 'Etat' 
 
end 


select @CurrentUser = user_name() 
execute sp_addextendedproperty 'MS_Description',  
   'Propriété d''un équipement', 
   'user', @CurrentUser, 'table', 'Etat'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Etat')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Equipement_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Equipement_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant de l''équipement',
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Equipement_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Etat')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Nom')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Nom'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Nom',
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Nom'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Etat')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Valeur')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Valeur'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Valeur',
   'user', @CurrentUser, 'table', 'Etat', 'column', 'Valeur'
go

/*==============================================================*/
/* Index: R1_FK                                                 */
/*==============================================================*/
create index R1_FK on Etat (
Equipement_Id ASC
)
go

/*==============================================================*/
/* Table: Serveur                                               */
/*==============================================================*/
create table Serveur (
   Serveur_Id           int                  identity,
   AdressePhysique      varchar(17)          not null,
   Jeton                varchar(17)          not null,
   AdresseIP            varchar(15)          null,
   constraint PK_SERVEUR primary key nonclustered (Serveur_Id),
   constraint AK_ADDRESS_MAC_SERVEUR unique (AdressePhysique),
   constraint AK_TOKEN_SERVEUR unique (Jeton)
)
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Serveur')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Serveur_Id')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'Serveur_Id'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Identifiant du serveur',
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'Serveur_Id'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Serveur')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'AdressePhysique')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'AdressePhysique'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Adresse Physique',
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'AdressePhysique'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Serveur')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'Jeton')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'Jeton'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Jeton',
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'Jeton'
go

if exists(select 1 from sys.extended_properties p where
      p.major_id = object_id('Serveur')
  and p.minor_id = (select c.column_id from sys.columns c where c.object_id = p.major_id and c.name = 'AdresseIP')
)
begin
   declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_dropextendedproperty 'MS_Description', 
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'AdresseIP'

end


select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Adresse IP',
   'user', @CurrentUser, 'table', 'Serveur', 'column', 'AdresseIP'
go

alter table Commande
   add constraint FK_COMMANDE_R2_EQUIPEMENT foreign key (Equipement_Id)
      references Equipement (Equipement_Id)
go

alter table Equipement
   add constraint FK_EQUIPEMENT_R4_SERVEUR foreign key (Serveur_Id)
      references Serveur (Serveur_Id)
go

alter table Etat
   add constraint FK_ETAT_R1_EQUIPEMENT foreign key (Equipement_Id)
      references Equipement (Equipement_Id)
go

