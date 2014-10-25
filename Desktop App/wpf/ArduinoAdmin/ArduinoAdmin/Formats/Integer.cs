/*
   Format de données Integer

   !!Attention!!
   Ce code source est généré automatiquement depuis PowerDesigner, toutes modifications risques d'être perdues
   
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Controls;
using System.Globalization;
using System.Reflection;
using ArduinoAdmin.Formats;
using ArduinoAdmin.Lib;
using System.Text.RegularExpressions;

namespace ArduinoAdmin.Formats
{
      public static class Integer
      {
            /// <summary>
            /// 
            /// </summary>
            /// <param name="str">Chaine à valider</param>
            /// <returns>True si le champ est valide, sinon False</returns>
            public static bool Validate(string str, ref string msg)
            {
               System.Text.RegularExpressions.Regex myRegex = new Regex(@"^([0-9]+)$");
               if (!myRegex.IsMatch(str))
               {
                   msg = "INVALID_INTEGER_FORMAT";
                   //Result.last = new Result().Failed("INVALID_INTEGER_FORMAT");
                   return false;
               }
               msg = String.Empty;
               return true;
            }
      }
}