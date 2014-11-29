/*
   Extension de la classe d'entité Commande

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
    public class Commande : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["Commande_Id"]) != String.Empty) ? (GetPropertyDesc("Commande_Id") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Description"]) != String.Empty) ? (GetPropertyDesc("Description") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["CodeCmd"]) != String.Empty) ? (GetPropertyDesc("CodeCmd") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["CmdParams"]) != String.Empty) ? (GetPropertyDesc("CmdParams") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
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
                    case "Commande_Id":
                          if(this.Commande_Id == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "Description":
                          if(this.Description == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           ArduinoAdmin.Formats.NotEmpty.Validate(this.Description.ToString(),ref msg);
                        break;
                    case "CodeCmd":
                          if(this.CodeCmd == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "CmdParams":
                          if(this.CmdParams == null)
                              break;
                           ArduinoAdmin.Formats.StringParam.Validate(this.CmdParams.ToString(),ref msg);
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

                    case "Commande_Id":
                        return "Identifiant de la commande";

                    case "Description":
                        return "Description";

                    case "CodeCmd":
                        return "Code commande";

                    case "CmdParams":
                        return "Paramètres de la commande";
            }
            return "";
        }
    }
}