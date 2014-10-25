/*
   Format de données Numeric

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
      public static class Numeric
      {
            /// <summary>
            /// 
            /// </summary>
            /// <param name="str">Chaine à valider</param>
            /// <returns>True si le champ est valide, sinon False</returns>
            public static bool Validate(string str, ref string msg)
            {
               System.Text.RegularExpressions.Regex myRegex = new Regex(@"^(?:0|1[0-9]*)(?:\.[0-9]+)?$");
               if (!myRegex.IsMatch(str))
               {
                   msg = "INVALID_NUMERIC_FORMAT";
                   //Result.last = new Result().Failed("INVALID_NUMERIC_FORMAT");
                   return false;
               }
               msg = String.Empty;
               return true;
            }
      }
}