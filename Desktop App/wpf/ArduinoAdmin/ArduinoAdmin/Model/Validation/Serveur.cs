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
    public class Serveur : IDataErrorInfo
    {
        // Validation globale de l'entité
        public string Error
        {
            get
            {
                string all_mess = "";
                string msg;
                all_mess += ((msg = this["Serveur_Id"]) != String.Empty) ? (GetPropertyDesc("Serveur_Id") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["AdressePhysique"]) != String.Empty) ? (GetPropertyDesc("AdressePhysique") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["Jeton"]) != String.Empty) ? (GetPropertyDesc("Jeton") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
                all_mess += ((msg = this["AdresseIP"]) != String.Empty) ? (GetPropertyDesc("AdresseIP") + " :\n\t" + App.TranslateAppErrorCode(msg) + "\n") : String.Empty;
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
                    case "Serveur_Id":
                          if(this.Serveur_Id == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "AdressePhysique":
                          if(this.AdressePhysique == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "Jeton":
                          if(this.Jeton == null){
                              msg = "NOT_NULL_RESTRICTION";
                              break;
                            }
                           // Pas de test
                        break;
                    case "AdresseIP":
                          if(this.AdresseIP == null)
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

                    case "Serveur_Id":
                        return "Identifiant du serveur";

                    case "AdressePhysique":
                        return "Adresse Physique";

                    case "Jeton":
                        return "Jeton";

                    case "AdresseIP":
                        return "Adresse IP";
            }
            return "";
        }
    }
}