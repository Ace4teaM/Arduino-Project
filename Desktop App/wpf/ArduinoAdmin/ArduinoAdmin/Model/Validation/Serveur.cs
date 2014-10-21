/*
   Extension de la classe d'entité Serveur

   !!Attention!!
   Ce code source est généré automatiquement, toutes modifications seront perdues
   
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Controls;
using System.Globalization;
using System.Reflection;
using ArduinoAdmin.Lib;
using ArduinoAdmin.Formats;
namespace ArduinoAdmin.Model
{
    /// <summary>
    /// Implémente la validation des propriétés
    /// </summary>
    public partial class Serveur : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["SERVEUR_ID"]) != String.Empty) ? (GetPropertyDesc("SERVEUR_ID") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["ADDRESS_MAC"]) != String.Empty) ? (GetPropertyDesc("ADDRESS_MAC") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["TOKEN"]) != String.Empty) ? (GetPropertyDesc("TOKEN") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                return all_mess;
            }
        }

        // Validation par propriété
        public string this[string propertyName]
        {
            get
            {
                string msg = String.Empty;
                switch (propertyName)
                {
                    case "SERVEUR_ID":
                          if(this.SERVEUR_ID == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "ADDRESS_MAC":
                          if(this.ADDRESS_MAC == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "TOKEN":
                          if(this.TOKEN == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                }
                
                if (msg != String.Empty)
                    return GetPropertyDesc(propertyName) + ":\n" + App.TranslateAppErrorCode(msg);
                return String.Empty;
            }
        }

        public static string GetClassDesc()
        {
            return "";
        }
        
        public static string GetPropertyDesc(string propertyName)
        {
            switch (propertyName)
            {

                    case "SERVEUR_ID":
                        return "";

                    case "ADDRESS_MAC":
                        return "";

                    case "TOKEN":
                        return "";
            }
            return "";
        }
    }
}