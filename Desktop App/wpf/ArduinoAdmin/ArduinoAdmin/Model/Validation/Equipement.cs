/*
   Extension de la classe d'entité Equipement

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
    public class Equipement : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["Equipement_Id"]) != String.Empty) ? (GetPropertyDesc("Equipement_Id") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Nom"]) != String.Empty) ? (GetPropertyDesc("Nom") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Description"]) != String.Empty) ? (GetPropertyDesc("Description") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["RxPinNum"]) != String.Empty) ? (GetPropertyDesc("RxPinNum") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["TxPinNum"]) != String.Empty) ? (GetPropertyDesc("TxPinNum") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Px"]) != String.Empty) ? (GetPropertyDesc("Px") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Py"]) != String.Empty) ? (GetPropertyDesc("Py") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Pz"]) != String.Empty) ? (GetPropertyDesc("Pz") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
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
                    case "Equipement_Id":
                          if(this.Equipement_Id == null){
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
                    case "Description":
                          if(this.Description == null)
                              break;
                           ArduinoAdmin.Formats.NotEmpty.Validate(this.Description.ToString(),ref msg);
                        break;
                    case "RxPinNum":
                          if(this.RxPinNum == null)
                              break;
                           // Pas de test
                        break;
                    case "TxPinNum":
                          if(this.TxPinNum == null)
                              break;
                           // Pas de test
                        break;
                    case "Px":
                          if(this.Px == null)
                              break;
                           // Pas de test
                        break;
                    case "Py":
                          if(this.Py == null)
                              break;
                           // Pas de test
                        break;
                    case "Pz":
                          if(this.Pz == null)
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
            return "";
        }
        
        public static string GetPropertyDesc(string propertyName)
        {
            switch (propertyName)
            {

                    case "Equipement_Id":
                        return "Identifiant de l'équipement";

                    case "Nom":
                        return "Nom";

                    case "Description":
                        return "Description";

                    case "RxPinNum":
                        return "Numéro PIN (RX)";

                    case "TxPinNum":
                        return "Numéro PIN (TX)";

                    case "Px":
                        return "Position X";

                    case "Py":
                        return "Position Y";

                    case "Pz":
                        return "Position Z";
            }
            return "";
        }
    }
}