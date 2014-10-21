/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     21/10/2014 20:43:33                          */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('COMMANDE') and o.name = 'FK_COMMANDE_R2_EQUIPEMENT')
alter table COMMANDE
   drop constraint FK_COMMANDE_R2_EQUIPEMENT
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('COMMANDE_ARGUMENT') and o.name = 'FK_COMMANDE_ARGUMENT_R1_COMMANDE')
alter table COMMANDE_ARGUMENT
   drop constraint FK_COMMANDE_ARGUMENT_R1_COMMANDE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('EQUIPEMENT') and o.name = 'FK_EQUIPEMENT_R4_SERVEUR')
alter table EQUIPEMENT
   drop constraint FK_EQUIPEMENT_R4_SERVEUR
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('COMMANDE')
            and   name  = 'R2_FK'
            and   indid > 0
            and   indid < 255)
   drop index COMMANDE.R2_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('COMMANDE')
            and   type = 'U')
   drop table COMMANDE
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('COMMANDE_ARGUMENT')
            and   name  = 'R1_FK'
            and   indid > 0
            and   indid < 255)
   drop index COMMANDE_ARGUMENT.R1_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('COMMANDE_ARGUMENT')
            and   type = 'U')
   drop table COMMANDE_ARGUMENT
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('EQUIPEMENT')
            and   name  = 'R4_FK'
            and   indid > 0
            and   indid < 255)
   drop index EQUIPEMENT.R4_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('EQUIPEMENT')
            and   type = 'U')
   drop table EQUIPEMENT
go

if exists (select 1
            from  sysobjects
           where  id = object_id('SERVEUR')
            and   type = 'U')
   drop table SERVEUR
go

/*==============================================================*/
/* Table: COMMANDE                                              */
/*==============================================================*/
create table COMMANDE (
   COMMANDE_ID          int                  identity,
   EQUIPEMENT_ID        int                  null,
   DESCRIPTION          varchar(256)         null,
   constraint PK_COMMANDE primary key nonclustered (COMMANDE_ID)
)
go

/*==============================================================*/
/* Index: R2_FK                                                 */
/*==============================================================*/
create index R2_FK on COMMANDE (
EQUIPEMENT_ID ASC
)
go

/*==============================================================*/
/* Table: COMMANDE_ARGUMENT                                     */
/*==============================================================*/
create table COMMANDE_ARGUMENT (
   COMMANDE_ARGUMENT_ID int                  identity,
   COMMANDE_ID          int                  null,
   DESCRIPTION          varchar(256)         not null,
   TYPEVALEUR           varchar(32)          not null,
   NOM                  varchar(32)          not null,
   constraint PK_COMMANDE_ARGUMENT primary key nonclustered (COMMANDE_ARGUMENT_ID)
)
go

/*==============================================================*/
/* Index: R1_FK                                                 */
/*==============================================================*/
create index R1_FK on COMMANDE_ARGUMENT (
COMMANDE_ID ASC
)
go

/*==============================================================*/
/* Table: EQUIPEMENT                                            */
/*==============================================================*/
create table EQUIPEMENT (
   EQUIPEMENT_ID        int                  identity,
   SERVEUR_ID           int                  null,
   DESCRIPTION          varchar(256)         not null,
   RXPINNUM             int                  not null,
   TXPINNUM             int                  not null,
   constraint PK_EQUIPEMENT primary key nonclustered (EQUIPEMENT_ID)
)
go

/*==============================================================*/
/* Index: R4_FK                                                 */
/*==============================================================*/
create index R4_FK on EQUIPEMENT (
SERVEUR_ID ASC
)
go

/*==============================================================*/
/* Table: SERVEUR                                               */
/*==============================================================*/
create table SERVEUR (
   SERVEUR_ID           int                  identity,
   ADDRESS_MAC          tinyint              not null,
   TOKEN                varchar(8)           not null,
   constraint PK_SERVEUR primary key nonclustered (SERVEUR_ID),
   constraint AK_ADDRESS_MAC_SERVEUR unique (ADDRESS_MAC),
   constraint AK_TOKEN_SERVEUR unique (TOKEN)
)
go

alter table COMMANDE
   add constraint FK_COMMANDE_R2_EQUIPEMENT foreign key (EQUIPEMENT_ID)
      references EQUIPEMENT (EQUIPEMENT_ID)
go

alter table COMMANDE_ARGUMENT
   add constraint FK_COMMANDE_ARGUMENT_R1_COMMANDE foreign key (COMMANDE_ID)
      references COMMANDE (COMMANDE_ID)
go

alter table EQUIPEMENT
   add constraint FK_EQUIPEMENT_R4_SERVEUR foreign key (SERVEUR_ID)
      references SERVEUR (SERVEUR_ID)
go

