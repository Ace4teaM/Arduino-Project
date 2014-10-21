/*
   Extension de la classe d'entité CommandeArgument

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
    public partial class CommandeArgument : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["COMMANDE_ARGUMENT_ID"]) != String.Empty) ? (GetPropertyDesc("COMMANDE_ARGUMENT_ID") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["DESCRIPTION"]) != String.Empty) ? (GetPropertyDesc("DESCRIPTION") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["TYPEVALEUR"]) != String.Empty) ? (GetPropertyDesc("TYPEVALEUR") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["NOM"]) != String.Empty) ? (GetPropertyDesc("NOM") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
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
                    case "COMMANDE_ARGUMENT_ID":
                          if(this.COMMANDE_ARGUMENT_ID == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "DESCRIPTION":
                          if(this.DESCRIPTION == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "TYPEVALEUR":
                          if(this.TYPEVALEUR == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "NOM":
                          if(this.NOM == null){
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

                    case "COMMANDE_ARGUMENT_ID":
                        return "";

                    case "DESCRIPTION":
                        return "";

                    case "TYPEVALEUR":
                        return "";

                    case "NOM":
                        return "";
            }
            return "";
        }
    }
}