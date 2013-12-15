/*==============================================================*/
/* Nom de SGBD :  PostgreSQL 8 (WFW)                            */
/* Date de création :  15/12/2013 11:34:33                      */
/*==============================================================*/


drop table if exists CLIENT  CASCADE;

drop table if exists CONTROLEUR  CASCADE;

drop table if exists EQUIPEMENT  CASCADE;

drop table if exists PIN  CASCADE;

drop table if exists REQUIS  CASCADE;

drop domain if exists PIN_TYPE CASCADE;

/*==============================================================*/
/* Domaine : PIN_TYPE                                           */
/*==============================================================*/
create domain PIN_TYPE as CHAR(1);

/*==============================================================*/
/* Table : CLIENT                                               */
/*==============================================================*/
create table CLIENT (
   CLIENT_ID            INT4                 not null,
   ADRESSE_IP           CHAR(11)             not null,
   constraint PK_CLIENT primary key (CLIENT_ID)
);

/*==============================================================*/
/* Table : CONTROLEUR                                           */
/*==============================================================*/
create table CONTROLEUR (
   CONTROLEUR_ID        INT4                 not null,
   ADRESSE_IP           CHAR(11)             not null,
   LIBRE                BOOL                 not null,
   constraint PK_CONTROLEUR primary key (CONTROLEUR_ID)
);

/*==============================================================*/
/* Table : EQUIPEMENT                                           */
/*==============================================================*/
create table EQUIPEMENT (
   EQUIPEMENT_ID        INT4                 not null,
   constraint PK_EQUIPEMENT primary key (EQUIPEMENT_ID)
);

/*==============================================================*/
/* Table : PIN                                                  */
/*==============================================================*/
create table PIN (
   PIN_ID               INT4                 not null,
   CONTROLEUR_ID        INT4                 not null,
   PIN_TYPE             PIN_TYPE             not null,
   PIN_NUM              INT4                 not null,
   constraint PK_PIN primary key (PIN_ID)
);

/*==============================================================*/
/* Table : REQUIS                                               */
/*==============================================================*/
create table REQUIS (
   EQUIPEMENT_ID        INT4                 not null,
   PIN_ID               INT4                 not null,
   constraint PK_REQUIS primary key (EQUIPEMENT_ID, PIN_ID)
);

alter table PIN
   add constraint FK_RESERVE foreign key (CONTROLEUR_ID)
      references CONTROLEUR (CONTROLEUR_ID)
      on delete restrict on update restrict;

alter table REQUIS
   add constraint FK_REQUIS foreign key (PIN_ID)
      references PIN (PIN_ID)
      on delete restrict on update restrict;

alter table REQUIS
   add constraint FK_REQUIS2 foreign key (EQUIPEMENT_ID)
      references EQUIPEMENT (EQUIPEMENT_ID)
      on delete restrict on update restrict;

