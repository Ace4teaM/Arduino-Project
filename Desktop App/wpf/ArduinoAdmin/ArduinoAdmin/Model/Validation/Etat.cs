/*
   Extension de la classe d'entité Etat

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
    public class Etat : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["Etat_Id"]) != String.Empty) ? (GetPropertyDesc("Etat_Id") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Nom"]) != String.Empty) ? (GetPropertyDesc("Nom") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Valeur"]) != String.Empty) ? (GetPropertyDesc("Valeur") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
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
                    case "Etat_Id":
                          if(this.Etat_Id == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "Nom":
                          if(this.Nom == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "Valeur":
                          if(this.Valeur == null)
                              break;
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
            return "Propriété d'un équipement";
        }
        
        public static string GetPropertyDesc(string propertyName)
        {
            switch (propertyName)
            {

                    case "Etat_Id":
                        return "";

                    case "Nom":
                        return "Nom";

                    case "Valeur":
                        return "Valeur";
            }
            return "";
        }
    }
}