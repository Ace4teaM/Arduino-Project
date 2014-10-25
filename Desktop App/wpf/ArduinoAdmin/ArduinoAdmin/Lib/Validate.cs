using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Controls;
using System.Windows.Media;
using System.Diagnostics;
using System.Windows;
using System.Reflection;
using System.ComponentModel.DataAnnotations;
using System.Windows.Data;
using ArduinoAdmin.Lib;


namespace ArduinoAdmin.Lib
{
    public static class Validate
    {
        /// <summary>
        /// Test la validité d'une dépendance et ses enfants
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="ex">Retourne la première exception trouvée</param>
        /// <returns>True, si l'ojet et les objets enfants sont valides. Sinon, False.</returns>
        public static bool IsValid(DependencyObject obj, out Exception ex, bool ignoreDisabledElements)
        {
            List<DependencyObject> list = new List<DependencyObject>();
            EnumChildren(obj, list, ignoreDisabledElements);
            for (int i = 0; i < list.Count; i++)
            {
                if (Validation.GetHasError(list[i]))
                {
                    //obtient la premiere erreur
                    ValidationError err = Validation.GetErrors(list[i])[0];
/*
                    Console.WriteLine("GetErrors.count =" + Validation.GetErrors(list[i]).Count);
                    Console.WriteLine("GetErrors.ErrorContent =" + err.ErrorContent);
                    Console.WriteLine("GetErrors.BindingInError =" + err.BindingInError);
                    Console.WriteLine("GetErrors.RuleInError =" + err.RuleInError);
                    Console.WriteLine("Exception =" + err.Exception);
*/
                    // erreur venant d'une exception ?
                    if (err.Exception != null)
                    {
                        ex = err.Exception;
                        return false;
                    }
                    
                    // message d'erreur ?
                    if (err.ErrorContent != null)
                    {
                        ex = new ValidationException(err.ErrorContent.ToString());
                        return false;
                    }

                    // autre ?
                    ex = new ValidationException("Erreur de validation inconnue");
                    return false;
                }
            }

            if (Validation.GetHasError(obj))
            {
                ex = Validation.GetErrors(obj)[0].Exception;
                Console.WriteLine("IsValid error :" + Validation.GetErrors(obj)[0].Exception);
                return false;
            }

            ex = null;
            return true;
        }

        /// <summary>
        /// Valide un objet dont le format est passé en argument
        /// </summary>
        /// <param name="obj">Objet à valider</param>
        /// <param name="format">Format de validation (Nom de la fonction sans 'Validate')</param>
        /// <param name="msg">Chaine recevant le message d'erreur</param>
        /// <returns>True si le champ est valide, sinon False</returns>
        public static bool ValidateDomain(this object obj, string[] formatList, ref string msg)
        {
            string objValue = (obj == null) ? "" : obj.ToString();
            foreach (string format in formatList)
            {
                if(objValue == format)
                    return true;
            }

            msg = "INVALID_FORMAT";
            return false;
        }

        /// <summary>
        /// Convertie un booléen
        /// </summary>
        /// <param name="str">Chaine à convertir</param>
        /// <returns>Valeur de retour</returns>
        public static bool ParseBool(this string str)
        {
            switch (str.ToLower())
            {
                case "1":
                case "oui":
                case "vrai":
                case "true":
                    return true;
            }
            return false;
        }
        /// <summary>
        /// Enumére les enfants visuel d'un objet
        /// </summary>
        /// <param name="obj">Objet parent</param>
        /// <param name="list">Liste recevant les objets enfants</param>
        /// <param name="ignoreDisabledElements">Si true, ignore les éléments inactif (propriété IsEnable des types UIElement)</param>
        /// <returns></returns>
        public static List<DependencyObject> EnumChildren(DependencyObject obj, List<DependencyObject> list, bool ignoreDisabledElements)
        {
            int nChild = VisualTreeHelper.GetChildrenCount(obj);
            for (int i = 0; i < nChild; i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(obj, i);
                //ignore les éléments inactif
                if (ignoreDisabledElements && child is UIElement && (child as UIElement).IsEnabled == false)
                    continue;
                //ajoute a la liste
                list.Add(child);
                if(VisualTreeHelper.GetChildrenCount(child) > 0)
                    EnumChildren(child, list, ignoreDisabledElements);
            }
            return list;
        }
    }
}
